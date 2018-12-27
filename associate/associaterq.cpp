#include "associaterq.h"
#include <string.h>
#include "../type/uid.h"


AssociateRQ::AssociateRQ(/* args */)
{
}

AssociateRQ::~AssociateRQ()
{
}

void AssociateRQ::InitAssociateRQPDU(AssociateRQPDU *associateRQPDU)
{

}

ApplicationContexItem AssociateRQ::InitApplicationContextItem()
{
    //固定不变
    ApplicationContexItem applicationcontexitem;

    applicationcontexitem.itemHead.ItemType = 0x10;
    applicationcontexitem.itemHead.Reserved = 0x00;
    applicationcontexitem.AppicationContextName = "1.2.840.10008.3.1.1.1";
    applicationcontexitem.itemHead.ItemLen = applicationcontexitem.AppicationContextName.size();

    return applicationcontexitem;
}

PresentationContextItem AssociateRQ::InitPresentationContextItem()
{
    //可变条目
    PresentationContextItem presentationcontextitem;

    presentationcontextitem.itemHead.ItemType = 0x20;
    presentationcontextitem.itemHead.Reserved = 0x00;

    int index = -1;
    presentationcontextitem.PresentationContextID = index + 2;
    memset(presentationcontextitem.Reserved, 0, sizeof(presentationcontextitem.Reserved));
    
    NegotiationSyntaxItem negotiationsyntaxitem;
    negotiationsyntaxitem.abstractSyntax = InitAbstractSyntax(StudyRoot_QueryRetrieveInformationModel_FIND);
    negotiationsyntaxitem.transferSyntaxlist.push_back(InitTransferSyntax(ImplicitVRLittleEndian));
    presentationcontextitem.negotiationSyntaxItem.push_back(negotiationsyntaxitem);

    int length = 0;
    for(int i = 0;i < presentationcontextitem.negotiationSyntaxItem.size();i++)
    {
        int abstractsyntaxlen = presentationcontextitem.negotiationSyntaxItem[i].abstractSyntax.itemHead.ItemLen + 1 + 1 + 2;
        length += abstractsyntaxlen;

        for(int j = 0;j < length;j++)
        {
            int  transfersyntaxlen = presentationcontextitem.negotiationSyntaxItem[i].transferSyntaxlist[j].itemHead.ItemLen + 1 + 1 + 2;
            length += transfersyntaxlen;
        }
        
    }

    presentationcontextitem.itemHead.ItemLen = length;
}

UserInfoItem AssociateRQ::InitUserInfoItem()
{

}

SyntaxItem AssociateRQ::InitAbstractSyntax(string abstractSyntax)
{
    SyntaxItem abstractsyntax;
    abstractsyntax.itemHead.ItemType = 0x30;
    abstractsyntax.itemHead.Reserved = 0x00;
    abstractsyntax.Syntax = abstractSyntax;
    abstractsyntax.itemHead.ItemLen = abstractsyntax.Syntax.size();

    return abstractsyntax;
}

SyntaxItem AssociateRQ::InitTransferSyntax(string transferSyntax)
{
    SyntaxItem transfersyntax;

    transfersyntax.itemHead.ItemType = 0x40;
    transfersyntax.itemHead.Reserved = 0x00;
    transfersyntax.Syntax = transferSyntax;
    transfersyntax.itemHead.ItemLen = transfersyntax.Syntax.size();

    return transfersyntax;
}