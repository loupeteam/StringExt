/********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: StringExt
 * File: unixTimeStamp.c
 * Author: David Blackburn
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

#ifdef __cplusplus
};
#endif


#include <string.h>


/********************************************************************/
/* Generate a unix time stamp string from a DTStructure pointer		*/
/********************************************************************/



unsigned long unixTimeStamp(unsigned long pDest, unsigned long pSrc)
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
/* Generate Unix Time Stamp						*/
/************************************************/

DTStructure*		DTStruct;
unsigned long long*		timeStamp64;

DTStruct = (DTStructure*) pSrc;
timeStamp64 = (unsigned long long*) pDest;

//convert everything to milliseconds and add it to the 64 bit ULINT
*timeStamp64 = DTStruct->millisec
		+ DTStruct->second*1000
		+ DTStruct->minute*60000000
		+ DTStruct->hour*3600000000
		+ DTStruct->day*86400000000
		+ DTStruct->month*2628000000000
		+ DTStruct->year*31540000000000;
	
return 1;


} // End Fn //
