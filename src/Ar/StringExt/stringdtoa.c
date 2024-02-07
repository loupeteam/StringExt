/*
 * File: time.cpp
 * Copyright (c) 2023 Loupe
 * https://loupe.team
 * 
 * This file is part of StringExt, licensed under the MIT License.
 * 
 */

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
#include "dtoa.h"

int init = 0;

unsigned long stringdtoa(double value, unsigned long mode, unsigned long ndigits, unsigned long decpt, unsigned long sign, unsigned long rve) {
	if(!init) {
		init = 1;
		
	}
	return (unsigned long) dtoa(value, mode, ndigits, (int*) decpt, (int*) sign, (char**)rve);
}