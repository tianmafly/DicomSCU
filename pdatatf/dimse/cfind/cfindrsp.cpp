#include "cfindrsp.h"
#include "../../../dul/dulpdatatfrsp.h"
#include "../../../type/uid.h"

using namespace PDUPDataTF_namespace;

CFindRSPDIMSE::CFindRSPDIMSE(string transfersyntax) : CDIMSERSP(transfersyntax)
{
    
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

