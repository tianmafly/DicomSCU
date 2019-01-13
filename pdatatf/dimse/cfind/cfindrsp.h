#ifndef CFINDRSP_H
#define CFINDRSP_H
#include "../dimse.h"
#include <map>
#include <string>
#include "../../../pdu/pdupdatatf.h"
using namespace std;
using namespace PDUPDataTF_namespace;

class CFindRSPDIMSE: public CDIMSERSP
{
public:
    DcmElement *affectedSOPInstanceUID;
public:
    CFindRSPDIMSE(string transfersyntax);
public:
    vector<DcmElement*> noResultList;
};


struct CFindRSPResult
{
    vector<DcmElement*> commandElementList;
    vector<DcmElement*> dataSetElementList;
};




class CFindRSP
{
public:
    CFindRSP();
    ~CFindRSP();
public:
    vector<CFindRSPResult> ReceiveCFindRsp(int conn, string bytemodel);
    
private:
    void GetCFindResult(PDataTFPDU * pDataTFPDU);
    bool CheckCFindRsp();
    bool IsReceiveAll();
    void Clear();
private:
    vector<DcmElement*> commandElementList;
    vector<DcmElement*> dataSetElementList;
    bool isCommandLastFragment;
    bool isDataSetLastFragment;
};












#endif // !CFINDRSP_H