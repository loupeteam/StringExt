#ifndef STREXT_NOT_BR_H
#define STREXT_NOT_BR_H
#ifdef _NOT_BR
#include <stdlib.h>
#define brsitoa(a, b) itoa(a, (char*)b, 10)
#define brsftoa(a, b) ftoa(a, b)
#endif
#endif