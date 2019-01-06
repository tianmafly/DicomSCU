#ifndef DIMSE_H
#define DIMSE_H

#include <string.h>
#include<stdio.h>
#include <stdint.h>


class ElementData
{
public:
	int len;
	unsigned char *data;
};

class DcmElement
{
public:
	char tag[4];
	ElementData vr;
	ElementData datalen;
	ElementData data;
};

class CDIMSE
{
public:
    CDIMSE();
    
public:
    void InitElementTag(DcmElement *dcmelement, uint32_t tag);
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
};

class CDIMSERQ : public CDIMSE
{
public:
    CDIMSERQ();
public:
    DcmElement  messageID;
    DcmElement  priority;
};

struct CDIMSERSP : public CDIMSE
{
public:
    CDIMSERSP();
public:
    DcmElement  messageIDBeingRespondedTo;
    DcmElement  status;
};



#endif // !DIMSE_H