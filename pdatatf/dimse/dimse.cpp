#include "dimse.h"
#include "../../type/uid.h"



void DcmElementHandle::InitElementTag(DcmElement *dcmelement, uint16_t group, uint16_t element)
{
    memcpy(dcmelement->tag, &group, sizeof(group));
    memcpy(dcmelement->tag + sizeof(group), &element, sizeof(element));
    dcmelement->vr.len = ImplicitDataElementVRLength;
    dcmelement->vr.data = NULL;
}

void DcmElementHandle::InitElementData(DcmElement *dcmelement, uint32_t len, const unsigned char * data)
{
    // implicit elementlen is 4 bytes
    dcmelement->datalen.len = ImplicitDataElementValueLength;
    dcmelement->datalen.data = new unsigned char[dcmelement->datalen.len];
    if(len % 2 == 1)
        len += 1;
    memcpy(dcmelement->datalen.data, &len, dcmelement->datalen.len);
    
    dcmelement->data.len = len;
    dcmelement->data.data = new unsigned char[dcmelement->data.len];
    memcpy(dcmelement->data.data, data, dcmelement->data.len);
}

void DcmElementHandle::InitElementData(DcmElement *dcmelement, uint32_t data)
{
    InitElementData(dcmelement, sizeof(data), (unsigned char *)&data);
}

void DcmElementHandle::InitElementData(DcmElement *dcmelement, uint16_t data)
{
    InitElementData(dcmelement, sizeof(data), (unsigned char *)&data);
}

void DcmElementHandle::InitElementData(DcmElement *dcmelement, uint8_t data)
{
    InitElementData(dcmelement, sizeof(data), (unsigned char *)&data);
}

int DcmElementHandle::GetDcmElementLen(DcmElement dcmelement)
{
    return sizeof(dcmelement.tag) + dcmelement.vr.len + dcmelement.datalen.len + dcmelement.data.len;
}

// void DcmElementHandle::InitElementData(DcmElement *dcmelement, uint32_t len, void *data)
// {
//     dcmelement->datalen.len = ImplicitDataElementValueLength;
//     dcmelement->datalen.data = new unsigned char[dcmelement->datalen.len];
//     memcpy(dcmelement->datalen.data, &len, dcmelement->datalen.len);

//     dcmelement->data.len = len;
//     dcmelement->data.data = new unsigned char[dcmelement->data.len];
//     memcpy(dcmelement->data.data, data, dcmelement->data.len);
// }

CDIMSE::CDIMSE(string transfersyntax) 
{
    this->transfersyntax = transfersyntax;
    InitElementTag(&groupLength, 0x0000, 0x0000);
    InitElementTag(&affectedSOPClassUID, 0x0000, 0x0002);
    InitElementTag(&commandField, 0x0000, 0x0100);
    InitElementTag(&commandDataSetType, 0x0000, 0x0800);
}

CDIMSERQ::CDIMSERQ(string transfersyntax) : CDIMSE(transfersyntax)
{
    InitElementTag(&messageID, 0x0000, 0x0110);
    InitElementTag(&priority, 0x0000, 0x0700);
}

CDIMSERSP::CDIMSERSP(string transfersyntax) : CDIMSE(transfersyntax)
{
    InitElementTag(&messageIDBeingRespondedTo, 0x0000, 0x0120);
    InitElementTag(&status, 0x0000, 0x0900);
}