#ifndef UID_H
#define UID_H

#include <string>
using namespace std;

//SOPClassUID
//QueryRetrieve
const string PatientRoot_QueryRetrieveInformationModel_FIND = "1.2.840.10008.5.1.4.1.2.1.1";
const string StudyRoot_QueryRetrieveInformationModel_FIND = "1.2.840.10008.5.1.4.1.2.2.1";

const string PatientRoot_QueryRetrieveInformationModel_MOVE = "1.2.840.10008.5.1.4.1.2.1.2";
const string StudyRoot_QueryRetrieveInformationModel_MOVE = "1.2.840.10008.5.1.4.1.2.2.2";

const string PatientRoot_QueryRetrieveInformationModel_GET = "1.2.840.10008.5.1.4.1.2.1.3";
const string StudyRoot_QueryRetrieveInformationModel_GET = "1.2.840.10008.5.1.4.1.2.2.3";


//TransferSyntaxUID
const string  ImplicitVRLittleEndian = "1.2.840.10008.1.2";
const string  ExplicitVRLittleEndian = "1.2.840.10008.1.2.1";
const string  ExplicitVRBigEndian = "1.2.840.10008.1.2.2";


enum CFindRoot 
{
    CFindPatientRoot = 1,
    CFindStudyRoot = 2
};

uint16_t CFindRQ_CommandType = 0x0020;
uint16_t CFindRSP_CommandType = 0x8020;
uint16_t CCancelFindRQ_CommandType = 0x0FFF;

uint16_t CGetRQ_CommandType = 0x0010;
uint16_t CGetRSP_CommandType = 0x8010;
uint16_t CCancelGetRQ_CommandType = 0x0FFF;

uint16_t CMoveRQ_CommandType = 0x0021;
uint16_t CMoveRSP_CommandType = 0x8021;
uint16_t CCancelMoveRQ_CommandType = 0x0FFF;
#endif