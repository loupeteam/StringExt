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



#include "./gdtoa/gdtoa.h"

int init = 0;

unsigned long stringdtoa(double value, char* buffer, unsigned long ndig, unsigned long bufferSize) {
	if(!init) {
		init = 1;
		
	}
	
	return g_dfmt(buffer, &value, ndig, bufferSize);
}