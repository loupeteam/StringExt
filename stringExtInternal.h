#ifndef _SG4_
#include "bur.h"
#endif

#ifndef brsitoa
    #ifndef itoa
        #include <stdio.h>
        #define brsitoa(a,b) sprintf(b,"%d",a)
    #else
        #include <stdlib.h>
        #define brsitoa(a,b) strlen(itoa(a,(char*)b,10))
    #endif
#endif


#ifndef brsftoa
#include "math.h"
#include "string.h"
#define brsftoa(a,b) ftoa((a),(char*)(b),14)
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

