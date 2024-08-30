
/* IEC type definitions */

#ifndef _IEC_TYPE_H_
#define _IEC_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	IEC_TYPE_INVALID = 0,        /* No IEC Type              */
	IEC_TYPE_BOOL = 1,           /* 8 Bit containing a boolean value FALSE=0 or TRUE=1 */
	IEC_TYPE_SINT = 2,           /* 8 Bit signed integer     */
	IEC_TYPE_INT = 3,            /* 16 Bit signed integer    */
	IEC_TYPE_DINT = 4,           /* 32 Bit signed integer    */
	IEC_TYPE_USINT = 5,          /* 8 Bit unsigned integer   */
	IEC_TYPE_UINT = 6,           /* 16 Bit unsigned integer  */
	IEC_TYPE_UDINT = 7,          /* 32 Bit unsigned integer  */
	IEC_TYPE_REAL = 8,           /* 32 Bit floating point number */
	IEC_TYPE_STRING = 9,         /* Variable-length single-byte character string */
	IEC_TYPE_ULINT = 10,         /* 64 Bit unsigned integer  */
	IEC_TYPE_DATE_AND_TIME = 11, /* 32 Bit of Date in Seconds since 01.01.1970 00:00:00 */
	IEC_TYPE_TIME = 12,          /* 32 Bit of Time in ms     */
	IEC_TYPE_DATE = 13,          /* 32 Bit of Date (only)    */
	IEC_TYPE_LREAL = 14,         /* 64 Bit floating point number */
	IEC_TYPE_obsoletDT15 = 15,   /* not used any more (historisch "struct array") */
	IEC_TYPE_TIME_OF_DAY = 16,   /* 32 Bit Time of day (only)*/
	IEC_TYPE_BYTE = 17,          /* Bit string of length 8   */
	IEC_TYPE_WORD = 18,          /* Bit string of length 16  */
	IEC_TYPE_DWORD = 19,         /* Bit string of length 32  */
	IEC_TYPE_LWORD = 20,         /* Bit string of length 64  */
	IEC_TYPE_WSTRING = 21,       /* Variable-length double-byte character string */
	BUR_TYPE_OCTET = 22,         /* OCTET fuer Felder        */
	IEC_TYPE_LINT = 23           /* 64 Bit signed integer    */
} IEC_TYPE;

#if AR_CORE
#include <private/iecTypeP.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
