#ifndef ASSOCIATERQ_H
#define ASSOCIATERQ_H


#include "../pdu/pduassociaterq.h"
#include <string>

using namespace std;
using namespace AssociateRQPDU_NameSpace;


class AssociateRQ
{
public:
    AssociateRQ(AssociateRQPDU *associaterqpdu, string callingae, string calledae);
    ~AssociateRQ();
public:
    int SendAssociateRQ(string ip, int port);
    
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
