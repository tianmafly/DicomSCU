#include "cmoverq.h"
#include <stdio.h>

CMoveRQDIMSE::CMoveRQDIMSE(string transfersyntax) : CDIMSERQ(transfersyntax)
{
    moveDestination = new DcmElement();
    InitElementTag(moveDestination, 0x0000, 0x0600);

    dcmElemenetList.push_back(moveDestination);
}


CMoveRQ::CMoveRQ(int conn, string transfersyntax, unsigned char presentationid, string moveAE) : DIMSERQ(conn, transfersyntax, presentationid)
{
    cDIMSERQ = new CMoveRQDIMSE(transfersyntax);
    commandtype = CMoveRQ_CommandType;
    this->moveAE = moveAE;
    printf("%s\n", this->moveAE.c_str());
    printf("%s\n", transfersyntax.c_str());
}

CMoveRQ::~CMoveRQ()
{
    
}

void CMoveRQ::InitDIMSERQCommand(QueryRetrieveRoot root)
{
    if (root == PatientRoot)
        queryRetrieveRoot = PatientRoot_QueryRetrieveInformationModel_MOVE;
    else if (root == StudyRoot)
        queryRetrieveRoot = StudyRoot_QueryRetrieveInformationModel_MOVE;

    DIMSERQ::InitDIMSERQCommand(root);
    
    cDIMSERQ->InitElementData(((CMoveRQDIMSE*)cDIMSERQ)->moveDestination, moveAE.size(), (unsigned char*)moveAE.c_str());
    grouplen += cDIMSERQ->GetDcmElementLen(((CMoveRQDIMSE*)cDIMSERQ)->moveDestination);
    cDIMSERQ->InitElementData(cDIMSERQ->groupLength, grouplen);
    commandlen = cDIMSERQ->GetDcmElementLen(cDIMSERQ->groupLength) + grouplen;
}