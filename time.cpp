
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
#include "StringExt.h"
#ifdef __cplusplus
	};
#endif

#include "string.h"

#define __XSI_VISIBLE 1
#include "time.h"


unsigned long stringfTime(unsigned long dest, unsigned long destSize, unsigned long format, DATE_AND_TIME time) {
	if(!dest || !destSize || !format) return 0; // Return if null pointers or if destSize is 0
	tm t = {};
	gmtime_r((time_t*)&time, &t);
	return strftime((char*)dest, destSize, (char*)format, &t);
}

DATE_AND_TIME stringpTime(unsigned long src, unsigned long format) {
	if(!src || !format) return 0; // Return if null pointers
	tm t = {};
	strptime((char*)src, (char*)format, &t);
	return mktime(&t);
}
