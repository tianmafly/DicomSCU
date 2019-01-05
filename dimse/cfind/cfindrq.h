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
    int InitCFindeRQCommand(CFindRoot cfindroot);
    int InitCFindeRQDataSet(vector<DcmElement> querykeylist);
    int GetDcmElementLen(DcmElement dcmelement);
private:
    CFindRQDIMSE *cFindRQDIMSE;
    vector<DcmElement> queryKeyList;
    int commandlen;
    int datasetlen;
};



#endif // !CFINDRQ_H
