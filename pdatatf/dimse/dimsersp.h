#ifndef DIMSERSP_H
#define DIMSERSP_H
#include "dimse.h"
#include <string>
#include "../../pdu/pdupdatatf.h"
#include "../../dul/dulpdatatfrsp.h"
using namespace std;
using namespace PDUPDataTF_namespace;


struct DIMSERSPResult
{
    vector<DcmElement*> commandElementList;
    vector<DcmElement*> dataSetElementList;
};


class DIMSERSP
{
public:
    DIMSERSP(int conn, string transfersyntax);
    ~DIMSERSP();
public:
    vector<DIMSERSPResult> ReceivePDataTfRsp();
    
protected:
    virtual void GetStatus(uint16_t *status) = 0;
    void GetPDataTfResult(PDataTFPDU * pDataTFPDU);
    virtual bool CheckPDataTfRsp(vector<DcmElement *> commandelementlist);
    bool IsReceiveOneFullResult();
    void Clear();
protected:
    vector<DcmElement*> commandElementList;
    vector<DcmElement*> dataSetElementList;
    bool isCommandLastFragment;
    bool isDataSetLastFragment;;
    CDIMSERSP *cDIMSERSP;
    PDataTfRSPDUL *pDataTfRSPDUL;
};












#endif // !CFINDRSP_H