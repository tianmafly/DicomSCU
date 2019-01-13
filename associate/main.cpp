#include "associate.h"
#include "../pdu/pduassociaterq.h"
#include "../pdu/pduassociateac.h"
#include "../pdatatf/dimse/cfind/cfindrq.h"
#include "../type/uid.h"
#include "../pdatatf/dimse/dimse.h"
#include "../pdu/pduassociaterq.h"
#include "../pdatatf/dimse/cfind/cfindrsp.h"
#include "../pdatatf/dimse/cmove/cmoverq.h"

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
    vector<DcmElement*> querykeylist;

    DcmElement queryRetrieveLevel;
    string queryRetrieveLevelValue = "STUDY";
    CDIMSE cDIMSE(transfersyntax);
    cDIMSE.InitElementTag(&queryRetrieveLevel, 0x0008, 0x0052);
    cDIMSE.InitElementData(&queryRetrieveLevel, queryRetrieveLevelValue.size(), (unsigned char*)queryRetrieveLevelValue.c_str());

    DcmElement studyID;
    string studyIDValue = "3075905";
    cDIMSE.InitElementTag(&studyID, 0x0020, 0x0010);
    cDIMSE.InitElementData(&studyID, studyIDValue.size(), (unsigned char*)studyIDValue.c_str());

    DcmElement studyInstanceUID;
    string studyInstanceUIDValue = "";
    cDIMSE.InitElementTag(&studyInstanceUID, 0x0020, 0x000D);
    cDIMSE.InitElementData(&studyInstanceUID, studyInstanceUIDValue.size(), (unsigned char*)studyInstanceUIDValue.c_str());

    querykeylist.push_back(&queryRetrieveLevel);
    querykeylist.push_back(&studyID);
    querykeylist.push_back(&studyInstanceUID);

    CFindRQ cFindRQ(conn, transfersyntax, presentationid);
    cFindRQ.DIMSE_SendPDataTfPDU(querykeylist, StudyRoot);

    CFindRSP cFindRSP;
    vector<CFindRSPResult> cFindRSPResultList = cFindRSP.ReceiveCFindRsp(conn, transfersyntax);
    int a = 3;
}

void cmove(int conn, string transfersyntax, unsigned char presentationid, string studyinstanceuid)
{
    vector<DcmElement*> querykeylist;

    DcmElement queryRetrieveLevel;
    string queryRetrieveLevelValue = "STUDY";
    CDIMSE cDIMSE(transfersyntax);
    cDIMSE.InitElementTag(&queryRetrieveLevel, 0x0008, 0x0052);
    cDIMSE.InitElementData(&queryRetrieveLevel, queryRetrieveLevelValue.size(), (unsigned char*)queryRetrieveLevelValue.c_str());

    DcmElement studyInstanceUID;
    string studyInstanceUIDValue = studyinstanceuid;
    cDIMSE.InitElementTag(&studyInstanceUID, 0x0020, 0x000D);
    cDIMSE.InitElementData(&studyInstanceUID, studyInstanceUIDValue.size(), (unsigned char*)studyInstanceUIDValue.c_str());

    querykeylist.push_back(&queryRetrieveLevel);
    querykeylist.push_back(&studyInstanceUID);

    string AE = "TEST_AEM";
    CMoveRQ cMoveRQ(conn, transfersyntax, presentationid, AE);
    cMoveRQ.DIMSE_SendPDataTfPDU(querykeylist, StudyRoot);

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

void CFindOperate()
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
}

void CMoveOperate()
{
    string AbstractSyntax = StudyRoot_QueryRetrieveInformationModel_MOVE;
    AssociateRQPDU_NameSpace::AssociateRQPDU *associateRQPDU = new AssociateRQPDU_NameSpace::AssociateRQPDU();
    AssociateACPDU_NameSpace::AssociateACPDU *associateACPDU = new AssociateACPDU_NameSpace::AssociateACPDU();

    int conn = associate(AbstractSyntax, associateRQPDU, associateACPDU);

    vector<AssociatedSyntax> associatedsyntaxlist = GetAssociatedSyntax(associateRQPDU, associateACPDU);
    for(int i=0; i<associatedsyntaxlist.size(); i++)
    {
        if(associatedsyntaxlist[i].AbstractSyntax == AbstractSyntax)
        {
            string StudyInstanceUID = "1.2.840.113619.186.80861568102.20180319190234143.549";
            cmove(conn, associatedsyntaxlist[i].TransferSyntax, associatedsyntaxlist[i].PresentationID, StudyInstanceUID);
            break;
        }
            
    }
}

int main()
{
    // CFindOperate();
    CMoveOperate();
    
    int x = 312;
}
