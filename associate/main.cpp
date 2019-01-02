#include "associate.h"
#include "../pdu/pduassociaterq.h"
#include "../pdu/pduassociateac.h"
int main()
{
    AssociateRQPDU_NameSpace::AssociateRQPDU *associaterqpdu = new AssociateRQPDU_NameSpace::AssociateRQPDU();
    AssociateParas associateParas;
    associateParas.CallingAE = "TEST_AET";
    associateParas.CalledAE = "TEST_STORE";
    associateParas.SCPIP = "127.0.0.1";
    associateParas.SCPPort = 4100;

    AssociateACPDU_NameSpace::AssociateACPDU *associateacpdu = new AssociateACPDU_NameSpace::AssociateACPDU();

    Associate associate;
    associate.SendAssociateRQ(associaterqpdu, associateParas);
    associate.ReceiveAssociateAC(associateacpdu);
    
}