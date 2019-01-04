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
    unsigned char* Syntax;
};

struct MaximumLengthItem
{
    ItemHead itemHead;
    uint32_t MaxLenReceived;
};

struct ApplicationContexItem
{
    ItemHead itemHead;
    unsigned char* AppicationContextName;
};

struct PresentationContextItem
{
    ItemHead itemHead;
    unsigned char PresentationContextID;
    unsigned char Reserved1;
    unsigned char Result;
    unsigned char Reserved2;
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
    unsigned char Reserved1[2];
    unsigned char Reserved2[16];
    unsigned char Reserved3[16];
    unsigned char Reserved4[32];

    ApplicationContexItem applicationContexItem;
    vector<PresentationContextItem> presentationContextItemlist;
    UserInfoItem userInfoItem;
};

}; // AssociateACPUD_NameSpace
#endif