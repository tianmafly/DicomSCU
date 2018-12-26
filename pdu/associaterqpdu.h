#include <vector>
using namespace std;

struct PduHead
{
    char PduType;
    char Reserved;
    char PduLen[4];
};

struct ItemHead
{
    char ItemType[1];
    char Reserved[1];
    char ItemLen[2];
};

struct SyntaxItem
{
    ItemHead itemHead;
    char Syntax[64];
};

struct NegotiationSyntaxItem
{
    SyntaxItem abstractSyntax;
    vector<SyntaxItem> transferSyntax;
};

struct MaximumLengthItem
{
    ItemHead itemHead;
    char MaxLenReceived[4];
};

struct ApplicationContexItem
{
    ItemHead itemHead;
    char AppicationContextName[64];
};

struct PresentationContextItem
{
    ItemHead itemHead;
    char PresentationContextID[2];
    char Reserved[3];
    vector<NegotiationSyntaxItem> negotiationSyntaxItem;
};

struct UserInfoItem
{
    ItemHead itemHead;
    MaximumLengthItem maxLenItem;
};





struct AssociateRQPDU
{
    PduHead pduHead;

    char ProtocolVersion[2];
    char Reserved1[2];
    char CalledAE[16];
    char CallingAE[16];
    char Reserved2[32];

    ApplicationContexItem applicationContexItem;
    PresentationContextItem presentationContextItem;
    UserInfoItem userInfoItem;
};
