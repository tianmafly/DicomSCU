#include "dimsersp.h"
#include "../../type/uid.h"

using namespace PDUPDataTF_namespace;

DIMSERSP::DIMSERSP(int conn, string transfersyntax)
{
    isCommandLastFragment = false;
    isDataSetLastFragment= false;
    cDIMSERSP = NULL;
    pDataTfRSPDUL = new PDataTfRSPDUL(conn, transfersyntax);
}

DIMSERSP::~DIMSERSP()
{
    delete pDataTfRSPDUL;
    pDataTfRSPDUL = NULL;
}

// one P-Data-TF PDU may contain one command pdv and one or more dataset pdvs.
// one P-Data-TF PDU also may only contain one command pdv or one dataset pdv.
// dcmtk cfindrsp/cmoversp command pdv is a P-Data-TF PDU. Dataset pdv is a P-Data-TF PDU.
vector<DIMSERSPResult> DIMSERSP::ReceivePDataTfRsp()
{
    uint16_t status = Pending_OK_Status;
    
    vector<DIMSERSPResult> cFindRspResultList;
    while(status == Pending_OK_Status)
    {
        
        PDataTFPDU * pDataTFPDU = pDataTfRSPDUL->DUL_ReceivePDataTfRSP();
        GetPDataTfResult(pDataTFPDU);
        if (!CheckPDataTfRsp())
            return cFindRspResultList;
        GetStatus(&status);
        
        if(IsReceiveOneFullResult())
        {
            DIMSERSPResult cFindRSPResult;
            cFindRSPResult.commandElementList = commandElementList;
            cFindRSPResult.dataSetElementList = dataSetElementList;
            cFindRspResultList.push_back(cFindRSPResult);

            Clear();
        }
    }
    
    return cFindRspResultList;
}

void DIMSERSP::GetPDataTfResult(PDataTFPDU * pDataTFPDU)
{   
    for(int i=0; i<pDataTFPDU->presentationDataValueItemList.size(); i++)
    {
        if((pDataTFPDU->presentationDataValueItemList[i].presentationDataValue.messageControlHeader & 0b00000001) == PDVCommand)
        {
            vector<DcmElement*> partCommandElementlist = pDataTFPDU->presentationDataValueItemList[i].presentationDataValue.messageCommandOrDataSetFragment;
            commandElementList.insert(commandElementList.end(), partCommandElementlist.begin(), partCommandElementlist.end());

            if((pDataTFPDU->presentationDataValueItemList[i].presentationDataValue.messageControlHeader & 0b00000011) == PDVCommandLastFragment)
            {
                isCommandLastFragment = true;
            }
        }
        else if((pDataTFPDU->presentationDataValueItemList[i].presentationDataValue.messageControlHeader & 0b00000001) == PDVDataSet)
        {
            vector<DcmElement*> partdataSetElementList = pDataTFPDU->presentationDataValueItemList[i].presentationDataValue.messageCommandOrDataSetFragment;
            dataSetElementList.insert(dataSetElementList.end(), partdataSetElementList.begin(), partdataSetElementList.end());

            if((pDataTFPDU->presentationDataValueItemList[i].presentationDataValue.messageControlHeader & 0b00000011) == PDVDataSetLastFragment)
            {
                isDataSetLastFragment = true;
            }
        }  
    }
}

bool DIMSERSP::CheckPDataTfRsp()
{
    vector<DcmElement*> dcmElementlist;
    if(isCommandLastFragment)
    {
        if(commandElementList.size() == cDIMSERSP->dcmElemenetList.size())
        {
            dcmElementlist = cDIMSERSP->dcmElemenetList;
        }
        else if(commandElementList.size() == cDIMSERSP->noResultList.size())
        {
            dcmElementlist = cDIMSERSP->noResultList;   
        }
        else
        {
            return false;
        }

        for(int i=0; i< commandElementList.size(); i++)
        {
            if(memcmp(commandElementList[i]->tag, dcmElementlist[i]->tag, sizeof(commandElementList[i]->tag)) != 0)
                return false;
        }
    }
    
    return true;
    
}

bool DIMSERSP::IsReceiveOneFullResult()
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

void DIMSERSP::Clear()
{
    commandElementList.clear();
    dataSetElementList.clear();

    isCommandLastFragment = false;
    isDataSetLastFragment = false;
}