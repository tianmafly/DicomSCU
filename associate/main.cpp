#include "associate.h"
#include "../pdu/pduassociaterq.h"
#include "../pdu/pduassociateac.h"
#include "../dimse/cfind/cfindrq.h"
#include "../type/uid.h"
#include "../dimse/dimse.h"
int main()
{
    AssociateRQPDU_NameSpace::AssociateRQPDU *associaterqpdu = new AssociateRQPDU_NameSpace::AssociateRQPDU();
    AssociateParas associateParas;
    associateParas.CallingAE = "TEST_AET";
    associateParas.CalledAE = "TEST_STORE";
    associateParas.SCPIP = "127.0.0.1";
    associateParas.SCPPort = 4100;

    AssociateACPDU_NameSpace::AssociateACPDU *associateacpdu = new AssociateACPDU_NameSpace::AssociateACPDU();

    Associate associate;
    associate.SendAssociateRQ(associaterqpdu, associateParas);
    associate.ReceiveAssociateAC(associateacpdu);
    
    vector<DcmElement> querykeylist;
    DcmElement queryRetrieveLevel;

    int tag = 0x00000000;
    string value = "STUDY";
    CDIMSE cDIMSE;
    memcpy(queryRetrieveLevel.tag, &tag, sizeof(queryRetrieveLevel.tag));
    cDIMSE.InitElementData(&queryRetrieveLevel, value.size(), (unsigned char*)value.c_str());

    DcmElement studyID;
    tag = 0x00000000;
    uint32_t value1 = 123;
    memcpy(studyID.tag, &tag, sizeof(studyID.tag));
    cDIMSE.InitElementData(&studyID, sizeof(value1), value1);

    querykeylist.push_back(queryRetrieveLevel);
    querykeylist.push_back(studyID);

    CFindRQ cFindRQ;
    cFindRQ.SendCFindRQPDU(querykeylist, CFindStudyRoot, 1);
    int x = 312;
}