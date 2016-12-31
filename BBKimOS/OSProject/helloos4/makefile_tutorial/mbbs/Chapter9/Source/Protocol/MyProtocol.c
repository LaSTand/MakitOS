
#include "MyProtocol.h"

void InitCommand(MyCommandT* a_command)
{
	if ( !a_command )
	{
		_PET;PERROR("invalid command\n");
		return;
	}
	_PET;PERROR("init command...\n");
}
