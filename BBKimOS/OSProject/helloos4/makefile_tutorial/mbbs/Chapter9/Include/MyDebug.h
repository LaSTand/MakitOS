
#ifndef _MyDebug_h_
#define _MyDebug_h_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_DEBUG) && defined(ACTIVATE_PDEBUG)
#define PDEBUG_ACTIVATED
#	ifdef __KERNEL__
#		define PDEBUG(fmt, args...) printk(fmt , ##args)
#	else
#		define PDEBUG(fmt, args...) fprintf(stdout, fmt, ##args)
#	endif
#else
#	define PDEBUG(fmt,args...)
#endif

#define PERROR(fmt, args...) fprintf(stdout, fmt, ##args)

#define _PET PERROR("[%s:%s(%d)]\t", __FUNCTION__, __FILE__, __LINE__)
#define _PEL PERROR("[%s:%s(%d)]\n", __FUNCTION__, __FILE__, __LINE__)
#define _PDL PDEBUG("[%s:%s(%d)]\n", __FILE__, __FUNCTION__, __LINE__)
#define _PDT PDEBUG("[%s:%s(%d)]\t", __FILE__, __FUNCTION__, __LINE__)

#define _BEGIN(X) PDEBUG("[%s:%s(%d)] >>> %s\n", __FILE__, __FUNCTION__, __LINE__, X)
#define _END(X) PDEBUG("[%s:%s(%d)] <<< %s\n", __FILE__, __FUNCTION__, __LINE__, X)
 
#define _ENTER PDEBUG("[%s:%s(%d)] >>> \n", __FILE__, __FUNCTION__, __LINE__)
#define _EXIT  PDEBUG("[%s:%s(%d)] <<< \n", __FILE__, __FUNCTION__, __LINE__)

#endif // _MyDebug_h_

