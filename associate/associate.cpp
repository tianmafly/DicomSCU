#include "associate.h"
#include <stdio.h>
#include <string.h>
#include "../type/uid.h"


Associate::Associate(/* args */)
{
}

Associate::~Associate()
{   
}

void Associate::SendAssociate()
{

}

void Associate::ReceiveAssociate()
{

}

void Associate::InitAssociationRQPDU(AssociateRQPDU *associateRQPDU)
{
    //init PUD Head
    associateRQPDU->pduHead.PduType = 0x01;
    associateRQPDU->pduHead.Reserved = 0x00;
    associateRQPDU->pduHead.PduLen;

    //两字节,只能用bit 0表示
    associateRQPDU->ProtocolVersion[0] = 0x01;
    associateRQPDU->ProtocolVersion[1] = 0x00;
    memset(associateRQPDU->Reserved1, 0x00, sizeof(associateRQPDU->Reserved1));
    memset(associateRQPDU->Reserved2, 0x00, sizeof(associateRQPDU->Reserved2));
    
    //init Variable Items
    //init ApplicationContextItem
    associateRQPDU->applicationContexItem.itemHead.ItemType = 0x10;
    associateRQPDU->applicationContexItem.itemHead.Reserved = 0x00;
    associateRQPDU->applicationContexItem.AppicationContextName = "1.2.840.10008.3.1.1.1";
    associateRQPDU->applicationContexItem.itemHead.ItemLen = associateRQPDU->applicationContexItem.AppicationContextName.size();

    //init PresentationContextItem
    associateRQPDU->presentationContextItem.itemHead.ItemType = 0x20;
    associateRQPDU->presentationContextItem.itemHead.Reserved = 0x00;

    int index = -1;
    associateRQPDU->presentationContextItem.PresentationContextID = index + 2;
    memset(associateRQPDU->presentationContextItem.Reserved, 0, sizeof(associateRQPDU->presentationContextItem.Reserved));
    
    NegotiationSyntaxItem negotiationsyntaxitem;
    negotiationsyntaxitem.abstractSyntax.itemHead.ItemType = 0x30;
    negotiationsyntaxitem.abstractSyntax.itemHead.Reserved = 0x00;
    negotiationsyntaxitem.abstractSyntax.Syntax = StudyRoot_QueryRetrieveInformationModel_FIND;
    negotiationsyntaxitem.abstractSyntax.itemHead.ItemLen = negotiationsyntaxitem.abstractSyntax.Syntax.size();

    SyntaxItem transferSyntax;
    transferSyntax.itemHead.ItemType = 0x40;
    transferSyntax.itemHead.Reserved = 0x00;
    transferSyntax.Syntax = ImplicitVRLittleEndian;
    transferSyntax.itemHead.ItemLen = transferSyntax.Syntax.size();

    negotiationsyntaxitem.transferSyntaxlist.push_back(transferSyntax);

    associateRQPDU->presentationContextItem.negotiationSyntaxItem.push_back(negotiationsyntaxitem);
    

    associateRQPDU->userInfoItem.itemHead.ItemType = 0x50;
    associateRQPDU->userInfoItem.itemHead.Reserved = 0x00;
    associateRQPDU->presentationContextItem.itemHead.ItemLen ;


}