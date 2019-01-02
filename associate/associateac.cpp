#include "associateac.h"
#include <string.h>
#include "../type/uid.h"
#include "../dul/dulassociateac.h"

AssociateAC::AssociateAC(AssociateACPDU *associateacpdu)
{
    //char ItemType; char Reserved; uint16_t ItemLen;
    this->itemheadlength = sizeof(ItemHead::ItemType) + sizeof(ItemHead::Reserved) + sizeof(ItemHead::ItemLen);
    this->associateACPDU = associateacpdu;
}

AssociateAC::~AssociateAC()
{
}

void AssociateAC::ReceiveAssociateAC(int conn)
{
    AssociateACDUL associateACDUL(conn);
    associateACDUL.DUL_ReceiveAssociateAC(this->associateACPDU);
    
}
