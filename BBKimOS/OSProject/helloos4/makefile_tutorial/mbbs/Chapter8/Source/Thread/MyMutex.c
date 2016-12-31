
#include <stdlib.h>

#include "MyMutex.h"

MyMutexT* NewMutex(void)
{
	MyMutexT* newMutex = static_cast(MyMutexT*, malloc(sizeof(MyMutexT)));
	if ( !newMutex )
	{
		_PET;PERROR("fail to alloc\n");
		return NULL;
	}
	
	pthread_mutex_init(newMutex, NULL);

	return newMutex;
}

void DeleteMutex(MyMutexT* a_mutex)
{
	if ( !a_mutex )
	{
		_PDT;PDEBUG("a_mutex is null\n");
		return;
	}

	UnlockMutex(a_mutex);

	pthread_mutex_destroy(a_mutex);
	free(a_mutex);
	a_mutex = NULL;
}

boolean LockMutex(MyMutexT* a_mutex)
{
	if ( !a_mutex )
	{
		_PDT;PDEBUG("a_semaphore is null\n");
		return false;
	}

	return pthread_mutex_lock(a_mutex) == 0;
}

boolean UnlockMutex(MyMutexT* a_mutex)
{
	if ( !a_mutex )
	{
		_PDT;PDEBUG("a_semaphore is null\n");
		return false;
	}

	return pthread_mutex_unlock(a_mutex) == 0;
}

