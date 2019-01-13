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

//PDV
static const uint8_t PDVCommand = 0b00000001;
static const uint8_t PDVCommandLastFragment = 0b00000011;
static const uint8_t PDVDataSet = 0b00000000;
static const uint8_t PDVDataSetLastFragment = 0b00000010;

enum QueryRetrieveRoot 
{
    PatientRoot = 1,
    StudyRoot = 2
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

static const unsigned char ImplicitDataElementVRLength = 0;
static const unsigned char EmplicitDataElementVRLength = 2;
static const unsigned char EmplicitDataElementOBVRLength = 4;

static const uint16_t Sucess_Status = 0x0000;
static const uint16_t Pending_OK_Status = 0xFF00;
static const uint16_t Pending_Warn_Status = 0xFF01;
static const uint16_t Cancel_Status = 0xFE00;
static const uint16_t OutofResource_Status = 0xA700;
static const uint16_t IdentifierDoesNotMatchSOPClass_Status = 0xA900;
static const uint16_t UnableToProcess_Status = 0xC000;
#endif