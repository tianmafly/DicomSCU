#include "dulpdatatfrq.h"
#include "../socket/socket.h"



PDataTfRQDUL::PDataTfRQDUL(PDataTFPDU *pdatatf)
{
    index = 0;
    this->pdatatf = pdatatf;
    pdatatflen = pdatatf->headItem.pduLen + sizeof(pdatatf->headItem.pduLen) + sizeof(pdatatf->headItem.reserve) + sizeof(pdatatf->headItem.pduType);
    buffer = new unsigned char[pdatatflen];

    DUL_GetPDataTfPDUMemory();
}

PDataTfRQDUL::~PDataTfRQDUL()
{
    delete buffer;
    buffer = NULL;
}

void PDataTfRQDUL::DUL_SendPDataTfPDU(int conn)
{
    TcpSocket tcpSocket;
    tcpSocket.Send(conn, buffer, pdatatflen);
    for(int i=0; i<pdatatflen; i++)
    {
        printf("%x,%d\n", buffer[i], i);
    }
}

void PDataTfRQDUL::DUL_GetPDataTfPDUMemory()
{
    DUL_GetBufferFromPoint(&(pdatatf->headItem.pduType), sizeof(pdatatf->headItem.pduType));
    DUL_GetBufferFromPoint(&(pdatatf->headItem.reserve), sizeof(pdatatf->headItem.reserve));
    DUL_GetBufferFromInt(pdatatf->headItem.pduLen, sizeof(pdatatf->headItem.pduLen));

    DUL_GetPresentationDataValueItemMemory();
}

void PDataTfRQDUL::DUL_GetPresentationDataValueItemMemory()
{
    for(int i=0; i< pdatatf->presentationDataValueItemList.size(); i++)
    {
        DUL_GetBufferFromInt(pdatatf->presentationDataValueItemList[i].itemLen, sizeof(pdatatf->presentationDataValueItemList[i].itemLen));
        DUL_GetBufferFromPoint(&(pdatatf->presentationDataValueItemList[i].presentationID), sizeof(pdatatf->presentationDataValueItemList[i].presentationID));
        DUL_GetPresentationDataValueMemory(&(pdatatf->presentationDataValueItemList[i].presentationDataValue));
    }
}

void PDataTfRQDUL::DUL_GetPresentationDataValueMemory(PresentationDataValue *presentationDataValue)
{
    DUL_GetBufferFromPoint(&(presentationDataValue->messageControlHeader), sizeof(presentationDataValue->messageControlHeader));

    for(int i=0; i<presentationDataValue->messageCommandOrDataSetFragment.size(); i++)
    {
        DUL_GetBuffFromDcmElement(presentationDataValue->messageCommandOrDataSetFragment[i]);
    }
}

void PDataTfRQDUL::DUL_GetBuffFromDcmElement(DcmElement *dcmelement)
{
    DUL_GetBufferFromPoint(dcmelement->tag, sizeof(dcmelement->tag));
    DUL_GetBufferFromPoint(dcmelement->vr.data, dcmelement->vr.len);
    DUL_GetBufferFromPoint(dcmelement->datalen.data, dcmelement->datalen.len);
    DUL_GetBufferFromPoint(dcmelement->data.data, dcmelement->data.len);
}

void PDataTfRQDUL::DUL_GetBufferFromPoint(const unsigned char *data, int len)
{
    memcpy(buffer + index, data, len);
    index += len;
}

void  PDataTfRQDUL::DUL_GetBufferFromInt(int data, int len)
{
    // 大端排列,scp服务端按照长度截取,直接转换为内存中的整形值.
    int pos = len - 1;
    for(int i=0; i<len; i++)
    {
        buffer[index+pos] = (data & 0xFF);
        data = data >> 8;
        pos--;
    }
    index += len;
}