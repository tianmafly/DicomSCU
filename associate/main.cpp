#include "associate.h"
#include "../pdu/pduassociaterq.h"
#include "../pdu/pduassociateac.h"
#include "../pdatatf/dimse/cfind/cfindrq.h"
#include "../type/uid.h"
#include "../pdatatf/dimse/dimse.h"
#include "../pdu/pduassociaterq.h"

struct AssociatedSyntax
{
    unsigned char PresentationID;
    string AbstractSyntax;
    string TransferSyntax;
};


int associate(string abstractsyntax, AssociateRQPDU_NameSpace::AssociateRQPDU *associaterqpdu, AssociateACPDU_NameSpace::AssociateACPDU *associateacpdu)
{
    AssociateParas associateParas;
    associateParas.CallingAE = "TEST_AET";
    associateParas.CalledAE = "TEST_STORE";
    associateParas.SCPIP = "127.0.0.1";
    associateParas.SCPPort = 4100;

    Associate associate;
    associate.SendAssociateRQ(associaterqpdu, associateParas, abstractsyntax);
    associate.ReceiveAssociateAC(associateacpdu);

    return associate.GetSocketConn();
}

void cfind(int conn, string transfersyntax, unsigned char presentationid)
{
    vector<DcmElement> querykeylist;
    DcmElement queryRetrieveLevel;

    string value = "STUDY";
    CDIMSE cDIMSE(transfersyntax);
    cDIMSE.InitElementTag(&queryRetrieveLevel, 0x0008, 0x0052);
    cDIMSE.InitElementData(&queryRetrieveLevel, value.size(), (unsigned char*)value.c_str());

    DcmElement studyID;
    string value1 = "123";
    cDIMSE.InitElementTag(&studyID, 0x0020, 0x0010);
    cDIMSE.InitElementData(&studyID, value1.size(), (unsigned char*)value1.c_str());

    querykeylist.push_back(queryRetrieveLevel);
    querykeylist.push_back(studyID);

    CFindRQ cFindRQ(conn, transfersyntax, presentationid);
    cFindRQ.SendCFindRQPDU(querykeylist, CFindStudyRoot);
}

vector<AssociatedSyntax> GetAssociatedSyntax( AssociateRQPDU_NameSpace::AssociateRQPDU *associaterqpdu, AssociateACPDU_NameSpace::AssociateACPDU *associateacpdu)
{
    vector<AssociatedSyntax> associatedsyntaxlist;
    for(int i=0; i<associateacpdu->presentationContextItemlist.size(); i++)
    {
        // 0 means ok
        if(associateacpdu->presentationContextItemlist[i].Result == 0)
        {
            AssociatedSyntax associatedsyntax;
            associatedsyntax.PresentationID = associateacpdu->presentationContextItemlist[i].PresentationContextID;
            associatedsyntax.TransferSyntax = (char *)associateacpdu->presentationContextItemlist[i].transferSyntax.Syntax;

            for(int j=0; j<associaterqpdu->presentationContextItemlist.size(); j++)
            {
                if(associatedsyntax.PresentationID == associaterqpdu->presentationContextItemlist[j].PresentationContextID)
                    associatedsyntax.AbstractSyntax = (char *)associaterqpdu->presentationContextItemlist[j].negotiationSyntaxItem.abstractSyntax.Syntax;
                    break;
            }
            associatedsyntaxlist.push_back(associatedsyntax);
        }
    }

    return associatedsyntaxlist;
}

int main()
{
    string AbstractSyntax = StudyRoot_QueryRetrieveInformationModel_FIND;
    AssociateRQPDU_NameSpace::AssociateRQPDU *associateRQPDU = new AssociateRQPDU_NameSpace::AssociateRQPDU();
    AssociateACPDU_NameSpace::AssociateACPDU *associateACPDU = new AssociateACPDU_NameSpace::AssociateACPDU();

    int conn = associate(AbstractSyntax, associateRQPDU, associateACPDU);

    vector<AssociatedSyntax> associatedsyntaxlist = GetAssociatedSyntax(associateRQPDU, associateACPDU);
    for(int i=0; i<associatedsyntaxlist.size(); i++)
    {
        if(associatedsyntaxlist[i].AbstractSyntax == AbstractSyntax)
        {
            cfind(conn, associatedsyntaxlist[i].TransferSyntax, associatedsyntaxlist[i].PresentationID);
            break;
        }
            
    }
    
    
    int x = 312;
}
