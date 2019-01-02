#ifndef PDUASSOCIATEAC_H
#define PDUASSOCIATEAC_H


#include <vector>
#include <stdint.h>
#include <string>
using namespace std;


namespace AssociateACPDU_NameSpace
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
    char* Syntax;
};

struct MaximumLengthItem
{
    ItemHead itemHead;
    uint32_t MaxLenReceived;
};

struct ApplicationContexItem
{
    ItemHead itemHead;
    char* AppicationContextName;
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





struct AssociateACPDU
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

}; // AssociateACPUD_NameSpace
#endif