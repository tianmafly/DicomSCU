#ifndef CMOVERQ_H
#define CMOVERQ_H
#include "../dimse.h"
#include "../dimserq.h"

using namespace std;


class CMoveRQDIMSE : public CDIMSERQ
{
public:
    CMoveRQDIMSE(string transfersyntax);
public:
    DcmElement *moveDestination;
};

struct CMoveRSPDIMSE : public CDIMSERSP
{
    DcmElement numberofRemainingSubOperations;
    DcmElement numberofCompleteSubOperations;
    DcmElement numberofFailedSubOperations;
    DcmElement numberofWarningSubOperations;
};


class CMoveRQ : public DIMSERQ
{
public:
    CMoveRQ(int conn, string transfersyntax, unsigned char presentationid, string moveAE);
    ~CMoveRQ();
protected:
    virtual void InitDIMSERQCommand(QueryRetrieveRoot root);
private:
    string moveAE;
};


#endif // !CMOVE_H