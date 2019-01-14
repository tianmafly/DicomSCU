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

int DcmElementHandle::GetDcmElementLen(DcmElement *dcmelement)
{
    return sizeof(dcmelement->tag) + dcmelement->vr.len + dcmelement->datalen.len + dcmelement->data.len;
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

    groupLength = new DcmElement();
    affectedSOPClassUID = new DcmElement();
    commandField = new DcmElement();
    commandDataSetType = new DcmElement();

    InitElementTag(groupLength, 0x0000, 0x0000);
    InitElementTag(affectedSOPClassUID, 0x0000, 0x0002);
    InitElementTag(commandField, 0x0000, 0x0100);
    InitElementTag(commandDataSetType, 0x0000, 0x0800);
}

CDIMSERQ::CDIMSERQ(string transfersyntax) : CDIMSE(transfersyntax)
{
    messageID = new DcmElement();
    priority = new DcmElement();
    InitElementTag(messageID, 0x0000, 0x0110);
    InitElementTag(priority, 0x0000, 0x0700);

    dcmElemenetList.push_back(groupLength);
    dcmElemenetList.push_back(affectedSOPClassUID);
    dcmElemenetList.push_back(commandField);
    dcmElemenetList.push_back(messageID);
    dcmElemenetList.push_back(priority);
    dcmElemenetList.push_back(commandDataSetType);
}

CDIMSERSP::CDIMSERSP(string transfersyntax) : CDIMSE(transfersyntax)
{
    messageIDBeingRespondedTo = new DcmElement();
    InitElementTag(messageIDBeingRespondedTo, 0x0000, 0x0120);
    status = new DcmElement();
    InitElementTag(status, 0x0000, 0x0900);

    dcmElemenetList.push_back(groupLength);
    dcmElemenetList.push_back(affectedSOPClassUID);
    dcmElemenetList.push_back(commandField);
    dcmElemenetList.push_back(messageIDBeingRespondedTo);
    dcmElemenetList.push_back(commandDataSetType);
    dcmElemenetList.push_back(status);
}