/*
 * File: time.cpp
 * Copyright (c) 2023 Loupe
 * https://loupe.team
 * 
 * This file is part of StringExt, licensed under the MIT License.
 * 
 */

#ifndef __DTOA_H__
#define __DTOA_H__

#include <bur/plctypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "StringExt.h"

#ifdef __cplusplus
}
#endif

char *dtoa(double d, int mode, int ndigits, int *decpt, int *sign, char **rve);


#endif /* __FILE_NAME_H__ */