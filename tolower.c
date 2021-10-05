/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: StringExt
 * File: tolower.c
 * Author: Josh
 * Created: March 03, 2015
 ********************************************************************
 * Implementation of library StringExt
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

	#include "StringExt.h"

#ifdef __cplusplus
	};
#endif

// Converts a string to lower case

// DONE and TESTED DFB 20150715

unsigned long ToLower (unsigned long pString)
{

	if(pString == 0) return 0;
	
	for(; *(char*)pString; pString++)
		if(('A' <= *(char*)pString) && (*(char*)pString <= 'Z'))
			*(char*)pString = 'a' + (*(char*)pString - 'A');

	return 0;
	
}
