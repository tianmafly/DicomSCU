#include "associaterq.h"
#include <string.h>
#include "../type/uid.h"
#include "../dul/dulassociaterq.h"

AssociateRQ::AssociateRQ(AssociateRQPDU *associaterqpdu, string callingae, string calledae, string abstractsyntax)
{
    //char ItemType; char Reserved; uint16_t ItemLen;
    this->itemheadlength = sizeof(ItemHead::ItemType) + sizeof(ItemHead::Reserved) + sizeof(ItemHead::ItemLen);

    InitAssociateRQPDU(associaterqpdu, callingae, calledae, abstractsyntax);
    this->associateRQPDU = associaterqpdu;
}

AssociateRQ::~AssociateRQ()
{
}

int AssociateRQ::SendAssociateRQ(string ip, int port)
{
    AssociateRQDUL associateRQDUL(ip, port);
    // return associateRQDUL.DUL_sendAssociateRQ(this->associateRQPDU);
    int conn = associateRQDUL.DUL_sendAssociateRQ(this->associateRQPDU);
    return conn;
}

void AssociateRQ::InitAssociateRQPDU(AssociateRQPDU *associaterqpdu, string callingae, string calledae, string abstractsyntax)
{
    InitDefaultAssociateRQPDU(associaterqpdu, abstractsyntax);

    //leading and trailing spaces (20H) being non-significant(part 8, 9.3.2)
    memset(associaterqpdu->CallingAE, 0x20, sizeof(associaterqpdu->CallingAE));
    memcpy(associaterqpdu->CallingAE, callingae.c_str(), callingae.size());
    memset(associaterqpdu->CalledAE, 0x20, sizeof(associaterqpdu->CalledAE));
    memcpy(associaterqpdu->CalledAE, calledae.c_str(), calledae.size());
}

void AssociateRQ::InitDefaultAssociateRQPDU(AssociateRQPDU *associaterqpdu, string abstractsyntax)
{
    //init PUD Head
    associaterqpdu->pduHead.PduType = 0x01;
    associaterqpdu->pduHead.Reserved = 0x00;
    
    //两字节,只能用bit 0表示
    associaterqpdu->ProtocolVersion = 0x01;
    associaterqpdu->Reserved1 = 0x00;
    memset(associaterqpdu->CalledAE,0, sizeof(associaterqpdu->CalledAE));
    memset(associaterqpdu->CallingAE,0, sizeof(associaterqpdu->CallingAE));
    memset(associaterqpdu->Reserved2, 0, sizeof(associaterqpdu->Reserved2));

    associaterqpdu->applicationContexItem = InitApplicationContextItem();
    associaterqpdu->presentationContextItemlist.push_back(InitPresentationContextItem(abstractsyntax));
    associaterqpdu->userInfoItem = InitUserInfoItem(10000);

    uint16_t applicationcontexitemlen = associaterqpdu->applicationContexItem.itemHead.ItemLen + itemheadlength;
    uint16_t presentationcontextitemlen = 0;
    for(int i=0; i<associaterqpdu->presentationContextItemlist.size(); i++)
    {
        presentationcontextitemlen += associaterqpdu->presentationContextItemlist[i].itemHead.ItemLen + itemheadlength;
    }
    uint16_t userinfoitemlen = associaterqpdu->userInfoItem.itemHead.ItemLen + itemheadlength;

    associaterqpdu->pduHead.PduLen =  sizeof(associaterqpdu->ProtocolVersion) + 
                                      sizeof(associaterqpdu->Reserved1) + 
                                      sizeof(associaterqpdu->CalledAE) + 
                                      sizeof(associaterqpdu->CallingAE) + 
                                      sizeof(associaterqpdu->Reserved2) + 
                                      applicationcontexitemlen + 
                                      presentationcontextitemlen + 
                                      userinfoitemlen;
}

ApplicationContexItem AssociateRQ::InitApplicationContextItem()
{
    //固定不变
    ApplicationContexItem applicationcontexitem;

    applicationcontexitem.itemHead.ItemType = 0x10;
    applicationcontexitem.itemHead.Reserved = 0x00;

    applicationcontexitem.AppicationContextName = new unsigned char[sizeof("1.2.840.10008.3.1.1.1")];
    memcpy(applicationcontexitem.AppicationContextName, "1.2.840.10008.3.1.1.1", sizeof("1.2.840.10008.3.1.1.1"));
    applicationcontexitem.itemHead.ItemLen = sizeof("1.2.840.10008.3.1.1.1");

    return applicationcontexitem;
}

PresentationContextItem AssociateRQ::InitPresentationContextItem(string abstractsyntax)
{
    //可变条目
    PresentationContextItem presentationcontextitem;

    presentationcontextitem.itemHead.ItemType = 0x20;
    presentationcontextitem.itemHead.Reserved = 0x00;

    int index = -1;
    presentationcontextitem.PresentationContextID = index + 2;
    memset(presentationcontextitem.Reserved, 0, sizeof(presentationcontextitem.Reserved));
    
    NegotiationSyntaxItem negotiationsyntaxitem;
    negotiationsyntaxitem.abstractSyntax = InitAbstractSyntax(abstractsyntax);
    negotiationsyntaxitem.transferSyntaxlist.push_back(InitTransferSyntax(ImplicitVRLittleEndian));
    presentationcontextitem.negotiationSyntaxItem = negotiationsyntaxitem;

    int length = sizeof(presentationcontextitem.PresentationContextID) + sizeof(presentationcontextitem.Reserved);
    int abstractsyntaxitemlen = presentationcontextitem.negotiationSyntaxItem.abstractSyntax.itemHead.ItemLen + itemheadlength;
    length += abstractsyntaxitemlen;

    for(int j = 0;j < presentationcontextitem.negotiationSyntaxItem.transferSyntaxlist.size();j++)
    {
        int  transfersyntaxitemlen = presentationcontextitem.negotiationSyntaxItem.transferSyntaxlist[j].itemHead.ItemLen + itemheadlength;
        length += transfersyntaxitemlen;
    }

    presentationcontextitem.itemHead.ItemLen = length;

    return presentationcontextitem;
}

UserInfoItem AssociateRQ::InitUserInfoItem(uint32_t maximumLength)
{
    UserInfoItem userinfoitem;

    userinfoitem.itemHead.ItemType = 0x50;
    userinfoitem.itemHead.Reserved = 0x00;

    userinfoitem.maxLenItem = InitMaximumLength(maximumLength);
    int maxlenitemlen = userinfoitem.maxLenItem.itemHead.ItemLen + itemheadlength;

    userinfoitem.itemHead.ItemLen = maxlenitemlen;

    return userinfoitem;
}

SyntaxItem AssociateRQ::InitAbstractSyntax(string abstractSyntax)
{
    SyntaxItem abstractsyntax;
    abstractsyntax.itemHead.ItemType = 0x30;
    abstractsyntax.itemHead.Reserved = 0x00;

    abstractsyntax.Syntax = new unsigned char[abstractSyntax.size()];
    memcpy(abstractsyntax.Syntax, abstractSyntax.c_str(), abstractSyntax.size());
    abstractsyntax.itemHead.ItemLen = abstractSyntax.size();

    return abstractsyntax;
}

SyntaxItem AssociateRQ::InitTransferSyntax(string transferSyntax)
{
    SyntaxItem transfersyntax;

    transfersyntax.itemHead.ItemType = 0x40;
    transfersyntax.itemHead.Reserved = 0x00;

    transfersyntax.Syntax = new unsigned char[transferSyntax.size()];
    memcpy(transfersyntax.Syntax, transferSyntax.c_str(), transferSyntax.size());
    transfersyntax.itemHead.ItemLen = transferSyntax.size();

    return transfersyntax;
}

MaximumLengthItem AssociateRQ::InitMaximumLength(uint32_t maximumLength)
{
    MaximumLengthItem maximumlength;
    maximumlength.itemHead.ItemType = 0x51;
    maximumlength.itemHead.Reserved = 0x00;
    maximumlength.itemHead.ItemLen = 4;

    maximumlength.MaxLenReceived = maximumLength;

    return maximumlength;
}