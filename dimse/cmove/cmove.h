#ifndef CMOVE_H
#define CMOVE_H
#include "../dimse.h"

struct CMoveRQDIMSE : public CDIMSERQ
{
    DcmElement  moveDestination;
};

struct CFindRSPDIMSE : public CDIMSERSP
{
    DcmElement numberofRemainingSubOperations;
    DcmElement numberofCompleteSubOperations;
    DcmElement numberofFailedSubOperations;
    DcmElement numberofWarningSubOperations;
};


#endif // !CMOVE_H