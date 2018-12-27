#include "../pdu/associaterqpdu.h"

class Associate
{
  private:
    /* data */
  public:
    Associate(/* args */);
    ~Associate();

  public:
    void SendAssociate();
    void ReceiveAssociate();
  private:
    void InitAssociationRQPDU(AssociateRQPDU *associateRQPDU);
  
};


