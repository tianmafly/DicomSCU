#ifndef DULPDATATFRQ_H
#define DULPDATATFRQ_H
#include "../pdu/pdupdatatf.h"
using namespace PDUPDataTF_namespace;

class PDataTfRQDUL
{
private:
    
public:
    PDataTfRQDUL(PDataTFPDU *pdatatf);
    ~PDataTfRQDUL();
public:
    void DUL_SendPDataTfPDU(int conn);

private:
    void DUL_GetPDataTfPDUMemory();
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