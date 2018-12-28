#include "associate.h"

int main()
{
    AssociateRQPDU *associateRQPDU = new AssociateRQPDU();
    AssociateParas associateParas;
    associateParas.CallingAE = "TEST_SCU";
    associateParas.CalledAE = "TEST_SCP";
    associateParas.SCPIP = "127.0.0.1";
    associateParas.SCPPort = 4100;

    Associate associate;
    associate.SendAssociateRQ(associateRQPDU, associateParas);

    delete associateRQPDU;
    associateRQPDU = NULL;
}