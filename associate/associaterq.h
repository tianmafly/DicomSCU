#ifndef ASSOCIATERQ_H
#define ASSOCIATERQ_H


#include "../pdu/pduassociaterq.h"
#include <string>

using namespace std;
using namespace AssociateRQPDU_NameSpace;


class AssociateRQ
{
public:
    AssociateRQ(AssociateRQPDU *associaterqpdu, string callingae, string calledae, string abstractsyntax);
    ~AssociateRQ();
public:
    int SendAssociateRQ(string ip, int port);
    
private:
    void InitDefaultAssociateRQPDU(AssociateRQPDU *associaterqpdu, string abstractsyntax);
    void InitAssociateRQPDU(AssociateRQPDU *associaterqpdu, string callingae, string calledae, string abstractsyntax);
    ApplicationContexItem InitApplicationContextItem();
    PresentationContextItem InitPresentationContextItem(string abstractsyntax);
    UserInfoItem InitUserInfoItem(uint32_t maximumLength);

    SyntaxItem InitAbstractSyntax(string abstractSyntax);
    SyntaxItem InitTransferSyntax(string transferSyntax);
    MaximumLengthItem InitMaximumLength(uint32_t maximumlength);

private:
    int itemheadlength;
    AssociateRQPDU *associateRQPDU;
};

#endif
