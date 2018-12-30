#ifndef DUL_H
#define DUL_H

#include "../socket/socket.h"
#include "../pdu/associaterqpdu.h"

struct Data
{
  char* buffer;
  int len;
};

class AssociateRQDUL
{
public:
  AssociateRQDUL(string ip, int port);
  ~AssociateRQDUL();

public:
  void DUL_sendAssociateRQ(AssociateRQPDU *associaterqpdu);
  void DUL_ReceiveAssociateAC();
private:
  void DUL_GetAssociateRQPUDMemory(AssociateRQPDU *associaterqpdu);
  void DUL_GetApplicationContexItemMemory(ApplicationContexItem *applicationcontexitem);
  void DUL_GetPresentationContextItemMemory(PresentationContextItem *presentationcontextitem);
  void DUL_GetUserInfoItemItemMemory(UserInfoItem *userinfoitem);


  void DUL_GetAbstractSyntaxMemory(SyntaxItem *abstractsyntaxitem);
  void DUL_GetTransferSyntaxMemory(SyntaxItem *transfersyntaxitem);
  void DUL_GetMaximumLengthItemMemory(MaximumLengthItem *maximumlengthitem);
  void DUL_GetBufferFromPoint(const char *data, int len);
  void DUL_GetBufferFromInt(int data, int len);

private:
  TcpSocket *tcpSocket;
  int conn;
  Data associatedata;
  int index;
};

#endif