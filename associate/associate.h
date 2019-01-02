#ifndef ASSOCIATE_H
#define ASSOCIATE_H

#include "../pdu/pduassociaterq.h"
#include "../pdu/pduassociateac.h"
#include <string>
using namespace std;

struct AssociateParas
{
  string CallingAE;
  string CalledAE;
  string SCPIP;
  int SCPPort;
};


class Associate
{
  private:
    /* data */
  public:
    Associate(/* args */);
    ~Associate();

  public:
    void SendAssociateRQ(AssociateRQPDU_NameSpace::AssociateRQPDU *associaterqpdu, AssociateParas associateparas);
    void ReceiveAssociateAC(AssociateACPDU_NameSpace::AssociateACPDU *associateacpdu);
  private:
    int conn;
  
};

#endif
