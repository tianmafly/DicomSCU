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
    char PduType;
    char Reserved;
    uint32_t PduLen;
};

struct ItemHead
{
    char ItemType;
    char Reserved;
    uint16_t ItemLen;
};

struct SyntaxItem
{
    ItemHead itemHead;
    string Syntax;
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
    string AppicationContextName;
};

struct PresentationContextItem
{
    ItemHead itemHead;
    char PresentationContextID;
    char Reserved[3];
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
    char CalledAE[16];
    char CallingAE[16];
    char Reserved2[32];

    ApplicationContexItem applicationContexItem;
    vector<PresentationContextItem> presentationContextItemlist;
    UserInfoItem userInfoItem;
};

}; // AssociateRQPDU_NameSpace

#endif