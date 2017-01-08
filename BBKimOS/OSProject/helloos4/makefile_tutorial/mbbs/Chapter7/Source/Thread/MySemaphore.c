
#include "MySemaphore.h"

MySemaphoreT* NewSemaphore(MySemaphoreValueT a_initValue)
{
	MySemaphoreT* newSem = static_cast(MySemaphoreT*, malloc(sizeof(MySemaphoreT)));
	if ( !newSem )
	{
		_PET;PERROR("fail to alloc\n");
		return NULL;
	}

	if ( sem_init(newSem, 0, a_initValue) == -1 )
	{
		_PET;PERROR("fail to init semaphore\n");
		free(newSem);
		return NULL;
	}

	return newSem;
}

void DeleteSemaphore(MySemaphoreT* a_semaphore)
{
	if ( !a_semaphore )
	{
		_PDT;PDEBUG("a_semaphore is null\n");
		return;
	}

	sem_destroy(a_semaphore);
	free(a_semaphore);
	a_semaphore = NULL;
}

boolean LockSemaphore(MySemaphoreT* a_semaphore)
{
	if ( !a_semaphore )
	{
		_PDT;PDEBUG("a_semaphore is null\n");
		return false;
	}

	return sem_wait(a_semaphore) != -1;
}

boolean UnlockSemaphore(MySemaphoreT* a_semaphore)
{
	if ( !a_semaphore )
	{
		_PDT;PDEBUG("a_semaphore is null\n");
		return false;
	}

	return sem_post(a_semaphore) != -1;
}

