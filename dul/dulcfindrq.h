#ifndef DULCFINDRQ_H
#define DULCFINDRQ_H
#include "../pdu/pdupdatatf.h"
using namespace PDUPDataTF_namespace;

class CFindeRQDUL
{
private:
    
public:
    CFindeRQDUL(PDataTFPDU *pdatatf);
    ~CFindeRQDUL();
public:
    void DUL_SendCFindRQ(int conn);

private:
    void DUL_GetCFindRQPDUMemory();
    void DUL_GetPresentationDataValueItemMemory();
    void DUL_GetPresentationDataValueMemory(PresentationDataValue *presentationDataValue);
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