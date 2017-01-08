
#ifndef _MySocket_h_
#define _MySocket_h_

#include <sys/types.h>
#include <sys/socket.h>		// basic socket definitions
#include <sys/time.h>		// timeval{} for select()
#include <netinet/in.h>		// struct sockaddr_in, htonl()
#include <arpa/inet.h>		// inet_aton(), inet_ntoa(), inet_pton(), inet_ntop()
#include <unistd.h>
#include <ctype.h>
#include <netdb.h>
#include <net/if.h>

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

#include "MyCommon.h"

typedef INT32 MySocketT;
#ifdef __cplusplus
extern "C" {
#endif

enum { INVALID_SOCKET = -1 };
boolean IsSocketValid(MySocketT a_socket);
boolean IsSocketInvalid(MySocketT a_socket);
INT32 CloseSocket(MySocketT a_socket);
const CHAR* ConvertNetworkAddressToString(const void* a_address, CHAR* a_string);
INT32 ConvertStringToNetworkAddress(const CHAR* a_string, void* a_address);

MySocketT CreateTcpSocket(void);
MySocketT CreateUdpSocket(void);

boolean GetIpOfLocalNetworkDevice(const char* a_interface, char* a_ip, int a_size);
boolean GetMacOfLocalNetworkDevice(const char* a_interface, char* a_mac, unsigned int a_size);

#ifdef __cplusplus
}
#endif

#endif // _MySocket_h_

