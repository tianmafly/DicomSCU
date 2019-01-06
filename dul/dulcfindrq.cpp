#include "dulcfindrq.h"
#include "../socket/socket.h"



CFindeRQPDU::CFindeRQPDU(PDataTFPDU *pdatatf)
{
    index = 0;
    this->pdatatf = pdatatf;
    pdatatflen = pdatatf->headItem.pduLen + sizeof(pdatatf->headItem.pduLen) + sizeof(pdatatf->headItem.reserve) + sizeof(pdatatf->headItem.pduType);
    buffer = new unsigned char[pdatatflen];

    DUL_GetCFindRQPDU();
}

CFindeRQPDU::~CFindeRQPDU()
{
    delete buffer;
    buffer = NULL;
}

void CFindeRQPDU::DUL_SendCFindRQ(int conn)
{
    TcpSocket tcpSocket;
    tcpSocket.Send(conn, buffer, pdatatflen);

}

void CFindeRQPDU::DUL_GetCFindRQPDU()
{
    DUL_GetBufferFromPoint(&(pdatatf->headItem.pduType), sizeof(pdatatf->headItem.pduType));
    DUL_GetBufferFromPoint(&(pdatatf->headItem.reserve), sizeof(pdatatf->headItem.reserve));
    DUL_GetBufferFromPoint((const unsigned char*)&(pdatatf->headItem.pduLen), sizeof(pdatatf->headItem.pduLen));

    DUL_GetPresentationDataValueItem();
}

void CFindeRQPDU::DUL_GetPresentationDataValueItem()
{
    for(int i=0; i< pdatatf->presentationDataValueItemList.size(); i++)
    {
        DUL_GetBufferFromPoint((const unsigned char *)&(pdatatf->presentationDataValueItemList[i].itemLen), sizeof(pdatatf->presentationDataValueItemList[i].itemLen));
        DUL_GetBufferFromPoint(&(pdatatf->presentationDataValueItemList[i].presentationID), sizeof(pdatatf->presentationDataValueItemList[i].presentationID));
        DUL_GetPresentationDataValue(&(pdatatf->presentationDataValueItemList[i].presentationDataValue);
    }
}

void CFindeRQPDU::DUL_GetPresentationDataValue(PresentationDataValue *presentationDataValue)
{
    DUL_GetBufferFromPoint(&(presentationDataValue->messageControlHeader), sizeof(presentationDataValue->messageControlHeader));

    for(int i=0; i<presentationDataValue->messageCommandOrDataSetFragment.size(); i++)
    {
        DUL_GetBuffFromDcmElement(&(presentationDataValue->messageCommandOrDataSetFragment[i]));
    }
}

void CFindeRQPDU::DUL_GetBuffFromDcmElement(DcmElement *dcmelement)
{
    DUL_GetBufferFromPoint(dcmelement->tag, sizeof(dcmelement->tag));
    DUL_GetBufferFromPoint(dcmelement->vr.data, dcmelement->vr.len);
    DUL_GetBufferFromPoint(dcmelement->datalen.data, dcmelement->datalen.len);
    DUL_GetBufferFromPoint(dcmelement->data.data, sizeof(dcmelement->data.len));
}

void CFindeRQPDU::DUL_GetBufferFromPoint(const unsigned char *data, int len)
{
    memcpy(buffer + index, data, len);
    index += len;
}

void  CFindeRQPDU::DUL_GetBufferFromInt(int data, int len)
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