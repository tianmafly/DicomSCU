#ifndef ASSOCIATEACPDU_H
#define ASSOCIATEACPDU_H


#include <vector>
#include <stdint.h>
#include <string>
using namespace std;

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
    char Reserved1;
    char Result;
    char Reserved2;
    SyntaxItem transferSyntax;
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
    char Reserved1[2];
    char Reserved2[16];
    char Reserved3[16];
    char Reserved4[32];

    ApplicationContexItem applicationContexItem;
    vector<PresentationContextItem> presentationContextItemlist;
    UserInfoItem userInfoItem;
};

#endif