#include "cfindrsp.h"
#include "../../../dul/dulpdatatfrsp.h"
#include "../../../type/uid.h"

using namespace PDUPDataTF_namespace;

CFindRSPDIMSE::CFindRSPDIMSE(string transfersyntax) : CDIMSERSP(transfersyntax)
{
    affectedSOPInstanceUID = new DcmElement();
    InitElementTag(affectedSOPInstanceUID, 0x0000, 0x1000);

    // affectedSOPInstanceUID is befor of status
    dcmElemenetList.insert((dcmElemenetList.end() -1), affectedSOPInstanceUID);
    
    noResultList  = dcmElemenetList;
    // delete affectedSOPInstanceUID
    noResultList.erase(noResultList.end() - 1 - 1);
}

CFindRSP::CFindRSP(int conn, string transfersyntax) : DIMSERSP(conn, transfersyntax)
{
    isCommandLastFragment = false;
    isDataSetLastFragment= false;
    cDIMSERSP = new CFindRSPDIMSE(transfersyntax);
}

CFindRSP::~CFindRSP()
{
    delete cDIMSERSP;
    cDIMSERSP = NULL;
}

void CFindRSP::GetStatus(uint16_t *status)
{
    memcpy(status, (*(commandElementList.end() - 1))->data.data, sizeof(status));
}

bool CFindRSP::IsReceiveOneFullResult()
{
    if(isCommandLastFragment)
    {
        uint16_t datasetflag = 0x0101;
        DcmElement *commandDataSetType = commandElementList[4];
        // no result or last rsp. only with commond.
        if(memcmp(commandDataSetType->data.data, &datasetflag, sizeof(datasetflag)) == 0)
        {
            return true;
        }
        else
        {
            if(isCommandLastFragment == true && isDataSetLastFragment == true)
            {
                
                return true;
            }
        }
    }

    return false;
}
