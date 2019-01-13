#include "cfindrsp.h"
#include "../../../dul/dulcfindrsp.h"

#include "../../../type/uid.h"

using namespace PDUPDataTF_namespace;

CFindRSPDIMSE::CFindRSPDIMSE(string transfersyntax) : CDIMSERSP(transfersyntax)
{
    InitElementTag(&affectedSOPInstanceUID, 0x0000, 0x1000);

    hasResultList.push_back(groupLength);
    hasResultList.push_back(affectedSOPClassUID);
    hasResultList.push_back(commandField);
    hasResultList.push_back(messageIDBeingRespondedTo);
    hasResultList.push_back(commandDataSetType);
    hasResultList.push_back(affectedSOPInstanceUID);
    hasResultList.push_back(status);

    noResultList.push_back(groupLength);
    noResultList.push_back(affectedSOPClassUID);
    noResultList.push_back(commandField);
    noResultList.push_back(messageIDBeingRespondedTo);
    noResultList.push_back(commandDataSetType);
    noResultList.push_back(status);

}

CFindRSP::CFindRSP()
{
    isCommandLastFragment = false;
    isDataSetLastFragment= false;
}

CFindRSP::~CFindRSP()
{

}

vector<CFindRSPResult> CFindRSP::ReceiveCFindRsp(int conn, string bytemodel)
{
    uint16_t status = Pending_OK_Status;
    CFindRSPDUL cFindRSPDUL(conn, bytemodel);
    vector<CFindRSPResult> cFindRspResultList;
    while(status == Pending_OK_Status)
    {
        
        PDataTFPDU * pDataTFPDU = cFindRSPDUL.DUL_ReceiveCFindRSP();
        GetCFindResult(pDataTFPDU);
        if (!CheckCFindRsp())
            return cFindRspResultList;
        memcpy(&status, (commandElementList.end() - 1)->data.data, sizeof(status));
        
        if(IsReceiveAll())
        {
            CFindRSPResult cFindRSPResult;
            cFindRSPResult.commandElementList = commandElementList;
            cFindRSPResult.dataSetElementList = dataSetElementList;
            cFindRspResultList.push_back(cFindRSPResult);

            Clear();
        }
    }
    
    return cFindRspResultList;
}

void CFindRSP::GetCFindResult(PDataTFPDU * pDataTFPDU)
{   
    for(int i=0; i<pDataTFPDU->presentationDataValueItemList.size(); i++)
    {
        if((pDataTFPDU->presentationDataValueItemList[i].presentationDataValue.messageControlHeader & 0b00000001) == PDVCommand)
        {
            vector<DcmElement> partCommandElementlist = pDataTFPDU->presentationDataValueItemList[i].presentationDataValue.messageCommandOrDataSetFragment;
            commandElementList.insert(commandElementList.end(), partCommandElementlist.begin(), partCommandElementlist.end());

            if((pDataTFPDU->presentationDataValueItemList[i].presentationDataValue.messageControlHeader & 0b00000011) == PDVCommandLastFragment)
            {
                isCommandLastFragment = true;
            }
        }
        else if((pDataTFPDU->presentationDataValueItemList[i].presentationDataValue.messageControlHeader & 0b00000001) == PDVDataSet)
        {
            vector<DcmElement> partdataSetElementList = pDataTFPDU->presentationDataValueItemList[i].presentationDataValue.messageCommandOrDataSetFragment;
            dataSetElementList.insert(dataSetElementList.end(), partdataSetElementList.begin(), partdataSetElementList.end());

            if((pDataTFPDU->presentationDataValueItemList[i].presentationDataValue.messageControlHeader & 0b00000011) == PDVDataSetLastFragment)
            {
                isDataSetLastFragment = true;
            }
        }  
    }
}

bool CFindRSP::CheckCFindRsp()
{
    CFindRSPDIMSE cFindRSPDIMSE("");

    vector<DcmElement> dcmElementlist;
    if(isCommandLastFragment)
    {
        if(commandElementList.size() == cFindRSPDIMSE.hasResultList.size())
        {
            dcmElementlist = cFindRSPDIMSE.hasResultList;
        }
        else if(commandElementList.size() == cFindRSPDIMSE.noResultList.size())
        {
            dcmElementlist = cFindRSPDIMSE.noResultList;   
        }
        else
        {
            return false;
        }

        for(int i=0; i< commandElementList.size(); i++)
        {
            if(memcmp(commandElementList[i].tag, dcmElementlist[i].tag, sizeof(commandElementList[i].tag)) != 0)
                return false;
        }
    }
    
    return true;
    
}

bool CFindRSP::IsReceiveAll()
{
    if(isCommandLastFragment)
    {
        uint16_t datasetflag = 0x0101;
        DcmElement commandDataSetType = commandElementList[4];
        // no result or last rsp. only with commond.
        if(memcmp(commandDataSetType.data.data, &datasetflag, sizeof(datasetflag)) == 0)
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

void CFindRSP::Clear()
{
    commandElementList.clear();
    dataSetElementList.clear();
}