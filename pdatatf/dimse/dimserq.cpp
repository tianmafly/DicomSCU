#include "dimserq.h"
#include "../pdatatf.h"
#include <stdint.h>
#include "../../dul/dulpdatatfrq.h"


DIMSERQ::DIMSERQ(int conn, string transfersyntax, unsigned char presentationid)
{
    this->conn = conn;
    this->transfersyntax = transfersyntax;
    this->presentationid = presentationid;

    commandlen = 0;
    datasetlen = 0;
    grouplen = 0;
}

DIMSERQ::~DIMSERQ()
{
    
}

void DIMSERQ::DIMSE_SendPDataTfPDU(vector<DcmElement*> querykeylist, QueryRetrieveRoot root)
{
    InitDIMSERQMessage(querykeylist, root);
    vector<DcmElement*> commandlist = cDIMSERQ->dcmElemenetList;

    PDataTF pDataTF;
    PDataTFPDU * pDataTFPDU = pDataTF.InitDefaultPDataTFPDU(commandlist, this->commandlen, querykeylist, this->datasetlen, presentationid);

    PDataTfRQDUL pDataTfRQDUL(pDataTFPDU);
    pDataTfRQDUL.DUL_SendPDataTfPDU(conn);
}

void DIMSERQ::InitDIMSERQMessage(vector<DcmElement*> querykeylist, QueryRetrieveRoot root)
{
    InitDIMSERQCommand(root);
    InitDIMSERQDataSet(querykeylist);
}

void DIMSERQ::InitDIMSERQCommand(QueryRetrieveRoot root)
{    
    cDIMSERQ->InitElementData(cDIMSERQ->affectedSOPClassUID, queryRetrieveRoot.size(), (unsigned char*)queryRetrieveRoot.c_str());
    cDIMSERQ->InitElementData(cDIMSERQ->commandField, commandtype);
    cDIMSERQ->InitElementData(cDIMSERQ->messageID, (uint8_t)0x01);
    cDIMSERQ->InitElementData(cDIMSERQ->priority, (uint16_t)0x0000);
    cDIMSERQ->InitElementData(cDIMSERQ->commandDataSetType, (uint16_t)0x1111);

    grouplen = cDIMSERQ->GetDcmElementLen(cDIMSERQ->affectedSOPClassUID) + 
               cDIMSERQ->GetDcmElementLen(cDIMSERQ->commandField) + 
               cDIMSERQ->GetDcmElementLen(cDIMSERQ->messageID) + 
               cDIMSERQ->GetDcmElementLen(cDIMSERQ->priority) + 
               cDIMSERQ->GetDcmElementLen(cDIMSERQ->commandDataSetType);
}

void DIMSERQ::InitDIMSERQDataSet(vector<DcmElement*> querykeylist)
{
    queryKeyList = querykeylist;

    for (int i = 0; i < querykeylist.size(); i++)
    {
        datasetlen += cDIMSERQ->GetDcmElementLen(querykeylist[i]);
    }
}
