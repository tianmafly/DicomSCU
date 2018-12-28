#include "dul.h"
#include <string.h>


AssociateRQDUL::AssociateRQDUL(string ip, int port)
{
    index = 0;
    char * buffer = NULL;

    tcpSocket = new TcpSocket();
    conn = tcpSocket->Connet(ip, port);
}

AssociateRQDUL::~AssociateRQDUL()
{
    delete tcpSocket;
    tcpSocket = NULL;

    delete buffer;
    buffer = NULL;
}

void AssociateRQDUL::DUL_sendAssociateRQ(AssociateRQPDU *associaterqpdu)
{
    char *buffer = DUL_GetAssociateRQPUDMemory(associaterqpdu);
    tcpSocket->Send(conn, buffer);
}

void AssociateRQDUL::DUL_ReceiveAssociateAC()
{

}

char * AssociateRQDUL::DUL_GetAssociateRQPUDMemory(AssociateRQPDU *associaterqpdu)
{
    int32_t associaterqpudheadlen = sizeof(associaterqpdu->pduHead.PduType) + sizeof(associaterqpdu->pduHead.Reserved) + sizeof(associaterqpdu->pduHead.PduLen);
    int32_t associaterqpudlen = associaterqpudheadlen + associaterqpdu->pduHead.PduLen;
    char *buffer = new char[associaterqpudlen];

    //pdu head
    buffer[index] = associaterqpdu->pduHead.PduType;

    DUL_GetBuffer(&(associaterqpdu->pduHead.PduType), sizeof(associaterqpdu->pduHead.PduType));
    DUL_GetBuffer(&(associaterqpdu->pduHead.Reserved), sizeof(associaterqpdu->pduHead.Reserved));
    DUL_GetBuffer((char*)(associaterqpdu->pduHead.PduLen), sizeof(associaterqpdu->pduHead.PduLen));

    DUL_GetBuffer((char*)(associaterqpdu->ProtocolVersion), sizeof(associaterqpdu->ProtocolVersion));
    DUL_GetBuffer((char*)(associaterqpdu->Reserved1), sizeof(associaterqpdu->Reserved1));
    DUL_GetBuffer(associaterqpdu->CalledAE, sizeof(associaterqpdu->CalledAE));
    DUL_GetBuffer(associaterqpdu->CallingAE, sizeof(associaterqpdu->CallingAE));
    DUL_GetBuffer(associaterqpdu->Reserved2, sizeof(associaterqpdu->Reserved2));

    DUL_GetApplicationContexItemMemory(&(associaterqpdu->applicationContexItem));
    DUL_GetPresentationContextItemMemory(&(associaterqpdu->presentationContextItem));
    DUL_GetUserInfoItemItemMemory(&(associaterqpdu->userInfoItem));
}

void AssociateRQDUL::DUL_GetApplicationContexItemMemory(ApplicationContexItem *applicationcontexitem)
{
    DUL_GetBuffer(&(applicationcontexitem->itemHead.ItemType), sizeof(applicationcontexitem->itemHead.ItemType));
    DUL_GetBuffer(&(applicationcontexitem->itemHead.Reserved), sizeof(applicationcontexitem->itemHead.Reserved));
    DUL_GetBuffer((char*)(applicationcontexitem->itemHead.ItemLen), sizeof(applicationcontexitem->itemHead.ItemLen));

    DUL_GetBuffer(applicationcontexitem->AppicationContextName.c_str(), sizeof(applicationcontexitem->AppicationContextName));
}

void AssociateRQDUL::DUL_GetPresentationContextItemMemory(PresentationContextItem *presentationcontextitem)
{
    DUL_GetBuffer(&(presentationcontextitem->itemHead.ItemType), sizeof(presentationcontextitem->itemHead.ItemType));
    DUL_GetBuffer(&(presentationcontextitem->itemHead.Reserved), sizeof(presentationcontextitem->itemHead.Reserved));
    DUL_GetBuffer((char*)(presentationcontextitem->itemHead.ItemLen), sizeof(presentationcontextitem->itemHead.ItemLen));

    DUL_GetBuffer((char*)(presentationcontextitem->PresentationContextID), sizeof(presentationcontextitem->PresentationContextID));
    DUL_GetBuffer(presentationcontextitem->Reserved, sizeof(presentationcontextitem->Reserved));

    for(int i = 0;i < presentationcontextitem->negotiationSyntaxItem.size();i++)
    {
        DUL_GetAbstractSyntaxMemory(&(presentationcontextitem->negotiationSyntaxItem[i].abstractSyntax));
        for(int j = 0;j < presentationcontextitem->negotiationSyntaxItem[i].transferSyntaxlist.size();j++)
        {
            DUL_GetTransferSyntaxMemory(&(presentationcontextitem->negotiationSyntaxItem[i].transferSyntaxlist[j]));
        }
    }
}

void AssociateRQDUL::DUL_GetUserInfoItemItemMemory(UserInfoItem *userinfoitem)
{
    DUL_GetBuffer(&(userinfoitem->itemHead.ItemType), sizeof(userinfoitem->itemHead.ItemType));
    DUL_GetBuffer(&(userinfoitem->itemHead.Reserved), sizeof(userinfoitem->itemHead.Reserved));
    DUL_GetBuffer((char*)(userinfoitem->itemHead.ItemLen), sizeof(userinfoitem->itemHead.ItemLen));

    DUL_GetMaximumLengthItemMemory(&(userinfoitem->maxLenItem));

}

void AssociateRQDUL::DUL_GetAbstractSyntaxMemory(SyntaxItem *abstractsyntaxitem)
{
    DUL_GetBuffer(&(abstractsyntaxitem->itemHead.ItemType), sizeof(abstractsyntaxitem->itemHead.ItemType));
    DUL_GetBuffer(&(abstractsyntaxitem->itemHead.Reserved), sizeof(abstractsyntaxitem->itemHead.Reserved));
    DUL_GetBuffer((char*)(abstractsyntaxitem->itemHead.ItemLen), sizeof(abstractsyntaxitem->itemHead.ItemLen));

    DUL_GetBuffer(abstractsyntaxitem->Syntax.c_str(), abstractsyntaxitem->Syntax.size());
}

void AssociateRQDUL::DUL_GetTransferSyntaxMemory(SyntaxItem *transfersyntaxitem)
{
    DUL_GetBuffer(&(transfersyntaxitem->itemHead.ItemType), sizeof(transfersyntaxitem->itemHead.ItemType));
    DUL_GetBuffer(&(transfersyntaxitem->itemHead.Reserved), sizeof(transfersyntaxitem->itemHead.Reserved));
    DUL_GetBuffer((char*)(transfersyntaxitem->itemHead.ItemLen), sizeof(transfersyntaxitem->itemHead.ItemLen));

    DUL_GetBuffer(transfersyntaxitem->Syntax.c_str(), transfersyntaxitem->Syntax.size());
}

void AssociateRQDUL::DUL_GetMaximumLengthItemMemory(MaximumLengthItem *maximumlengthitem)
{
    DUL_GetBuffer(&(maximumlengthitem->itemHead.ItemType), sizeof(maximumlengthitem->itemHead.ItemType));
    DUL_GetBuffer(&(maximumlengthitem->itemHead.Reserved), sizeof(maximumlengthitem->itemHead.Reserved));
    DUL_GetBuffer((char*)(maximumlengthitem->itemHead.ItemLen), sizeof(maximumlengthitem->itemHead.ItemLen));

    DUL_GetBuffer((char*)(maximumlengthitem->MaxLenReceived), sizeof(maximumlengthitem->MaxLenReceived));
}

void AssociateRQDUL::DUL_GetBuffer(const char *data, int len)
{
    memcpy(buffer + index, data, len);
    index += len;
}