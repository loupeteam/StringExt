#ifndef _SG4_
#include "bur.h"
#endif

#include <stdio.h>
#include "math.h"
#include "string.h"
#include <stdlib.h>
#ifndef brsitoa
    #ifndef itoa
        #define brsitoa(a,b) sprintf((b),"%d",(a))
    #else
        #define brsitoa(a,b) strlen(itoa((a),(char*)(b),10))
    #endif
#endif


#ifndef brsftoa
    #ifndef ftoa
        #define brsftoa(a,b) sprintf((b),"%f",(a))
    #else
        #define brsftoa(a,b) ftoa( (a), (b))
    #endif
#endif

#ifndef DTStructure 
#include "astime.h"
#endif

// Define some basic macros 
#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef ARRAY_ENTRIES
#define ARRAY_ENTRIES(array) (sizeof(array)/sizeof(array[0]))
#endif

