#ifndef ASSOCIATE_H
#define ASSOCIATE_H

#include "../pdu/associaterqpdu.h"
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
    void SendAssociateRQ(AssociateRQPDU *associateRQPDU, AssociateParas associateParas);
    void ReceiveAssociateAC();
  private:
    
  
};

#endif
