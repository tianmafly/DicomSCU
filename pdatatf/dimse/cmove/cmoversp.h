#ifndef CMOVERSP_H
#define CMOVERSP_H
#include "../dimse.h"
#include "../dimsersp.h"

class CMoveRSPDIMSE : public CDIMSERSP
{
public:
    CMoveRSPDIMSE(string transfersyntax);
    ~CMoveRSPDIMSE();
public:
    DcmElement *numberofRemainingSubOperations;
    DcmElement *numberofCompleteSubOperations;
    DcmElement *numberofFailedSubOperations;
    DcmElement *numberofWarningSubOperations;
};


class CMoveRSP : public DIMSERSP
{
public:
    CMoveRSP(int conn, string transfersyntax);
    ~CMoveRSP();
protected:
    virtual void GetStatus(uint16_t *status);
    virtual bool IsReceiveOneFullResult();
};

#endif // !CMOVERSP_H