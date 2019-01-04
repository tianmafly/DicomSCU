#include "associate.h"
#include <stdio.h>
#include <string.h>
#include "../type/uid.h"
#include "associaterq.h"
#include "associateac.h"

Associate::Associate(/* args */)
{
    conn = -1;
}

Associate::~Associate()
{

}

void Associate::SendAssociateRQ(AssociateRQPDU_NameSpace::AssociateRQPDU *associaterqpdu, AssociateParas associateparas)
{
    AssociateRQ associateRQ(associaterqpdu, associateparas.CallingAE, associateparas.CalledAE);
    conn = associateRQ.SendAssociateRQ(associateparas.SCPIP, associateparas.SCPPort);
}

void Associate::ReceiveAssociateAC(AssociateACPDU_NameSpace::AssociateACPDU *associateacpdu)
{
    AssociateAC associateAC(associateacpdu);
    associateAC.ReceiveAssociateAC(conn);
}
