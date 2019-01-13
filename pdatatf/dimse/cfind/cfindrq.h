#ifndef CFINDRQ_H
#define CFINDRQ_H


#include "../dimse.h"
#include <vector>
#include "../../../type/uid.h"

using namespace std;


class CFindRQDIMSE : public CDIMSERQ
{
public:
    CFindRQDIMSE(string transfersyntax);
};



class CFindRQ
{
public:
    CFindRQ(int conn, string transfersyntax, unsigned char presentationid);
    ~CFindRQ();
public:
    void SendCFindRQPDU(vector<DcmElement> querykeylist, CFindRoot cfindroot);
    
private:
    void InitCFindeRQMessage(vector<DcmElement> querykeylist, CFindRoot cfindroot);
    void InitCFindeRQCommand(CFindRoot cfindroot);
    void InitCFindeRQDataSet(vector<DcmElement> querykeylist);
    vector<DcmElement> TransferCommandToVector();
private:
    CFindRQDIMSE *cFindRQDIMSE;
    vector<DcmElement> queryKeyList;
    uint16_t commandlen;
    uint16_t datasetlen;
    int conn;
    string transfersyntax;
    unsigned char presentationid;
};



#endif // !CFINDRQ_H
