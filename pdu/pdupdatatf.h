#ifndef PDUPDATATF_H
#define PDUPDATATF_H


#include <stdint.h>
#include <vector>
#include "../pdatatf/dimse/dimse.h"
using namespace std;


namespace PDUPDataTF_namespace
{
    struct HeadItem
    {
        unsigned char pduType;
        unsigned char reserve;
        uint32_t pduLen;
    };

    struct PresentationDataValue
    {
        unsigned char messageControlHeader;
        vector<DcmElement> messageCommandOrDataSetFragment;
    };

    // PDV
    struct PresentationDataValueItem
    {
        uint32_t itemLen;
        unsigned char presentationID;

        PresentationDataValue presentationDataValue;
    };

    

    struct PDataTFPDU
    {
        HeadItem headItem;

        vector<PresentationDataValueItem> presentationDataValueItemList;

    };


}


















#endif // !CFIND_RQ_H