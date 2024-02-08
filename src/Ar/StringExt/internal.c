
#include <bur/plctypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

#include "includes/rtkBase.h"

#ifdef __cplusplus
};
#endif

// semaphores cause cycle time violations
//#define USE_SEMAPHORE 

#ifdef USE_SEMAPHORE
#include "includes/rtkSemaphore.h"

static __thread RTK_SEM_H criticalSection[2] = {0};

#define CREATE(name, max, section) RtkCreateSemaphore(name, max, section)
#define ACQUIRE(section, wait) RtkAcquireSemaphore(section, wait)
#define RELEASE(section) RtkReleaseSemaphore(section)

#else
#include "includes/rtkCriticalSection.h"

static __thread RTK_CRIT_SEC_H criticalSection[2] = {0};

#define CREATE(name, max, section) RtkCreateCriticalSection(name, section)
#define ACQUIRE(section, wait) RtkEnterCriticalSection(section)
#define RELEASE(section) RtkLeaveCriticalSection(section)
#endif

void lockSelect(n) {
	if(n > (sizeof(criticalSection)/sizeof(criticalSection[0]) - 1)) return;
	if(!criticalSection[n]) CREATE(0, 1, &criticalSection[n]);
	RTK_ERROR err = ACQUIRE(criticalSection[n], 500L);
}

void freeSelect(n) {
	if(n > (sizeof(criticalSection)/sizeof(criticalSection[0]) - 1)) return;
	if(!criticalSection[n]) return;
	RTK_ERROR err = RELEASE(criticalSection[n]);
}
