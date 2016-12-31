
#include <sys/ioctl.h>

#include "MySocket.h"

boolean IsSocketValid(MySocketT a_socket)
{
	return a_socket > 0;
}

boolean IsSocketInvalid(MySocketT a_socket)
{
	return a_socket < 0;
}

INT32 CloseSocket(MySocketT a_socket)
{
	return close(a_socket);
}

const CHAR* ConvertNetworkAddressToString(const void* a_address, CHAR* a_string)
{
	return inet_ntop(AF_INET, a_address, a_string, sizeof(a_string));
}

INT32 ConvertStringToNetworkAddress(const CHAR* a_string, void* a_address)
{
	return inet_pton(AF_INET, a_string, a_address);
}

MySocketT OpenTcpSocket()
{
	return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

MySocketT OpenUdpSocket()
{
	return socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

boolean GetIpOfLocalNetworkDevice(const char* a_interface, char* a_ip, int a_size)
{
	int fd;
	struct ifreq ifr;
	struct sockaddr_in *aptr;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
	{
		_PET;PERROR("socket(2) failed\n");
		return false;
	}

	strncpy(ifr.ifr_name, a_interface, IFNAMSIZ);

	if (ioctl(fd, SIOCGIFADDR, &ifr) < 0)
	{
		_PET;PERROR("socket(2) failed\n");
		CloseSocket(fd);
		return false;
	}

	aptr = (struct sockaddr_in *)&ifr.ifr_addr;
	ConvertNetworkAddressToString(&aptr->sin_addr, a_ip);
	_PDT;PDEBUG("%s - %s\n", a_interface, a_ip);
	CloseSocket(fd);

	return true;
}

boolean GetMacOfLocalNetworkDevice(const char* a_interface, char* a_mac, unsigned int a_size)
{
	enum { COMMAND_MAX_LENGTH = 256 };
	enum { MAC_ADDRESS_LENGTH = 12 };
	char command[COMMAND_MAX_LENGTH];
	FILE* macFile = NULL;

	if ( !strlen(a_interface) )
	{
		_PET;PERROR("invalid interface name\n");
		return false;
	}

	if ( a_size < MAC_ADDRESS_LENGTH + 1 )
	{
		_PET;PERROR("too short buffer length for saving mac: %d\n", a_size);
		return false;
	}

	sprintf(command, "/sbin/ifconfig %s|grep HW|awk '{print $5}'|sed s/://g > /tmp/.mac", a_interface);
	_PDT;PDEBUG("command to get mac address: %s\n", command);
	system(command);

	macFile = fopen("/tmp/.mac", "r");
	if ( !macFile )
	{
		_PET;PERROR("fail to get mac\n");
		return false;
	}

	memset(a_mac, 0, MAC_ADDRESS_LENGTH + 1);
	fread(a_mac, MAC_ADDRESS_LENGTH, sizeof(char), macFile);
	fclose(macFile);

	system("rm /tmp/.mac");

	return true;
}


