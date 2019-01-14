#ifndef CFINDRSP_H
#define CFINDRSP_H
#include "../dimse.h"
#include <string>
#include "../../../pdu/pdupdatatf.h"
#include "../dimsersp.h"
using namespace std;
using namespace PDUPDataTF_namespace;


class CFindRSPDIMSE: public CDIMSERSP
{
public:
    DcmElement *affectedSOPInstanceUID;
public:
    CFindRSPDIMSE(string transfersyntax);
};


class CFindRSP : public DIMSERSP
{
public:
    CFindRSP(int conn, string transfersyntax);
    ~CFindRSP();
public:
    virtual void GetStatus(uint16_t *status);
    virtual bool IsReceiveOneFullResult();
};












#endif // !CFINDRSP_H