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

	if((pDest == 0) || (pSrc == 0)){
		return 0;
	} // Check for null pointer //


	/************************************************/
	/* Generate millisecond Count					*/
	/************************************************/
	UDINT epochYear = 1970;
	UDINT daysFromPrevMonth[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
	UDINT daysSinceEpoch;
	UDINT leapYearDayCount;
	UDINT i;

	DTStructure*		DTStruct;
	unsigned long long*		timeStamp64;

	DTStruct = (DTStructure*) pSrc;
	timeStamp64 = (unsigned long long*) pDest;
	
	// Find the number of days since the epoch year
	// Loop through years to find the count leap years
	leapYearDayCount = 0;
	for(i=epochYear; i<DTStruct->year; i++){
		if (i % 4 == 0){
			leapYearDayCount++;
			if (i % 100 == 0){
				leapYearDayCount--;
				if (i % 400 ==0){
					leapYearDayCount++;
				}
			}
		}
	} 
	
	//Add in days from previous months, leap year days, and days from previous years
	daysSinceEpoch = daysFromPrevMonth[DTStruct->month-1] + leapYearDayCount + (((DTStruct->year-1)-epochYear)*365);	
		
	//convert everything to milliseconds and add it to the 64 bit ULINT
	*timeStamp64 = DTStruct->millisec
		+ DTStruct->second*1000
		+ DTStruct->minute*60000
		+ DTStruct->hour*3600000
		+ daysSinceEpoch*86400000;
	
	
	return daysSinceEpoch;


} // End Fn //
