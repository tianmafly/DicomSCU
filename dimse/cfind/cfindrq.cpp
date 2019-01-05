#include "cfindrq.h"
#include "../../type/uid.h"
#include "../../pdatatf/pdatatf.h"
#include <stdint.h>

CFindRQ::CFindRQ(/* args */)
{
    cFindRQDIMSE = new CFindRQDIMSE();
}

CFindRQ::~CFindRQ()
{
    delete cFindRQDIMSE;
    cFindRQDIMSE = NULL;
}

void CFindRQ::SendCFindRQPDU(vector<DcmElement> querykeylist, CFindRoot cfindroot, unsigned char presentationid)
{
    InitCFindeRQMessage(querykeylist, cfindroot);
    PDataTF pDataTF;
    pDataTF.InitDefaultPDataTFPDU(cFindRQDIMSE, commandlen, &querykeylist, datasetlen, presentationid);
}

void CFindRQ::InitCFindeRQMessage(vector<DcmElement> querykeylist, CFindRoot cfindroot)
{
    commandlen = InitCFindeRQCommand(cfindroot);
    datasetlen = InitCFindeRQDataSet(querykeylist);

    int groupLength = commandlen + datasetlen;
    cFindRQDIMSE->InitElementData(&(cFindRQDIMSE->groupLength), 2, groupLength);
}

int CFindRQ::InitCFindeRQCommand(CFindRoot cfindroot)
{
    string cFindRoot;
    if (cfindroot == CFindPatientRoot)
        cFindRoot = PatientRoot_QueryRetrieveInformationModel_FIND;
    else if (cfindroot == CFindStudyRoot)
        cFindRoot = StudyRoot_QueryRetrieveInformationModel_FIND;
    
    // groupLength to count command length
    cFindRQDIMSE->InitElementData(&(cFindRQDIMSE->groupLength), 2, (uint32_t)0x00);
    cFindRQDIMSE->InitElementData(&(cFindRQDIMSE->affectedSOPClassUID), cFindRoot.size(), (unsigned char*)cFindRoot.c_str());
    cFindRQDIMSE->InitElementData(&(cFindRQDIMSE->commandField), 2, 0x0020);
    cFindRQDIMSE->InitElementData(&(cFindRQDIMSE->messageID), 1, 0x01);
    cFindRQDIMSE->InitElementData(&(cFindRQDIMSE->priority), 2, (uint32_t)0x0000);
    cFindRQDIMSE->InitElementData(&(cFindRQDIMSE->commandDataSetType), 2, 0x1111);

    return GetDcmElementLen(cFindRQDIMSE->groupLength) + 
           GetDcmElementLen(cFindRQDIMSE->affectedSOPClassUID) + 
           GetDcmElementLen(cFindRQDIMSE->commandField) + 
           GetDcmElementLen(cFindRQDIMSE->messageID) + 
           GetDcmElementLen(cFindRQDIMSE->priority) + 
           GetDcmElementLen(cFindRQDIMSE->commandDataSetType);
}

int CFindRQ::InitCFindeRQDataSet(vector<DcmElement> querykeylist)
{
    queryKeyList = querykeylist;

    int len = 0;
    for (int i = 0; i < querykeylist.size(); i++)
    {
        len += GetDcmElementLen(querykeylist[i]);
    }

    return len;
}

int CFindRQ::GetDcmElementLen(DcmElement dcmelement)
{
    return sizeof(dcmelement.tag) + dcmelement.vr.len + dcmelement.datalen.len + dcmelement.data.len;
}