#ifndef CFINDRQ_H
#define CFINDRQ_H


#include "../dimserq.h"
using namespace std;


class CFindRQDIMSE : public CDIMSERQ
{
public:
    CFindRQDIMSE(string transfersyntax);
};



class CFindRQ : public DIMSERQ
{
public:
    CFindRQ(int conn, string transfersyntax, unsigned char presentationid);
    ~CFindRQ();
public:
    virtual void InitDIMSERQCommand(QueryRetrieveRoot root);
};



#endif // !CFINDRQ_H
