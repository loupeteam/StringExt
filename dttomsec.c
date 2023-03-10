/********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: StringExt
 * File: dttomsec.c
 * Author: James Jakeway
 * Created: March 28, 2012
 ********************************************************************
 * Implementation of library StringExt
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
extern "C"
{
#endif
	
	#include "StringExt.h"
	#include <stdint.h>

#ifdef __cplusplus
};
#endif


#include <string.h>


/********************************************************************/
/* Generate a millisecond count from a DTStructure pointer			*/
/********************************************************************/



unsigned long dttomsec(unsigned long pDest, unsigned long pSrc)
{
	
	
	/************************************************/
	/* Check for invalid inputs						*/
	/************************************************/

	if( 	(pDest == 0)
		||	(pSrc == 0)
	){
		
		return 0;
		
	} // Check for null pointer //


	/************************************************/
	/* Generate millisecond Count					*/
	/************************************************/
	unsigned long long myVar;
	UDINT size = sizeof(myVar);
	

	DTStructure*		DTStruct;
	unsigned long long*		timeStamp64;

	DTStruct = (DTStructure*) pSrc;
	timeStamp64 = (unsigned long long*) pDest;
	
	
	//convert everything to milliseconds and add it to the 64 bit ULINT
	*timeStamp64 = DTStruct->millisec
		+ DTStruct->second*1000
		+ DTStruct->minute*60000
		+ DTStruct->hour*3600000
		+ DTStruct->day*86400000
		+ DTStruct->month*262800000
		+ (DTStruct->year-startYear)*31540000000;
	
	
	return size;


} // End Fn //
