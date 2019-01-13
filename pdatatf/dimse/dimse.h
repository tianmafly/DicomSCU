#ifndef DIMSE_H
#define DIMSE_H

#include <string.h>
#include<stdio.h>
#include <stdint.h>
#include <string>
using namespace std;
/*
P-DATA-PUD和Associate一样是大端传输.服务端截取的内存,直接转换为整数,所以是按照大端来解析
DIMSE是0000组,是隐式小端传输
Identitor是从0x0008组开始,要按照协商的transfer来传输
*/

class ElementData
{
public:
	uint32_t len;
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

class DcmElementHandle
{
public:
    void InitElementTag(DcmElement *dcmelement, uint16_t group, uint16_t element);
    void InitElementData(DcmElement *dcmelement, uint32_t len, const unsigned char * data);
    void InitElementData(DcmElement *dcmelement, uint32_t data);
    void InitElementData(DcmElement *dcmelement, uint16_t data);
    void InitElementData(DcmElement *dcmelement, uint8_t data);

    int GetDcmElementLen(DcmElement dcmelement);

private:
    // void InitElementData(DcmElement *dcmelement, uint32_t len, void *data);
};

class CDIMSE : public DcmElementHandle
{
public:
    CDIMSE(string transfersyntax);

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

class CDIMSERSP : public CDIMSE
{
public:
    CDIMSERSP(string transfersyntax);
public:
    DcmElement  messageIDBeingRespondedTo;
    DcmElement  status;
};



#endif // !DIMSE_H