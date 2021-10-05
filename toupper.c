/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: StringExt
 * File: toupper.c
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

// Converts a string to upper case

// DONE and TESTED DFB 20150715

unsigned long ToUpper (unsigned long pString)
{

	if(pString == 0) return 0;
	
	for(; *(char*)pString; pString++)
		if(('a' <= *(char*)pString) && (*(char*)pString <= 'z'))
			*(char*)pString = 'A' + (*(char*)pString - 'a');

	return 0;
	
}
