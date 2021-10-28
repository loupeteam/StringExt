/********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: StringExt
 * File: GenerateTimestamp.c
 * Author: Scott Claiborne
 * Created: February 14, 2018
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
#include "stdlib.h"
#include "stdio.h"

#ifndef brsitoa
#define brsitoa(a,b) strlen(itoa(a,(char*)b,10))
#endif
#ifndef brsftoa
#include "math.h"
// Reverses a string 'str' of length 'len'
void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
  
// Converts a given integer x to string str[]. 
// d is the number of digits required in the output. 
// If d is more than the number of digits in x, 
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
  
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
  
    reverse(str, i);
    str[i] = '\0';
    return i;
}
  
// Converts a floating-point/double number to a string.
size_t ftoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
  
    // Extract floating part
    float fpart = n - (float)ipart;
  
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
  
    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot
  
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter 
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
  
        intToStr((int)fpart, res + i + 1, afterpoint);
    }

	return strlen(res);
}
#define brsftoa(a,b) ftoa(a,(char*)b,14)
#endif
#ifndef DTStructure 
#include "astime.h"
#endif

//-----------------------------------------------------------------------------
// Generate a time stamp string from a DTStructure variable
//-----------------------------------------------------------------------------

// Check for invalid inputs			DONE and TESTED SC 20180214
// Generate string					DONE and TESTED SC 20180214

unsigned short GenerateTimestampMS(unsigned long pDTStruct, unsigned long pTimestamp, unsigned long TimestampLength)
{
	
	
/************************************************/
/* Check for invalid inputs						*/
/************************************************/

if( 	(pTimestamp == 0)
	||	(TimestampLength == 0)
	||	(pDTStruct == 0)
	){
		
	return 0;
		
} // Check for null pointer //


/************************************************/
/* Generate String 								*/
/************************************************/

/* 'YYYY-MM-DD HH:MM:SS.SSS' */

STRING			TempString[6];
//DTStructure*	pDTStruct = ((DTStructure*) pDTStructure);


/* Clear String */

strcpy( (char*)pTimestamp, "" );


/* Year */

brsitoa(((DTStructure*) pDTStruct)->year, (UDINT)TempString);

strncat( (char*)pTimestamp, TempString, TimestampLength - strlen((char*)pTimestamp) );
strncat( (char*)pTimestamp, "-", TimestampLength - strlen((char*)pTimestamp) );


/* Month */

brsitoa( ((DTStructure*) pDTStruct)->month, (UDINT)TempString );

if( ((DTStructure*) pDTStruct)->month < 10 ) strncat( (char*)pTimestamp, "0" , TimestampLength - strlen((char*)pTimestamp) ); 
strncat( (char*)pTimestamp, TempString, TimestampLength - strlen((char*)pTimestamp) );
strncat( (char*)pTimestamp, "-", TimestampLength - strlen((char*)pTimestamp) );


/* Day */

brsitoa( ((DTStructure*) pDTStruct)->day, (UDINT)TempString );

if( ((DTStructure*) pDTStruct)->day < 10 ) strncat( (char*)pTimestamp, "0" , TimestampLength - strlen((char*)pTimestamp) ); 
strncat( (char*)pTimestamp, TempString, TimestampLength - strlen((char*)pTimestamp) );
strncat( (char*)pTimestamp, " ", TimestampLength - strlen((char*)pTimestamp) );


/* Hour */

brsitoa( ((DTStructure*) pDTStruct)->hour, (UDINT)TempString );

if( ((DTStructure*) pDTStruct)->hour < 10 ) strncat( (char*)pTimestamp, "0" , TimestampLength - strlen((char*)pTimestamp) ); 
strncat( (char*)pTimestamp, TempString, TimestampLength - strlen((char*)pTimestamp) );
strncat( (char*)pTimestamp, ":", TimestampLength - strlen((char*)pTimestamp) );


/* Minute */

brsitoa( ((DTStructure*) pDTStruct)->minute, (UDINT)TempString );

if( ((DTStructure*) pDTStruct)->minute < 10 ) strncat( (char*)pTimestamp, "0" , TimestampLength - strlen((char*)pTimestamp) ); 
strncat( (char*)pTimestamp, TempString, TimestampLength - strlen((char*)pTimestamp) );
strncat( (char*)pTimestamp, ":", TimestampLength - strlen((char*)pTimestamp) );


/* Second */

brsitoa( ((DTStructure*) pDTStruct)->second, (UDINT)TempString );

if( ((DTStructure*) pDTStruct)->second < 10 ) strncat( (char*)pTimestamp, "0" , TimestampLength - strlen((char*)pTimestamp) ); 
strncat( (char*)pTimestamp, TempString, TimestampLength - strlen((char*)pTimestamp) );
strncat( (char*)pTimestamp, ".", TimestampLength - strlen((char*)pTimestamp) );

/* MiliSecond */

brsitoa( ((DTStructure*) pDTStruct)->millisec, (UDINT)TempString );

if( ((DTStructure*) pDTStruct)->millisec < 100 ) strncat( (char*)pTimestamp, "0" , TimestampLength - strlen((char*)pTimestamp) ); 
if( ((DTStructure*) pDTStruct)->millisec < 10 ) strncat( (char*)pTimestamp, "0" , TimestampLength - strlen((char*)pTimestamp) ); 
strncat( (char*)pTimestamp, TempString, TimestampLength - strlen((char*)pTimestamp) );

return strlen( (char*)pTimestamp );


} // End Fn //


//-----------------------------------------------------------------------------
// Generate a time stamp string from a DTStructure - YYYYMMDD_HHMMSS_SSS
//-----------------------------------------------------------------------------

unsigned short GenerateTimestampMS_1(unsigned long pDTStruct, unsigned long pTimestamp, unsigned long TimestampLength)
{
	
	// Check for invalid inputs - tested
	if( (pTimestamp == 0) || (TimestampLength == 0)	|| (pDTStruct == 0)) return 0;

	// 'YYYYMMDD_HHMMSS_SSS' - 19 characters - tested
	STRING tempString[6+1];
	
	// Clear string
	memset((void*)pTimestamp, 0, TimestampLength);

	// Year - YY
	brsitoa(((DTStructure*)pDTStruct)->year, (UDINT)tempString);
	strncat((char*)pTimestamp, tempString, TimestampLength - strlen((char*)pTimestamp));
	
	// Month - MM
	brsitoa(((DTStructure*)pDTStruct)->month, (UDINT)tempString);
	if (((DTStructure*)pDTStruct)->month < 10) strncat((char*)pTimestamp, "0", TimestampLength - strlen((char*)pTimestamp));
	strncat((char*)pTimestamp, tempString, TimestampLength - strlen((char*)pTimestamp));
	
	// Day - DD_
	brsitoa(((DTStructure*)pDTStruct)->day, (UDINT)tempString);
	if (((DTStructure*)pDTStruct)->day < 10 ) strncat((char*)pTimestamp, "0", TimestampLength - strlen((char*)pTimestamp));
	strncat((char*)pTimestamp, tempString, TimestampLength - strlen((char*)pTimestamp));
	strncat((char*)pTimestamp, "_", TimestampLength - strlen((char*)pTimestamp));

	// Hour - HH
	brsitoa(((DTStructure*)pDTStruct)->hour, (UDINT)tempString);
	if (((DTStructure*)pDTStruct)->hour < 10) strncat((char*)pTimestamp, "0", TimestampLength - strlen((char*)pTimestamp));
	strncat((char*)pTimestamp, tempString, TimestampLength - strlen((char*)pTimestamp));
	
	// Minute - MM
	brsitoa(((DTStructure*)pDTStruct)->minute, (UDINT)tempString);
	if (((DTStructure*)pDTStruct)->minute < 10) strncat((char*)pTimestamp, "0", TimestampLength - strlen((char*)pTimestamp));
	strncat((char*)pTimestamp, tempString, TimestampLength - strlen((char*)pTimestamp));
	
	// Second  - SS_
	brsitoa(((DTStructure*)pDTStruct)->second, (UDINT)tempString);
	if (((DTStructure*)pDTStruct)->second < 10) strncat((char*)pTimestamp, "0", TimestampLength - strlen((char*)pTimestamp));
	strncat((char*)pTimestamp, tempString, TimestampLength - strlen((char*)pTimestamp));
	strncat((char*)pTimestamp, "_", TimestampLength - strlen((char*)pTimestamp));

	// MilliSecond - SSS
	brsitoa(((DTStructure*)pDTStruct)->millisec, (UDINT)tempString);
	if (((DTStructure*)pDTStruct)->millisec < 100) strncat((char*)pTimestamp, "0", TimestampLength - strlen((char*)pTimestamp));
	if (((DTStructure*)pDTStruct)->millisec < 10) strncat((char*)pTimestamp, "0", TimestampLength - strlen((char*)pTimestamp));
	strncat((char*)pTimestamp, tempString, TimestampLength - strlen((char*)pTimestamp));
	
	return strlen((char*)pTimestamp);

} // End Fn //
