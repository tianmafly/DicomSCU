#ifndef DULCFINDRSP_H
#define DULCFINDRSP_H

#include "../pdu/pdupdatatf.h"
using namespace PDUPDataTF_namespace;

class CFindRSPDUL
{
private:
    /* data */
public:
    CFindRSPDUL(/* args */);
    ~CFindRSPDUL();
public:
    PDataTFPDU * DUL_ReceiveCFindRSP();
};










#endif // !DULCFINDRSP_H
