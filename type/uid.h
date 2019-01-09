#ifndef UID_H
#define UID_H

#include <string>
using namespace std;

//SOPClassUID
//QueryRetrieve
static const string PatientRoot_QueryRetrieveInformationModel_FIND = "1.2.840.10008.5.1.4.1.2.1.1";
static const string StudyRoot_QueryRetrieveInformationModel_FIND = "1.2.840.10008.5.1.4.1.2.2.1";

static const string PatientRoot_QueryRetrieveInformationModel_MOVE = "1.2.840.10008.5.1.4.1.2.1.2";
static const string StudyRoot_QueryRetrieveInformationModel_MOVE = "1.2.840.10008.5.1.4.1.2.2.2";

static const string PatientRoot_QueryRetrieveInformationModel_GET = "1.2.840.10008.5.1.4.1.2.1.3";
static const string StudyRoot_QueryRetrieveInformationModel_GET = "1.2.840.10008.5.1.4.1.2.2.3";


//TransferSyntaxUID
static const string  ImplicitVRLittleEndian = "1.2.840.10008.1.2";
static const string  ExplicitVRLittleEndian = "1.2.840.10008.1.2.1";
static const string  ExplicitVRBigEndian = "1.2.840.10008.1.2.2";


enum CFindRoot 
{
    CFindPatientRoot = 1,
    CFindStudyRoot = 2
};

static const uint16_t CFindRQ_CommandType = 0x0020;
static const uint16_t CFindRSP_CommandType = 0x8020;
static const uint16_t CCancelFindRQ_CommandType = 0x0FFF;

static const uint16_t CGetRQ_CommandType = 0x0010;
static const uint16_t CGetRSP_CommandType = 0x8010;
static const uint16_t CCancelGetRQ_CommandType = 0x0FFF;

static const uint16_t CMoveRQ_CommandType = 0x0021;
static const uint16_t CMoveRSP_CommandType = 0x8021;
static const uint16_t CCancelMoveRQ_CommandType = 0x0FFF;


static const unsigned char ImplicitDataElementValueLength = 4;
static const unsigned char EmplicitDataElementValueLength = 2;
static const unsigned char EmplicitDataElementOBValueLength = 4;
#endif