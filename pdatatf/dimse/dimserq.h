#ifndef DIMSERE_H
#define DIMSERE_H


#include "dimse.h"
#include <vector>
#include "../../type/uid.h"

using namespace std;



class DIMSERQ
{
public:
    DIMSERQ(int conn, string transfersyntax, unsigned char presentationid);
    ~DIMSERQ();
public:
    void DIMSE_SendPDataTfPDU(vector<DcmElement*> querykeylist, QueryRetrieveRoot root);
    
protected:
    void InitDIMSERQMessage(vector<DcmElement*> querykeylist, QueryRetrieveRoot root);
    virtual void InitDIMSERQCommand(QueryRetrieveRoot root);
    void InitDIMSERQDataSet(vector<DcmElement*> querykeylist);

protected:
    CDIMSERQ *cDIMSERQ;
    vector<DcmElement*> queryKeyList;
    uint16_t commandlen;
    uint16_t datasetlen;
    uint16_t commandtype;
    uint16_t grouplen;
    int conn;
    string transfersyntax;
    unsigned char presentationid;
    string queryRetrieveRoot;
};



#endif // !CFINDRQ_H
