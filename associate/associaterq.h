#ifndef ASSOCIATERQ_H
#define ASSOCIATERQ_H


#include "../pdu/associaterqpdu.h"
#include <string>

using namespace std;

class AssociateRQ
{
public:
    AssociateRQ(AssociateRQPDU *associaterqpdu, string callingae, string calledae);
    ~AssociateRQ();
public:
    void SendAssociateRQ(string ip, int port);
    
private:
    void InitDefaultAssociateRQPDU(AssociateRQPDU *associaterqpdu);
    void InitAssociateRQPDU(AssociateRQPDU *associaterqpdu, string callingae, string calledae);
    ApplicationContexItem InitApplicationContextItem();
    PresentationContextItem InitPresentationContextItem();
    UserInfoItem InitUserInfoItem(uint32_t maximumLength);

    SyntaxItem InitAbstractSyntax(string abstractSyntax);
    SyntaxItem InitTransferSyntax(string transferSyntax);
    MaximumLengthItem InitMaximumLength(uint32_t maximumlength);

private:
    int itemheadlength;
    AssociateRQPDU *associateRQPDU;
};

#endif
