
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "MyThread.h"
#include "MyMutex.h"
#include "MySemaphore.h"

void MilliSleep(UINT32 a_milliSecs)
{
	usleep(a_milliSecs * 1000);
}

typedef struct _SyncData_
{
	INT32 m_value;
	INT32 m_value2;
	MyMutexT* m_mutex;
	MySemaphoreT* m_semaphore;
} SyncData;

void* ReadThreadProc(void* a_arg)
{
	MyThreadT* thread = static_cast(MyThreadT*, a_arg);

	if ( !a_arg )
	{
		_PET;PERROR("ERROR!! a_arg is NULL\n");
		SetThreadDone(thread, THREAD_RESULT_NULL);
		return 0;
	}
	
	while ( !IsThreadToBeQuit(thread) )
	{
		SyncData* syncData = GetThreadData(SyncData*, thread);
		if ( syncData->m_mutex )
		{
			LockMutex(syncData->m_mutex);
		}
		
		_PET;PERROR("(value, value2): (%d, %d)\n", syncData->m_value, syncData->m_value2);
		
		if ( syncData->m_mutex )
		{
			UnlockMutex(syncData->m_mutex);
		}
		
		MilliSleep(500);
	}

	SetThreadDone(thread, THREAD_RESULT_SUCCESS);
	return 0;
}

void* WriteThreadProc(void* a_arg)
{
	MyThreadT* thread = static_cast(MyThreadT*, a_arg);
	
	if ( !a_arg )
	{
		_PDT;PDEBUG("ERROR!! a_arg is NULL\n");
		SetThreadDone(thread, THREAD_RESULT_NULL);
		return 0;
	}

	while ( !IsThreadToBeQuit(thread) )
	{
		SyncData* syncData = GetThreadData(SyncData*, thread);

		if ( syncData->m_mutex )
		{
			LockMutex(syncData->m_mutex);
		}
		
		++(syncData->m_value);
		MilliSleep(500);
		++(syncData->m_value2);
		
		if ( syncData->m_mutex )
		{
			UnlockMutex(syncData->m_mutex);
		}
		_PET;PERROR("(value, value2): (%d, %d)\n", syncData->m_value, syncData->m_value2);
		MilliSleep(100);

		if ( syncData->m_value > 10 )
		{
			_PET;PERROR("Now it's time to stop\n");
			break;
		}
	}

	SetThreadDone(thread, THREAD_RESULT_SUCCESS);
	return 0;
}

int main(int a_argc, char** a_argv)
{
	SyncData syncData;
	MyThreadT* printThread = NULL;
	MyThreadT* increaseThread = NULL;

	syncData.m_value = syncData.m_value2 = 0;
	syncData.m_mutex = a_argc > 1 ? NewMutex() : NULL;
	syncData.m_semaphore = NULL;

	_PET;PERROR("\n\n *** TestThreadUsingMutex is started *** \n\n");
	
	printThread = NewThread(ReadThreadProc, &syncData, 0);
	increaseThread = NewThread(WriteThreadProc, &syncData, 0);

	_PET;PERROR("enter 'q' to quit\n");
	while ( true )
	{
		int input = getchar();
		if ( 'q' == input )
		{
			break;
		}
	}
	
	DeleteMutex(syncData.m_mutex);
	DeleteThread(printThread);
	DeleteThread(increaseThread);

	_PET;PERROR("\n\n *** TestThreadUsingMutex is ended *** \n\n");
	
	return 0;
}
