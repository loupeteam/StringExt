
#include <bur/plctypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

	#include "includes/rtkSemaphore.h"

#ifdef __cplusplus
};
#endif

static __thread RTK_SEM_H criticalSection[2] = {0};

void lockSelect(n) {
	if(n > (sizeof(criticalSection)/sizeof(criticalSection[0]) - 1)) return;
	if(!criticalSection[n]) RtkCreateSemaphore(0, 1, &criticalSection[n]);
	RtkAcquireSemaphore(&criticalSection[n], 500L);
}

void freeSelect(n) {
	if(n > (sizeof(criticalSection)/sizeof(criticalSection[0]) - 1)) return;
	if(!criticalSection[n]) return;
	RtkReleaseSemaphore(&criticalSection[n]);
}
