/********************************************************************
 * COPYRIGHT -- Microsoft
 ********************************************************************
 * Library: StringExt
 * File: Timestamp_TO_DT.c
 * Author: ScismD
 * Created: April 20, 2015
 ********************************************************************
 * Implementation of library StringExt
 ********************************************************************/

#include <bur/plctypes.h>
#include <string.h>
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


// Converts output of GenerateTimestamp to DATE_AND_TIME

// DONE not tested

plcdt Timestamp_TO_DT(unsigned long pDT, unsigned long pTimestamp)
{
 
	// Check for null pointer
  if(pTimestamp == 0)
  {
    return 0;  
  } 

  UINT        Length;
  STRING      TempString[6];
  DTStructure    DTStruct;
 
  Length = strlen((char*)pTimestamp);
  if (Length < 19)//19 is the size of the GenerateTimestamp function.
  {
    memset(&DTStruct,0,sizeof(DTStruct));
    return 0;
  }

  //clear string
  memset(&TempString,0,sizeof(TempString));

  //year
  memcpy(&TempString,(char*)pTimestamp,4);
  DTStruct.year = atoi(TempString);

  //clear string
  memset(&TempString,0,sizeof(TempString));

  //month
  memcpy(&TempString,(char*)pTimestamp+5,2);
  DTStruct.month = atoi(TempString);

  //clear string
  memset(&TempString,0,sizeof(TempString));

  //day
  memcpy(&TempString,(char*)pTimestamp+8,2);
  DTStruct.day = atoi(TempString);

  //clear string
  memset(&TempString,0,sizeof(TempString));

  //hour
  memcpy(&TempString,(char*)pTimestamp+11,2);
  DTStruct.hour = atoi(TempString);

  //clear string
  memset(&TempString,0,sizeof(TempString));

  //minute
  memcpy(&TempString,(char*)pTimestamp+14,2);
  DTStruct.minute = atoi(TempString);

  //clear string
  memset(&TempString,0,sizeof(TempString));

  //second
  memcpy(&TempString,(char*)pTimestamp+17,2);
  DTStruct.second = atoi(TempString);

  DTStruct.wday = 0;//this needs to be here otherwise the DTStruct to DT fails.
  DTStruct.millisec = 0;
  DTStruct.microsec = 0;
 
  if (pDT != 0)
  {
    memcpy((char*)pDT,&DTStruct,sizeof(DTStruct));
  }

  return DTStructure_TO_DT((UDINT)&DTStruct);
}
