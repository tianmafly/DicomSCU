#include "dimse.h"

CDIMSE::CDIMSE() 
{
    InitElementTag(&groupLength, 0x00000000);
    InitElementTag(&affectedSOPClassUID, 0x00000002);
    InitElementTag(&commandField, 0x00000100);
    InitElementTag(&commandDataSetType, 0x00000800);
}

void CDIMSE::InitElementTag(DcmElement *dcmelement, uint32_t tag)
{
    memcpy(dcmelement->tag, &tag, sizeof(dcmelement->tag));
    dcmelement->vr.len = 0;
    dcmelement->vr.data = NULL;
}

void CDIMSE::InitElementData(DcmElement *dcmelement, uint16_t len, const unsigned char * data)
{
    dcmelement->datalen.len = 2;
    dcmelement->datalen.data = new unsigned char[dcmelement->datalen.len];
    memcpy(dcmelement->datalen.data, &len, dcmelement->datalen.len);
    
    dcmelement->data.len = len;
    dcmelement->data.data = new unsigned char[dcmelement->data.len];
    memcpy(dcmelement->data.data, data, dcmelement->data.len);
}

void CDIMSE::InitElementData(DcmElement *dcmelement, uint32_t data)
{
    InitElementData(dcmelement, sizeof(data), &data);
}

void CDIMSE::InitElementData(DcmElement *dcmelement, uint16_t data)
{
    InitElementData(dcmelement, sizeof(data), &data);
}

void CDIMSE::InitElementData(DcmElement *dcmelement, uint8_t data)
{
    InitElementData(dcmelement, sizeof(data), &data);
}

void CDIMSE::InitElementData(DcmElement *dcmelement, int len, void *data)
{
    dcmelement->datalen.len = 2;
    dcmelement->datalen.data = new unsigned char[dcmelement->datalen.len];
    memcpy(dcmelement->datalen.data, &len, dcmelement->datalen.len);

    dcmelement->data.len = len;
    dcmelement->data.data = new unsigned char[dcmelement->data.len];
    memcpy(dcmelement->data.data, data, dcmelement->data.len);
}

CDIMSERQ::CDIMSERQ()
{
    InitElementTag(&messageID, 0x00000110);
    InitElementTag(&priority, 0x00000700);
}

CDIMSERSP::CDIMSERSP()
{
    InitElementTag(&messageIDBeingRespondedTo, 0x00000120);
    InitElementTag(&status, 0x00000900);
}