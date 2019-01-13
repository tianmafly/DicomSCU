#include "dulcfindrsp.h"
#include "../type/uid.h"
#include <stdio.h>
#include <unistd.h>


CFindRSPDUL::CFindRSPDUL(int conn, string transfersyntax)
{
    tcpSocket = new TcpSocket();
    this->conn = conn;
    

    transferSyntax = transfersyntax;
    InitDcmElementModel(transferSyntax);
    Init();
}

CFindRSPDUL::~CFindRSPDUL()
{
    delete tcpSocket;
    tcpSocket = NULL;
}

void CFindRSPDUL::Init()
{
    // PDUProtocolHead is big model
    isPDUProtocolHead = true;
    index = 0;
    pdubody = NULL;
}

void CFindRSPDUL::InitDcmElementModel(string transfersyntax)
{
    if(transfersyntax == ImplicitVRLittleEndian)
    {
        vrBytes = ImplicitDataElementVRLength;
        LengthBytes = ImplicitDataElementValueLength;
    }
    else if(transfersyntax == ExplicitVRLittleEndian || transfersyntax == ExplicitVRBigEndian)
    {
        vrBytes = EmplicitDataElementVRLength;
        LengthBytes = EmplicitDataElementValueLength;
    }
    else
    {
        vrBytes = 0;
        LengthBytes = 0;
    }
}

PDataTFPDU * CFindRSPDUL::DUL_ReceiveCFindRSP()
{
    Init();
    PDataTFPDU *pDataTFPDU = new PDataTFPDU();
    DUL_GetPDataTFHead(&(pDataTFPDU->headItem));
    DUL_GetPDataTFBody(&(pDataTFPDU->presentationDataValueItemList), pDataTFPDU->headItem.pduLen);

    return pDataTFPDU;
}

void CFindRSPDUL::DUL_GetPDataTFHead(HeadItem *headitem)
{
    isPDUProtocolHead = true;
    unsigned char pduhead[6];
    memset(pduhead, 0, sizeof(pduhead));
    tcpSocket->Reveive(this->conn, pduhead, sizeof(pduhead));
    
    headitem->pduType = pduhead[0];
    headitem->reserve = pduhead[1];
    DUL_BigToLittel(pduhead + 2, sizeof(pduhead) - 2);
    memcpy(&(headitem->pduLen), pduhead + 2, sizeof(headitem->pduLen));

    pdubody = new unsigned char[headitem->pduLen];
    memset(pdubody, 0,  headitem->pduLen);
    sleep(1);
    tcpSocket->Reveive(this->conn, pdubody, headitem->pduLen);
    printf("........................\n");
    for(int i=0; i< headitem->pduLen; i++)
    {
        printf("%X: %d\n", pdubody[i],i);
    }
}

void CFindRSPDUL::DUL_GetPDataTFBody(vector<PresentationDataValueItem> *presentationdatavalueitemlist, uint32_t itemlistlen)
{
    uint32_t itemlen = 0;
    for(int i=0; i< itemlistlen; i=itemlen)
    {
        PresentationDataValueItem presentationdatavalueitem;
        
        itemlen += DUL_GetPresentationDataValueItem(&presentationdatavalueitem);
        presentationdatavalueitemlist->push_back(presentationdatavalueitem);
    }
}

uint32_t CFindRSPDUL::DUL_GetPresentationDataValueItem(PresentationDataValueItem *presentationdatavalueitem)
{
    DUL_GetIntFromBuffer(&(presentationdatavalueitem->itemLen), sizeof(presentationdatavalueitem->itemLen));
    DUL_GetPointFromBuffer(&(presentationdatavalueitem->presentationID), sizeof(presentationdatavalueitem->presentationID));

    DUL_GetPresentationDataValue(&(presentationdatavalueitem->presentationDataValue), presentationdatavalueitem->itemLen - sizeof(presentationdatavalueitem->presentationID));

    return presentationdatavalueitem->itemLen + sizeof(presentationdatavalueitem->itemLen);
}

void CFindRSPDUL::DUL_GetPresentationDataValue(PresentationDataValue *presentationdatavalue, uint32_t presentationdatavaluelen)
{
    DUL_GetPointFromBuffer(&(presentationdatavalue->messageControlHeader), sizeof(presentationdatavalue->messageControlHeader));

    DUL_GetmessageCommandOrDataSetFragment(&(presentationdatavalue->messageCommandOrDataSetFragment), presentationdatavaluelen - sizeof(presentationdatavalue->messageControlHeader));
}

void CFindRSPDUL::DUL_GetmessageCommandOrDataSetFragment(vector<DcmElement*> *dcmelementlist, uint32_t dcmelementlistlen)
{
    // PDV's command is implicitlittel model
    isPDUProtocolHead = false;
    int dcmelementlen = 0;
    for(int i=0; i<dcmelementlistlen; i=dcmelementlen)
    {
        DcmElement *dcmelement = DUL_GetDcmElement();
        dcmelementlist->push_back(dcmelement);
        dcmelementlen += DcmElementHandle().GetDcmElementLen(dcmelement);
    }
}

DcmElement *CFindRSPDUL::DUL_GetDcmElement()
{
    DcmElement *dcmelement = new DcmElement();
    DUL_GetPointFromBuffer(dcmelement->tag, sizeof(dcmelement->tag));

    dcmelement->vr.len = vrBytes;
    dcmelement->vr.data = new unsigned char[dcmelement->vr.len];
    DUL_GetPointFromBuffer(dcmelement->vr.data, dcmelement->vr.len);

    dcmelement->datalen.len = LengthBytes;
    dcmelement->datalen.data = new unsigned char[dcmelement->datalen.len];
    DUL_GetPointFromBuffer(dcmelement->datalen.data, dcmelement->datalen.len);

    memcpy(&(dcmelement->data.len), dcmelement->datalen.data, dcmelement->datalen.len);
    dcmelement->data.data = new unsigned char[dcmelement->data.len];
    DUL_GetPointFromBuffer(dcmelement->data.data, dcmelement->data.len);

    return dcmelement;
}

void CFindRSPDUL::DUL_GetPointFromBuffer(unsigned char *data, int len)
{
    if(len == 0)
        return;

    memcpy(data, pdubody+index, len);
    if(len > 1 && (transferSyntax == ExplicitVRBigEndian || isPDUProtocolHead))
    {
        DUL_BigToLittel(data, len);
    }
    
    index += len;
}

void CFindRSPDUL::DUL_GetIntFromBuffer(uint16_t *data, int len)
{
    *data = 0;
    DUL_GetPointFromBuffer((unsigned char *)data, len);
    // for(int i=0; i<len; i++)
    // {
    //     *data |= (pdubody[index] << (8 * ((len - 1) - i)));
    //     index++;
    // }
}

void CFindRSPDUL::DUL_GetIntFromBuffer(uint32_t *data, int len)
{
    *data = 0;
    DUL_GetPointFromBuffer((unsigned char *)data, len);
    // for(int i=0; i<len; i++)
    // {
    //     *data |= (pdubody[index] << (8 * ((len - 1) - i)));
    //     index++;
    // }
}

void CFindRSPDUL::DUL_BigToLittel(unsigned char * bufferbig, int bufferlen)
{
    unsigned char bufferlittel[bufferlen];
    for(int i=0; i< bufferlen; i++)
    {
        bufferlittel[i] = bufferbig[bufferlen - 1 - i];
    }

    memcpy(bufferbig, bufferlittel, bufferlen);
}