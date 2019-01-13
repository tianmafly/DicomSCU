#ifndef PDATATF_H
#define PDATATF_H

#include "../pdu/pdupdatatf.h"

using namespace PDUPDataTF_namespace;

struct PDV
{
    PresentationDataValue presentationDataValue;
    uint32_t len;
};

class PDataTF
{
public:
    PDataTF();
    ~PDataTF();
public:
    PDataTFPDU *InitDefaultPDataTFPDU(vector<DcmElement*> commandlist, int commandlen, vector<DcmElement*> dataset, int datasetlen, unsigned char presentationid);
private:
    PresentationDataValueItem InitPresentationDataValueItem(unsigned char presentationid, PDV pdv);
    PDV InitCommandPresentationDataValue(vector<DcmElement*> commandlist, int commandlen);
    PDV InitDataSetPresentationDataValue(vector<DcmElement*> dataset, int datasetlen);
private:
    PDataTFPDU *pDataTFPDU;
};


#endif // !PDATATF_H