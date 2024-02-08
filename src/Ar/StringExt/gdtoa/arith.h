// Configure Macros for gdtoaimp
// We should use autoconf.sh to generate this file but I could not get it to work
// Kept saying autoconf v0.0.0 is less than 2.5.0
// Instead I was able to manually determine these by running arithchk.c in ARSim

#ifndef ARITH_H_INCLUDED
#define ARITH_H_INCLUDED

#include "../tlsf.h"
#include "../internal.h"

#define IEEE_8087
#define Arith_Kind_ASL 1

#define ENABLE_MULTITHREAD
#ifdef ENABLE_MULTITHREAD

#define MULTIPLE_THREADS 

#define ACQUIRE_DTOA_LOCK(n) lockSelect(n)
#define FREE_DTOA_LOCK(n) freeSelect(n)

// We likely want to use tlsf here but I dont see how as we can define FREE currently
// Will the heap_redirect take care of this for us ?
//#define MALLOC tlsf_malloc
//#define FREE tlsf_free

#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
#endif /* ARITH_H_INCLUDED */
