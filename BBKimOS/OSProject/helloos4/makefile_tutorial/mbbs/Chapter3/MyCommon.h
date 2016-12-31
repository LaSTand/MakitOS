
#ifndef _MyCommon_h_
#define _MyCommon_h_ 1

/* types */
#include "MyType.h"

/* debug info */
#include "MyDebug.h"

#ifndef __cplusplus
/* cast */
#define static_cast(TYPE, EXPR) ((TYPE)(EXPR))
#define const_cast(TYPE, EXPR) ((TYPE)(EXPR))
#endif

#define DS_UNUSED(x)	((void)(x))

#endif // _MyCommon_h_

