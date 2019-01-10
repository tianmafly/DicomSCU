#ifndef CFINDRSP_H
#define CFINDRSP_H
#include "../dimse.h"
#include <map>
#include <string>
using namespace std;

class CFindRSPDIMSE: public CDIMSERSP
{

};


class CFindRSP
{
private:
    
public:
    CFindRSP();
    ~CFindRSP();
public:
    map<string, string> ReceiveCFindRsp();
    map<string, string> GetCFindResult();
};












#endif // !CFINDRSP_H