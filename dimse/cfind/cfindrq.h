#ifndef CFINDRQ_H
#define CFINDRQ_H


#include "../dimse.h"
#include <vector>
#include "../../type/uid.h"
using namespace std;


class CFindRQDIMSE : public CDIMSERQ
{
    
};



class CFindRQ
{
public:
    CFindRQ();
    ~CFindRQ();
public:
    void SendCFindRQPDU(vector<DcmElement> querykeylist, CFindRoot cfindroot, unsigned char presentationid);
    
private:
    void InitCFindeRQMessage(vector<DcmElement> querykeylist, CFindRoot cfindroot);
    void InitCFindeRQCommand(CFindRoot cfindroot);
    void InitCFindeRQDataSet(vector<DcmElement> querykeylist);
    int GetDcmElementLen(DcmElement dcmelement);
private:
    CFindRQDIMSE *cFindRQDIMSE;
    vector<DcmElement> queryKeyList;
    uint16_t commandlen;
    uint16_t datasetlen;
};



#endif // !CFINDRQ_H
