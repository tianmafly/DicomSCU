#include "cfindrq.h"


CFindRQDIMSE::CFindRQDIMSE(string transfersyntax) : CDIMSERQ(transfersyntax)
{

}

CFindRQ::CFindRQ(int conn, string transfersyntax, unsigned char presentationid) : DIMSERQ(conn, transfersyntax, presentationid)
{
    cDIMSERQ = new CFindRQDIMSE(transfersyntax);
    commandtype = CFindRQ_CommandType;
}

CFindRQ::~CFindRQ()
{
    
}

void CFindRQ::InitDIMSERQCommand(QueryRetrieveRoot root)
{
    if (root == PatientRoot)
        queryRetrieveRoot = PatientRoot_QueryRetrieveInformationModel_FIND;
    else if (root == StudyRoot)
        queryRetrieveRoot = StudyRoot_QueryRetrieveInformationModel_FIND;

    DIMSERQ::InitDIMSERQCommand(root);
    
    cDIMSERQ->InitElementData(cDIMSERQ->groupLength, grouplen);
    commandlen = cDIMSERQ->GetDcmElementLen(cDIMSERQ->groupLength) + grouplen;
}