#ifndef DULCFINDRSP_H
#define DULCFINDRSP_H

#include "../pdu/pdupdatatf.h"
#include "../socket/socket.h"
#include "../type/commontype.h"

using namespace PDUPDataTF_namespace;

class CFindRSPDUL
{
private:
    /* data */
public:
    CFindRSPDUL(int conn, string transfersyntax);
    ~CFindRSPDUL();
public:
    PDataTFPDU * DUL_ReceiveCFindRSP();
private:
    void DUL_GetPDataTFHead(HeadItem *headitem);
    void DUL_GetPDataTFBody(vector<PresentationDataValueItem> *presentationdatavalueitemlist, uint32_t itemlistlen);
    uint32_t DUL_GetPresentationDataValueItem(PresentationDataValueItem *presentationdatavalueitem);
    void DUL_GetPresentationDataValue(PresentationDataValue *presentationdatavalue, uint32_t presentationdatavaluelen);
    void DUL_GetmessageCommandOrDataSetFragment(vector<DcmElement> *dcmelementlist, uint32_t dcmelementlistlen);

    void DUL_BigToLittel(unsigned char * bufferbig, int bufferlen);
    void DUL_GetPointFromBuffer(unsigned char *data, int len);
    void DUL_GetIntFromBuffer(uint16_t *data, int len);
    void DUL_GetIntFromBuffer(uint32_t *data, int len);

    DcmElement DUL_GetDcmElement();
    void InitDcmElementModel(string transfersyntax);
    void Init();
private:
    TcpSocket *tcpSocket;
    int conn;
    unsigned char *pdubody;
    int index;
    string transferSyntax;
    uint32_t vrBytes;
    uint32_t LengthBytes;
    bool isPDUProtocolHead;
};










#endif // !DULCFINDRSP_H
