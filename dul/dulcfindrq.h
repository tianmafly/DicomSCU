#ifndef DULCFINDRQ_H
#define DULCFINDRQ_H
#include "../pdu/pdupdatatf.h"
using namespace PDUPDataTF_namespace;

class CFindeRQPDU
{
private:
    
public:
    CFindeRQPDU(PDataTFPDU *pdatatf);
    ~CFindeRQPDU();
public:
    void DUL_SendCFindRQ(int conn);

private:
    void DUL_GetCFindRQPDU();
    void DUL_GetPresentationDataValueItem();
    void DUL_GetPresentationDataValue(PresentationDataValue *presentationDataValue);
    void DUL_GetBuffFromDcmElement(DcmElement *dcmelement);
    void DUL_GetBufferFromPoint(const unsigned char *data, int len);
    void DUL_GetBufferFromInt(int data, int len);

private:
    int index;
    PDataTFPDU *pdatatf;
    unsigned char *buffer;
    int pdatatflen;
};
























#endif // !DULCFINDRQ_H