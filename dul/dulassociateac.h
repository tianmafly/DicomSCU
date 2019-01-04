#ifndef DULASSOCIATEAC_H
#define DULASSOCIATEAC_H

#include "../socket/socket.h"
#include "../pdu/pduassociateac.h"

using namespace AssociateACPDU_NameSpace;

struct Data
{
  char* buffer;
  int len;
};

class AssociateACDUL
{
public:
  AssociateACDUL(int conn);
  ~AssociateACDUL();

public:
  void DUL_ReceiveAssociateAC(AssociateACPDU *associateacpdu);
private:
  void DUL_GetAssociateACPUDHead(AssociateACPDU *associateacpdu, unsigned char *pduhead);
  void DUL_GetAssociateRQBodyPUD(AssociateACPDU *associateacpdu);
  void DUL_GetApplicationContexItem(ApplicationContexItem *applicationcontexitem);
  void DUL_GetPresentationContextItem(PresentationContextItem *presentationcontextitem);
  void DUL_GetUserInfoItemItem(UserInfoItem *userinfoitem);

  void DUL_GetTransferSyntax(SyntaxItem *transfersyntaxitem);
  void DUL_GetMaximumLengthItem(MaximumLengthItem *maximumlengthitem);
  void DUL_GetItemHead(ItemHead * itemhead);
  void DUL_GetPointFromBuffer(unsigned char *data, int len);
  void DUL_GetIntFromBuffer(uint16_t *data, int len);
  void DUL_GetIntFromBuffer(uint32_t *data, int len);
private:
  TcpSocket *tcpSocket;
  int conn;
  Data associatedata;
  unsigned char *pdubody;
  int index;
};

#endif