#ifndef DIMSE_H
#define DIMSE_H

#include <string.h>
#include<stdio.h>
#include <stdint.h>
#include <string>
using namespace std;


class ElementData
{
public:
	int len;
	unsigned char *data;
};

class DcmElement
{
public:
	unsigned char tag[4];
	ElementData vr;
	ElementData datalen;
	ElementData data;
};

class CDIMSE
{
public:
    CDIMSE(string transfersyntax);
    
public:
    void InitElementTag(DcmElement *dcmelement, uint16_t group, uint16_t element);
    void InitElementData(DcmElement *dcmelement, uint16_t len, const unsigned char * data);
    void InitElementData(DcmElement *dcmelement, uint32_t data);
    void InitElementData(DcmElement *dcmelement, uint16_t data);
    void InitElementData(DcmElement *dcmelement, uint8_t data);
private:
    void InitElementData(DcmElement *dcmelement, int len, void *data);
public:
    DcmElement  groupLength;
    DcmElement  affectedSOPClassUID;
    DcmElement  commandField;
    DcmElement  commandDataSetType;
private:
    string transfersyntax;
};

class CDIMSERQ : public CDIMSE
{
public:
    CDIMSERQ(string transfersyntax);
public:
    DcmElement  messageID;
    DcmElement  priority;
};

struct CDIMSERSP : public CDIMSE
{
public:
    CDIMSERSP(string transfersyntax);
public:
    DcmElement  messageIDBeingRespondedTo;
    DcmElement  status;
};



#endif // !DIMSE_H