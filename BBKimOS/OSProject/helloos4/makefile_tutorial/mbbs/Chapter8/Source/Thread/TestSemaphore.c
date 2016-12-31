
#include "MySemaphore.h"

int main()
{
	MySemaphoreT* tmpSem = NewSemaphore(1);
	if ( !tmpSem )
	{
		_PET;PERROR("fail to create semaphore\n");
		return -1;
	}

	if ( LockSemaphore(tmpSem) )
	{
		_PET;PERROR("fail to lock semaphre\n");
		DeleteSemaphore(tmpSem);
		return -1;
	}

	if ( UnlockSemaphore(tmpSem) )
	{
		_PET;PERROR("fail to unlock semaphore\n");
		DeleteSemaphore(tmpSem);
		return -1;
	}

	DeleteSemaphore(tmpSem);

	return 0;
}
