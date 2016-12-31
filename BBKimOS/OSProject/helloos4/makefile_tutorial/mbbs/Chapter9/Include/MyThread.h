
/*!
	\file MyThread.h
	\brief Represents thread utiltiy

	MyThread는 은 리눅스에서  multi-threading을 수행하는 데 필요한 구조체 및 함수를 제공한다.
 
 */

#ifndef _MyThread_h_
#define _MyThread_h_

#include "MyCommon.h"

#include <pthread.h>
#include <semaphore.h>
#include "MyMutex.h"

typedef pthread_t _MyThreadT_;
typedef void* (* MyThreadProc)(void*);

typedef enum
{
	THREAD_RESULT_NULL = -1, 
	THREAD_RESULT_SUCCESS = 0 
} MyThreadResult;

typedef struct
{
	_MyThreadT_ m_handle;
	UINT32 m_stackSize;	// 0 if use default value
	MyThreadProc m_proc;
	void* m_data;
	INT32 m_result;
	boolean m_isRunning;
	boolean m_isToBeQuit;
} MyThreadT;

#ifdef __cplusplus
#define GetThreadData(a_type, a_thread) static_cast<a_type>(a_thread->m_data)
#define SetThreadData(a_thread, a_data) (a_thread->m_data = static_cast<void*>(a_data))
#else
#define GetThreadData(a_type, a_thread) static_cast(a_type, a_thread->m_data)
#define SetThreadData(a_thread, a_data) (a_thread->m_data = static_cast(void*, a_data))
#endif

#ifdef __cplusplus
extern "C" {
#endif

MyThreadT* NewThread(MyThreadProc a_proc, void* a_data, UINT32 a_stackSize);
int DeleteThread(MyThreadT* a_thread);
boolean IsThreadToBeQuit(MyThreadT* a_thread);
boolean IsThreadRunning(MyThreadT* a_thread);
const boolean* GetIsToBeQuitFlagOfThread(const MyThreadT* a_thread);
void SetThreadDone(MyThreadT* a_thread, int a_result);

void PrintThreadInfo(MyThreadT* a_thread);

#ifdef __cplusplus
}
#endif

#endif	// _MyThread_h_

