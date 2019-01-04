#ifndef PDUASSOCIATERQ_H
#define PDUASSOCIATERQ_H


#include <vector>
#include <stdint.h>
#include <string>
using namespace std;


namespace AssociateRQPDU_NameSpace
{
struct PduHead
{
    unsigned char PduType;
    unsigned char Reserved;
    uint32_t PduLen;
};

struct ItemHead
{
    unsigned char ItemType;
    unsigned char Reserved;
    uint16_t ItemLen;
};

struct SyntaxItem
{
    ItemHead itemHead;
    unsigned char *Syntax;
};

struct NegotiationSyntaxItem
{
    SyntaxItem abstractSyntax;
    vector<SyntaxItem> transferSyntaxlist;
};

struct MaximumLengthItem
{
    ItemHead itemHead;
    uint32_t MaxLenReceived;
};

struct ApplicationContexItem
{
    ItemHead itemHead;
    unsigned char *AppicationContextName;
};

struct PresentationContextItem
{
    ItemHead itemHead;
    unsigned char PresentationContextID;
    unsigned char Reserved[3];
    NegotiationSyntaxItem negotiationSyntaxItem;
};

struct UserInfoItem
{
    ItemHead itemHead;
    MaximumLengthItem maxLenItem;
};





struct AssociateRQPDU
{
    PduHead pduHead;

    uint16_t ProtocolVersion;
    uint16_t Reserved1;
    unsigned char CalledAE[16];
    unsigned char CallingAE[16];
    unsigned char Reserved2[32];

    ApplicationContexItem applicationContexItem;
    vector<PresentationContextItem> presentationContextItemlist;
    UserInfoItem userInfoItem;
};

}; // AssociateRQPDU_NameSpace

#endif