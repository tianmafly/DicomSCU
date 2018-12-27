#include "../pdu/associaterqpdu.h"
#include <string>

using namespace std;

class AssociateRQ
{
private:
    /* data */
public:
    AssociateRQ(/* args */);
    ~AssociateRQ();
public:
    void InitAssociateRQPDU(AssociateRQPDU *associateRQPDU);
    ApplicationContexItem InitApplicationContextItem();
    PresentationContextItem InitPresentationContextItem();
    UserInfoItem InitUserInfoItem();
private:
    SyntaxItem InitAbstractSyntax(string abstractSyntax);
    SyntaxItem InitTransferSyntax(string transferSyntax);
};


