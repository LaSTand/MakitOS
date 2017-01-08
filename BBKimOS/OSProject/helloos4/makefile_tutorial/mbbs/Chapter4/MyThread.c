
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "MyThread.h"

static boolean RunThread(MyThreadT* a_thread, UINT32 a_stackSize);
static void QuitThread(MyThreadT* a_thread);

MyThreadT* NewThread(MyThreadProc a_proc, void* a_data, UINT32 a_stackSize)
{
	MyThreadT* pThread = static_cast(MyThreadT*, malloc(sizeof(MyThreadT)));

	if ( !pThread )
	{
		_PET;PERROR("fail to alloc\n");
		return NULL;
	}
	
	pThread->m_handle = 0;
	pThread->m_stackSize = 0;
	pThread->m_isRunning = false;
	pThread->m_isToBeQuit = false;
	pThread->m_proc = a_proc;
	pThread->m_data = a_data;
	pThread->m_result = THREAD_RESULT_SUCCESS;
	
	if ( !RunThread(pThread, a_stackSize) )
	{
		free(pThread);
		pThread = NULL;
	}

	PrintThreadInfo(pThread);
	return pThread;
}

int DeleteThread(MyThreadT* a_thread)
{
	int result = THREAD_RESULT_SUCCESS;
	if ( !a_thread )
	{
		_PDT;PDEBUG("a_thread is null\n");
		return THREAD_RESULT_NULL;
	}

	QuitThread(a_thread);
	result = a_thread->m_result;

	free(a_thread);
	a_thread = NULL;

	return result;
}

static boolean RunThread(MyThreadT* a_thread, UINT32 a_stackSize)
{
	boolean failToCreateThread;
	pthread_attr_t attr;
	
	if ( !a_thread )
	{
		_PDT;PDEBUG("a_thread is null\n");
		return false;
	}

	if ( a_stackSize > 0 )
	{
		a_thread->m_stackSize = a_stackSize;
	}
	
	if ( pthread_attr_init(&attr) != 0 )
	{
		_PET;PERROR("Error in pthread_attr_init\n");
		return false;
	}

	if ( a_stackSize )
	{
		if ( pthread_attr_setstacksize(&attr, a_thread->m_stackSize) != 0 )
		{
			_PET;PERROR("Error in pthread_attr_setstacksize\n");
			return false;
		}
	}
	
	failToCreateThread = (pthread_create(&a_thread->m_handle, &attr, a_thread->m_proc, a_thread) != 0);

	if ( failToCreateThread )
	{
		_PET;PERROR("fail to alloc\n");
		return false;
	}

	a_thread->m_isRunning = true;

	_PDT; PDEBUG("MyThreadT(%lu) has been created to run\n", a_thread->m_handle);
	return true;
}

static void QuitThread(MyThreadT* a_thread)
{
	if ( !a_thread )
	{
		_PDT;PDEBUG("a_thread is null\n");
		return;
	}

	if ( !IsThreadToBeQuit(a_thread) )
	{
		a_thread->m_isToBeQuit = true;
		_PDT; PDEBUG("m_isToBeQuit flag(%d) of MyThreadT(%lu) has been set to true\n", a_thread->m_isToBeQuit, a_thread->m_handle);
	}
	
	pthread_join(a_thread->m_handle, NULL);

	a_thread->m_handle = 0;

	_PDT; PDEBUG("MyThreadT(%lu) has been quit\n", a_thread->m_handle);
}

boolean IsThreadToBeQuit(MyThreadT* a_thread)
{
	return !a_thread || a_thread->m_isToBeQuit;
}

boolean IsThreadRunning(MyThreadT* a_thread)
{
	return a_thread && a_thread->m_isRunning;
}

const boolean* GetIsToBeQuitFlagOfThread(const MyThreadT* a_thread)
{
	return a_thread ? &a_thread->m_isToBeQuit : NULL;
}

void SetThreadDone(MyThreadT* a_thread, int a_result)
{
	if ( a_thread )
	{
		a_thread->m_isRunning = false;
		a_thread->m_result = a_result;
	}
}

void PrintThreadInfo(MyThreadT* a_thread)
{
	if ( !a_thread )
	{
		_PDT;PDEBUG("a_thread is null\n");
		return;
	}

	_PDT; PDEBUG("thread info\n");
	PDEBUG("\t running:\t%d\n", a_thread->m_isRunning);
	PDEBUG("\t be quit:\t%d\n", a_thread->m_isToBeQuit);
	PDEBUG("\t stack size:\t%d\n", a_thread->m_stackSize);
	PDEBUG("\t handle:\t%ld\n", a_thread->m_handle);
	PDEBUG("\t proc:\t%p\n", a_thread->m_proc);
	PDEBUG("\t data:\t%p\n", a_thread->m_data);
	PDEBUG("\t result:\t%d\n", a_thread->m_result);
}

