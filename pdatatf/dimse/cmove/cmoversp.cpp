#include "cmoversp.h"

CMoveRSPDIMSE::CMoveRSPDIMSE(string transfersyntax) : CDIMSERSP(transfersyntax)
{
    numberofRemainingSubOperations = new DcmElement();
    InitElementTag(numberofRemainingSubOperations, 0x0000, 0x1020);

    numberofCompleteSubOperations = new DcmElement();
    InitElementTag(numberofCompleteSubOperations, 0x0000, 0x1021);

    numberofFailedSubOperations = new DcmElement();
    InitElementTag(numberofFailedSubOperations, 0x0000, 0x1022);

    numberofWarningSubOperations = new DcmElement();
    InitElementTag(numberofWarningSubOperations, 0x0000, 0x1023);

    dcmElemenetList.push_back(numberofRemainingSubOperations);
    dcmElemenetList.push_back(numberofCompleteSubOperations);
    dcmElemenetList.push_back(numberofFailedSubOperations);
    dcmElemenetList.push_back(numberofWarningSubOperations);

    lastSummaryRsp = dcmElemenetList;
    // dcmtk cmoversp lastsummaryrsp has no numberofRemainingSubOperations
    lastSummaryRsp.erase(lastSummaryRsp.end() - 1 - 3);
}

CMoveRSPDIMSE::~CMoveRSPDIMSE()
{

}


CMoveRSP::CMoveRSP(int conn, string transfersyntax) : DIMSERSP(conn, transfersyntax)
{
    isCommandLastFragment = false;
    isDataSetLastFragment= false;
    cDIMSERSP = new CMoveRSPDIMSE(transfersyntax);
}

CMoveRSP::~CMoveRSP()
{
    delete cDIMSERSP;
    cDIMSERSP = NULL;
}

bool CMoveRSP::CheckPDataTfRsp(vector<DcmElement *> commandelementlist)
{
    if(!DIMSERSP::CheckPDataTfRsp(commandelementlist))
    {
       return DIMSERSP::CheckPDataTfRsp(((CMoveRSPDIMSE *)cDIMSERSP)->lastSummaryRsp);
    }
    
    return true;
}

void CMoveRSP::GetStatus(uint16_t *status)
{
    memcpy(status, (*(commandElementList.end() - 1 - 4))->data.data, sizeof(status));
}
