
#include "MyMutex.h"

int main()
{
	MyMutexT* tmpMutex = NewMutex();
	if ( !tmpMutex )
	{
		_PET;PERROR("fail to create mutex\n");
		return -1;
	}

	if ( LockMutex(tmpMutex) )
	{
		_PET;PERROR("fail to lock mutex\n");
		DeleteMutex(tmpMutex);
		return -1;
	}

	if ( UnlockMutex(tmpMutex) )
	{
		_PET;PERROR("fail to unlock mutex\n");
		DeleteMutex(tmpMutex);
		return -1;
	}

	DeleteMutex(tmpMutex);

	return 0;
}
