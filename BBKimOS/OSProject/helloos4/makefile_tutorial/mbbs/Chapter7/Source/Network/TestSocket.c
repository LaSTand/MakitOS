
#include "MySocket.h"

INT32 main()
{
	MySocketT udpSocket = OpenUdpSocket();
	if ( IsSocketInvalid(udpSocket) )
	{
		_PET;PERROR("fail to open udp socket\n");
		return -1;
	}

	CloseSocket(udpSocket);

	return 0;
}
