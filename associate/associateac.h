#ifndef ASSOCIATEAC_H
#define ASSOCIATEAC_H


#include "../pdu/pduassociateac.h"
#include <string>

using namespace std;
using namespace AssociateACPDU_NameSpace;

class AssociateAC
{
public:
    AssociateAC(AssociateACPDU *associateacpdu);
    ~AssociateAC();
public:
    void ReceiveAssociateAC(int conn);

private:
    int itemheadlength;
    AssociateACPDU *associateACPDU;
};

#endif
