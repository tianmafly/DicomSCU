#include "associate.h"
#include "../pdu/associaterqpdu.h"

int main()
{
    AssociateRQPDU *associateRQPDU = new AssociateRQPDU();
    AssociateParas associateParas;
    associateParas.CallingAE = "TEST_AET";
    associateParas.CalledAE = "TEST_STORE";
    associateParas.SCPIP = "127.0.0.1";
    associateParas.SCPPort = 4100;

    Associate associate;
    associate.SendAssociateRQ(associateRQPDU, associateParas);

    delete associateRQPDU;
    associateRQPDU = NULL;
}