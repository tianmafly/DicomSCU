#include "cfindrsp.h"
#include "../../../dul/dulcfindrsp.h"
#include "../../../pdu/pdupdatatf.h"

using namespace PDUPDataTF_namespace;

CFindRSP::CFindRSP()
{

}

CFindRSP::~CFindRSP()
{

}

map<string, string>  CFindRSP::ReceiveCFindRsp()
{
    CFindRSPDUL cFindRSPDUL;
    PDataTFPDU * pDataTFPDU = cFindRSPDUL.DUL_ReceiveCFindRSP();

    map<string, string> a;
    return a;
}

map<string, string> CFindRSP::GetCFindResult()
{   
    map<string, string> a;
    return a;
}