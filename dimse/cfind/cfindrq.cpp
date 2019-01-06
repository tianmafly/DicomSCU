#include "cfindrq.h"
#include "../../type/uid.h"
#include "../../pdatatf/pdatatf.h"
#include <stdint.h>
#include "../../dul/dulcfindrq.h"

CFindRQDIMSE::CFindRQDIMSE(string transfersyntax) : CDIMSERQ(transfersyntax)
{

}

CFindRQ::CFindRQ(int conn, string transfersyntax, unsigned char presentationid)
{
    this->conn = conn;
    this->transfersyntax = transfersyntax;
    this->presentationid = presentationid;

    cFindRQDIMSE = new CFindRQDIMSE(transfersyntax);
    commandlen = 0;
    datasetlen = 0;
}

CFindRQ::~CFindRQ()
{
    delete cFindRQDIMSE;
    cFindRQDIMSE = NULL;
}

void CFindRQ::SendCFindRQPDU(vector<DcmElement> querykeylist, CFindRoot cfindroot)
{
    InitCFindeRQMessage(querykeylist, cfindroot);
    vector<DcmElement> commandlist = TransferCommandToVector();

    PDataTF pDataTF;
    PDataTFPDU * pDataTFPDU = pDataTF.InitDefaultPDataTFPDU(commandlist, this->commandlen, querykeylist, this->datasetlen, presentationid);

    CFindeRQPDU cFindRQPDU(pDataTFPDU);
    cFindRQPDU.DUL_SendCFindRQ(conn);
}

void CFindRQ::InitCFindeRQMessage(vector<DcmElement> querykeylist, CFindRoot cfindroot)
{
    InitCFindeRQCommand(cfindroot);
    InitCFindeRQDataSet(querykeylist);

    cFindRQDIMSE->InitElementData(&(cFindRQDIMSE->groupLength), (uint16_t)(this->commandlen + this->datasetlen));
}

void CFindRQ::InitCFindeRQCommand(CFindRoot cfindroot)
{
    string cFindRoot;
    if (cfindroot == CFindPatientRoot)
        cFindRoot = PatientRoot_QueryRetrieveInformationModel_FIND;
    else if (cfindroot == CFindStudyRoot)
        cFindRoot = StudyRoot_QueryRetrieveInformationModel_FIND;
    
    // groupLength to count command length
    cFindRQDIMSE->InitElementData(&(cFindRQDIMSE->groupLength), (uint16_t)0x0000);
    cFindRQDIMSE->InitElementData(&(cFindRQDIMSE->affectedSOPClassUID), cFindRoot.size(), (unsigned char*)cFindRoot.c_str());
    cFindRQDIMSE->InitElementData(&(cFindRQDIMSE->commandField), CFindRQ_CommandType);
    cFindRQDIMSE->InitElementData(&(cFindRQDIMSE->messageID), (uint8_t)0x01);
    cFindRQDIMSE->InitElementData(&(cFindRQDIMSE->priority), (uint16_t)0x0000);
    cFindRQDIMSE->InitElementData(&(cFindRQDIMSE->commandDataSetType), (uint16_t)0x1111);

    commandlen = GetDcmElementLen(cFindRQDIMSE->groupLength) + 
                 GetDcmElementLen(cFindRQDIMSE->affectedSOPClassUID) + 
                 GetDcmElementLen(cFindRQDIMSE->commandField) + 
                 GetDcmElementLen(cFindRQDIMSE->messageID) + 
                 GetDcmElementLen(cFindRQDIMSE->priority) + 
                 GetDcmElementLen(cFindRQDIMSE->commandDataSetType);
}

void CFindRQ::InitCFindeRQDataSet(vector<DcmElement> querykeylist)
{
    queryKeyList = querykeylist;

    for (int i = 0; i < querykeylist.size(); i++)
    {
        datasetlen += GetDcmElementLen(querykeylist[i]);
    }
}

int CFindRQ::GetDcmElementLen(DcmElement dcmelement)
{
    return sizeof(dcmelement.tag) + dcmelement.vr.len + dcmelement.datalen.len + dcmelement.data.len;
}

vector<DcmElement> CFindRQ::TransferCommandToVector()
{
    vector<DcmElement> commandlist;
    commandlist.push_back(cFindRQDIMSE->groupLength);
    commandlist.push_back(cFindRQDIMSE->affectedSOPClassUID);
    commandlist.push_back(cFindRQDIMSE->commandField);
    commandlist.push_back(((CFindRQDIMSE*)cFindRQDIMSE)->messageID);
    commandlist.push_back(((CFindRQDIMSE*)cFindRQDIMSE)->priority);
    commandlist.push_back(cFindRQDIMSE->commandDataSetType);
    
    return commandlist;
}