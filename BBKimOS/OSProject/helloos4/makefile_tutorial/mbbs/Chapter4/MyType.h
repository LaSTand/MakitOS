
#ifndef _MyType_h_
#define _MyType_h_ 1

typedef signed char INT8; /*!< 8-bit signed integer */
typedef unsigned char UINT8; /*!< 8-bit unsigned integer */
typedef signed short INT16; /*!< 16-bit signed integer */
typedef unsigned short UINT16; /*!< 16-bit unsigned integer */

typedef unsigned char BYTE; /*!< 8-bit unsigned integer */
typedef unsigned short WORD; /*!< 16-bit unsigned integer */
typedef unsigned long DWORD;

typedef char CHAR; /*!< 8-bit signed integer */
typedef unsigned char UCHAR; /*!< 8-bit unsigned integer */

typedef int INT; /*!< 32-bit signed integer */
typedef unsigned int UINT; /*!< 32-bit unsigned integer */

typedef signed int INT32; /*!< 32-bit signed integer */
typedef unsigned int UINT32; /*!< 32-bit unsigned integer */

typedef long long INT64; /*!< 64-bit signed integer */
typedef unsigned long long UINT64; /*!< 64-bit unsigned integer */

/*
 * ========================================== 
 * boolean type
 */
#ifndef __cplusplus
#if !defined(true) || !defined(false)
enum
{
	false, /*!< fail */
	true  /*!< success */
};
#endif
#endif // __cplusplus

typedef unsigned char boolean; /*!< success or fail */

/*
 * ========================================== 
 */

#endif // _MyType_h_

