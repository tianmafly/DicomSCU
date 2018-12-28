#include "associate.h"
#include <stdio.h>
#include <string.h>
#include "../type/uid.h"
#include "associaterq.h"

Associate::Associate(/* args */)
{

}

Associate::~Associate()
{

}

void Associate::SendAssociateRQ(AssociateRQPDU *associateRQPDU, AssociateParas associateParas)
{
    AssociateRQ associateRQ(associateRQPDU, associateParas.CallingAE, associateParas.CalledAE);
    associateRQ.SendAssociateRQ(associateParas.SCPIP, associateParas.SCPPort);
}

void Associate::ReceiveAssociateAC()
{

}
