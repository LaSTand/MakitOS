
/*!
	\file MySemaphore.h
	\brief Represents semaphore utility.
	
	A semaphore object is a synchronization object that maintains a value between zero and 
a specified maximum value. The value is decremented each time a thread locks a semaphore object 
and incremented each time a thread releases the semaphore. 
	When the value reaches zero, no more threads can successfully lock the semaphore object state 
to become signaled. The state of a semaphore is set to signaled when its value is greater than zero, 
and nonsignaled when its value is zero.
	The semaphore object is useful in controlling a shared resource that can support a limited number of users. 
It acts as a gate that limits the number of threads sharing the resource to a specified maximum number.
<br><br>
	MySemaphore supplies functions wrapping semaphore object in linux and windows. NewSemaphore()
creates a semaphore object, and DeleteSemaphore() destroies it. 
	A thread uses the NewSemaphore() function to create a semaphore object. The creating thread specifies 
the initial value. The initial value must be neither less than zero nor greater than SYT_SEMAPHORE_MAXCOUNT.
	A thread can decrement a semaphore's value more than once by repeatedly specifying the same semaphore 
object in calls to LockSemaphore(). And then, you can use UnlockSemaphore() to increment the value.
 */

#ifndef _MySemaphore_h_
#define _MySemaphore_h_ 1

#include "MyCommon.h"

#include <semaphore.h>

typedef sem_t MySemaphoreT;  /*!< type definition for handling semaphore in linux and WIN32 */
typedef UINT32 MySemaphoreValueT;  /*!< type definition for handling semaphore value in linux and WIN32 */

enum { MY_SEMAPHORE_MAXCOUNT = 128 };

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief This function constructs a semaphore object and returns it.

	NewSemaphore() initializes a semaphore with a_initValue. The state of a semaphore object is signaled 
when its value is greater than zero, and nonsignaled when its value is equal to zero. The a_initValue parameter 
specifies the initial value.
<br><br>
	Each time a blocked thread is available because of the semaphore's signaled state, the value of the semaphore
is decreased by one. Use the UnlockSemaphore() function to increment a semaphore's value by one. 
The value can never be less than zero or greater than SYT_SEMAPHORE_MAXCOUNT.

	\param a_initValue Initial counter value for the semaphore object. This value must be greater than 
or equal to zero and less than or equal to SYT_SEMAPHORE_MAXCOUNT.
	\return If the function succeeds, the return value is a pointer to the newly created semaphore object.
Otherwise, the return value is NULL.
 */
MySemaphoreT* NewSemaphore(MySemaphoreValueT a_initValue);

/*! \brief This function delete the semaphore indicated by a_semaphore.

	DeleteSemaphore() unlock the semaphore until all blocked threads are released, and then destroy it.

	\param a_semaphore pointer to a mutex object to be delete.
 */
void DeleteSemaphore(MySemaphoreT* a_semaphore);

/*! \brief This function lock the semaphore.

	LockSemaphore() shall lock the semaphore referenced by a_semaphore by performing a semaphore lock
operation on that semaphore. If the semaphore value is currently zero, then the calling thread shall be blocked
until one of other threads calls UnlockSemaphore().
by a signal.

	\param a_semaphore pointer to a mutex object to be delete.
	\return If the function succeeds, then the return value is TRUE. Otherwise, the return value is FALSE.
 */
boolean LockSemaphore(MySemaphoreT* a_semaphore);

/*! \brief This function unlock the semaphore.

	UnlockSemaphore() shall unlock the semaphore object referenced by a_semaphore. by performing a semaphore lock
operation on that semaphore. If UnlockSemaphore() is called, then the value of the semapore will be increased by one, 
that makes one of blocked threads, if any, becoming available. The scheduling policy shall determine which thread shall be
unblocked.

	\param a_semaphore pointer to a mutex object to be unlocked.
	\return If the function succeeds, then the return value is TRUE. Otherwise, the return value is FALSE.
 */
boolean UnlockSemaphore(MySemaphoreT* a_semaphore);

#ifdef __cplusplus
}
#endif

#endif // _MySemaphore_h_

