
#include "MyCommon.h"
#include "MySocket.h"
#include "MyMutex.h"
#include "MySemaphore.h"
#include "MyThread.h"

void* DoSomethingNiceProc(void* a_arg)
{
    _PET;PERROR("Do something nice...\n");

	return NULL;
}

INT32 main()
{
	MySemaphoreT* mySem = NewSemaphore(0);
	DeleteSemaphore(mySem);
	
	MyMutexT* myMutex = NewMutex();
	DeleteMutex(myMutex);
	
	MySocketT mySocket = CreateTcpSocket();
	close(mySocket);
	
	MyThreadT* myThread = NewThread(DoSomethingNiceProc, NULL, 512 * 1024 * 1024);
	DeleteThread(myThread);

	return 0;
}
