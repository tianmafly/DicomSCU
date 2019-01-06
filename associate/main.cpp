#include "associate.h"
#include "../pdu/pduassociaterq.h"
#include "../pdu/pduassociateac.h"
#include "../dimse/cfind/cfindrq.h"
#include "../type/uid.h"
#include "../dimse/dimse.h"





void associate()
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
}

void cfind()
{
    vector<DcmElement> querykeylist;
    DcmElement queryRetrieveLevel;

    int tag = 0x00080052;
    string value = "STUDY";
    CDIMSE cDIMSE;
    cDIMSE.InitElementTag(&queryRetrieveLevel, tag);
    cDIMSE.InitElementData(&queryRetrieveLevel, value.size(), (unsigned char*)value.c_str());

    DcmElement studyID;
    tag = 0x00200010;
    string value1 = "123";
    cDIMSE.InitElementTag(&studyID, tag);
    cDIMSE.InitElementData(&studyID, value1.size(), (unsigned char*)value1.c_str());

    querykeylist.push_back(queryRetrieveLevel);
    querykeylist.push_back(studyID);

    CFindRQ cFindRQ;
    cFindRQ.SendCFindRQPDU(querykeylist, CFindStudyRoot, 1);
}

int main()
{
    
    cfind();
   
    int x = 312;
}