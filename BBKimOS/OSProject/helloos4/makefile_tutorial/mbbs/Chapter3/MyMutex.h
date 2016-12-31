
#ifndef _MyMutex_h_
#define _MyMutex_h_ 1

#include "MyCommon.h"

#include <pthread.h>
typedef pthread_mutex_t MyMutexT;

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief mutex object를 생성 및 필요한 초기화를 수행한 다음 그 결과를 반환한다..

	\return 성공하면 생성된 mutex를 반환하고, 그렇지 않으면 NULL을 반환한다.
 */
MyMutexT* NewMutex(void);

/*! \brief 주어진 mutex object를 삭제한다.

	DeleteMutex()는 먼저 해당 mutex의 소유권을 반납한 다음 삭제한다.
	\param a_mutex 삭제할 mutex object에 대한 pointer.
 */
void DeleteMutex(MyMutexT* a_mutex);

/*! \brief 주어진 mutex object의 소유권을 획득한다.

	LockMutex()는 주어진 mutex object의 상태를 체크한다. 만약 LockMutex()가 호출되는 시점에, 해당
mutext object가 이미 다른 thread에 의해 소유되어 있다면, LockMutex()를 호출한 thread는 해당 mutext object
를 소유한 thread가 UnlockMutex()를 호출하여 소유권을 반납할 때까지 block된다. 하나 이상의 thread들이 block되어
있을 경우, 소유권을 가진 thread가 소유권을 반납하면, block된 thread들 중 하나만이 소유권을 소유하게 되면서
block이 풀리기 된다. (이때 어떤 thread가 소유권을 소유하게 될 지는 알 수 없다.)
<br><br>
	만약 이미 mutex object를 소유한 thread가 다시 LockMutex()를 호출하면, 해당 thread는 deadlock에 빠지게 된다.
만약 mutex object를 소유하지 않은 thread가 UnlockMutex()를 호출하면 정의되지 않은 일이 발생한다.

	\param a_mutex 소유권을 획득하고자 하는 mutex object에 대한 pointer.
	\return 성공하면 TRUE를, 그렇지 않으면 FALSE를 반환한다.
 */
boolean LockMutex(MyMutexT* a_mutex);

/*! \brief This function unlock the mutex.

	UnlockMutex()는 주어진 mutex object의 소유권을 반납한다. 하나 이상의 thread들이 LockMutex()를 호출하여
block되어 있을 때, UnlockMutex()가 호출되면, block된 thread들 중 하나가 소유권을 획득하여 block 상태에서
빠져 나오게 된다. (어떤 thread가 소유권을 소유하게 될 지는 알 수 없다.)

	\param a_mutex 소유권을 반납하고자 하는 mutex object에 대한 pointer.
	\return 성공하면 TRUE를, 그렇지 않으면 FALSE를 반환한다.
 */
boolean UnlockMutex(MyMutexT* a_mutex);

#ifdef __cplusplus
}
#endif

#endif // _MyMutex_h_

