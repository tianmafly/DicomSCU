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
    void InitDefaultPDataTFPDU(CDIMSE *command, int commandlen, vector<DcmElement> *dataset, int datasetlen, unsigned char presentationid);
private:
    PresentationDataValueItem InitPresentationDataValueItem(unsigned char presentationid, PDV pdv);
    PDV InitCommandPresentationDataValue(CDIMSE *command, int commandlen);
    PDV InitDataSetPresentationDataValue(vector<DcmElement> *dataset, int datasetlen);
private:
    PDataTFPDU *pDataTFPDU;
};


#endif // !PDATATF_H