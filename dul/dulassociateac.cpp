#include "dulassociateac.h"
#include <string.h>

AssociateACDUL::AssociateACDUL(int conn)
{
    index = 0;
    pdubody = NULL;
    tcpSocket = new TcpSocket();
    this->conn = conn;
}

AssociateACDUL::~AssociateACDUL()
{
    delete tcpSocket;
    tcpSocket = NULL;

    delete pdubody;
    pdubody = NULL;
}

void AssociateACDUL::DUL_ReceiveAssociateAC(AssociateACPDU *associateacpdu)
{
    unsigned char pduhead[6];
    memset(pduhead, 0, sizeof(pduhead));
    tcpSocket->Reveive(this->conn, pduhead, sizeof(pduhead));
    DUL_GetAssociateACPUDHead(associateacpdu, pduhead);

    pdubody = new unsigned char[associateacpdu->pduHead.PduLen];
    memset(pdubody, 0, associateacpdu->pduHead.PduLen);
    tcpSocket->Reveive(this->conn, pdubody, associateacpdu->pduHead.PduLen);
    DUL_GetAssociateRQBodyPUD(associateacpdu);
}

void AssociateACDUL::DUL_GetAssociateACPUDHead(AssociateACPDU *associateacpdu,  unsigned char *pduhead)
{
    associateacpdu->pduHead.PduType = pduhead[0];
    associateacpdu->pduHead.Reserved = pduhead[1];
    associateacpdu->pduHead.PduLen = pduhead[2] << 24 | pduhead[3] << 16 | pduhead[4] << 8 | pduhead[5];
}

 void AssociateACDUL::DUL_GetAssociateRQBodyPUD(AssociateACPDU *associateacpdu)
 {
    DUL_GetIntFromBuffer(&(associateacpdu->ProtocolVersion), sizeof(associateacpdu->ProtocolVersion));
    DUL_GetPointFromBuffer(associateacpdu->Reserved1, sizeof(associateacpdu->Reserved1));
    DUL_GetPointFromBuffer(associateacpdu->Reserved2, sizeof(associateacpdu->Reserved2));
    DUL_GetPointFromBuffer(associateacpdu->Reserved3, sizeof(associateacpdu->Reserved3));
    DUL_GetPointFromBuffer(associateacpdu->Reserved4, sizeof(associateacpdu->Reserved4));

    DUL_GetApplicationContexItem(&(associateacpdu->applicationContexItem));
    
    while(true)
    {
        if(pdubody[index] == 0x50)
            break;

        PresentationContextItem presentationContextItem;
        DUL_GetPresentationContextItem(&presentationContextItem);
        associateacpdu->presentationContextItemlist.push_back(presentationContextItem);
    }
    
    DUL_GetUserInfoItemItem(&(associateacpdu->userInfoItem));
 }

void AssociateACDUL::DUL_GetApplicationContexItem(ApplicationContexItem *applicationcontexitem)
{
    DUL_GetItemHead(&(applicationcontexitem->itemHead));

    applicationcontexitem->AppicationContextName = new unsigned char[applicationcontexitem->itemHead.ItemLen];
    DUL_GetPointFromBuffer(applicationcontexitem->AppicationContextName, applicationcontexitem->itemHead.ItemLen);
}

void AssociateACDUL::DUL_GetPresentationContextItem(PresentationContextItem *presentationcontextitem)
{
    DUL_GetItemHead(&(presentationcontextitem->itemHead));

    DUL_GetPointFromBuffer(&(presentationcontextitem->PresentationContextID), sizeof(presentationcontextitem->PresentationContextID));
    DUL_GetPointFromBuffer(&(presentationcontextitem->Reserved1), sizeof(presentationcontextitem->Reserved1));
    DUL_GetPointFromBuffer(&(presentationcontextitem->Result), sizeof(presentationcontextitem->Result));
    DUL_GetPointFromBuffer(&(presentationcontextitem->Reserved2), sizeof(presentationcontextitem->Reserved2));

    DUL_GetTransferSyntax(&(presentationcontextitem->transferSyntax));
}

void AssociateACDUL::DUL_GetUserInfoItemItem(UserInfoItem *userinfoitem)
{
    DUL_GetItemHead(&(userinfoitem->itemHead));

    DUL_GetMaximumLengthItem(&(userinfoitem->maxLenItem));
}

void AssociateACDUL::DUL_GetTransferSyntax(SyntaxItem *transfersyntaxitem)
{
    DUL_GetItemHead(&(transfersyntaxitem->itemHead));

    transfersyntaxitem->Syntax = new unsigned char[transfersyntaxitem->itemHead.ItemLen];
    DUL_GetPointFromBuffer(transfersyntaxitem->Syntax, transfersyntaxitem->itemHead.ItemLen);
}

void AssociateACDUL::DUL_GetMaximumLengthItem(MaximumLengthItem *maximumlengthitem)
{
    DUL_GetItemHead(&(maximumlengthitem->itemHead));

    DUL_GetIntFromBuffer(&(maximumlengthitem->MaxLenReceived), maximumlengthitem->itemHead.ItemLen);
}

void AssociateACDUL::DUL_GetItemHead(ItemHead * itemhead)
{
    DUL_GetPointFromBuffer(&(itemhead->ItemType), sizeof(itemhead->ItemType));
    DUL_GetPointFromBuffer(&(itemhead->Reserved), sizeof(itemhead->Reserved));
    DUL_GetIntFromBuffer(&(itemhead->ItemLen), sizeof(itemhead->ItemLen));
}

void AssociateACDUL::DUL_GetPointFromBuffer(unsigned char *data, int len)
{
    memcpy(data, pdubody+index, len);
    index += len;
}

void AssociateACDUL::DUL_GetIntFromBuffer(uint16_t *data, int len)
{
    *data = 0;
    for(int i=0; i<len; i++)
    {
        *data |= (pdubody[index] << (8 * ((len - 1) - i)));
        index++;
    }
}

void AssociateACDUL::DUL_GetIntFromBuffer(uint32_t *data, int len)
{
    *data = 0;
    for(int i=0; i<len; i++)
    {
        *data |= (pdubody[index] << (8 * ((len - 1) - i)));
        index++;
    }
}