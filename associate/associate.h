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
    void InitAssociationRQPDU(AssociateRQPDU *associateRQPDU);
};


