
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

#ifdef _NOT_BR
#define brsitoa(a, b) itoa(a, b)
#define brsftoa(a, b) ftoa(a, b)
#endif

// Define some basic macros 
#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef ARRAY_ENTRIES
#define ARRAY_ENTRIES(array) (sizeof(array)/sizeof(array[0]))
#endif

/*
 * 
 */
signed long formatString(plcstring* destination, unsigned long destSize, plcstring* src, StrExtArgs_typ* pArguments) {
	
	// Check for invalid inputs
	if(!destination || !src || !pArguments)
		return STREXT_ERR_INVALID_INPUT;

	// Temporary array for string concatenations 
	char temp_string[16];

	// Size of a string that is concatenated to the destination
	int concat_string_size;
	
	char* dst = destination;
	
	// Array index counters 
	int bool_counter   = 0;		
	int int_counter    = 0;
	int real_counter   = 0;
	int string_counter = 0;

	// If size is 0, dont do anything
	// We can't do anything in that case
	if(!destSize)
		return 0;
		
	destSize--; // Remove 1 from dest size to leave room for null char
	
	// Run through the source message and copy it to the destination until src is empty or destination is full 
	while ((*src != '\0') && (destSize > 0))
	{
		// Special character found and MessageData given 
		if ((pArguments != NULL) && (*src == '%'))
		{
			// Temporary 'close' the destination string (to allow strcat...) 
			*dst = '\0';
		
			// Consume the char and investigate the command 
			switch (*(++src))
			{
				// Insert bool 
				case 'b':
					// Only take a value if an array entry exists 
					if (bool_counter < ARRAY_ENTRIES(pArguments->b))
					{
						if (pArguments->b[bool_counter])
						{
							strncat(dst, "TRUE", destSize);
							concat_string_size = MIN(destSize, 4);
						}
						else
						{
							strncat(dst, "FALSE", destSize);
							concat_string_size = MIN(destSize, 5);
						}
						bool_counter++;
						dst += concat_string_size;
						destSize -= concat_string_size;
					}
					src++;
					break;
					
				// Insert integer 
				case 'i':
				case 'd':
					// Only take a value if an array entry exists 
					if (int_counter < ARRAY_ENTRIES(pArguments->i))
					{
						concat_string_size = brsitoa(pArguments->i[int_counter], (UDINT)temp_string);
						concat_string_size = MIN(destSize, concat_string_size);
						strncat(dst, temp_string, destSize);
						int_counter++;
						dst += concat_string_size;
						destSize -= concat_string_size;
					}
					src++;
					break;
					
				// Insert real 
				case 'r':
				case 'f':
					// Only take a value if an array entry exists 
					if (real_counter < ARRAY_ENTRIES(pArguments->r))
					{
						concat_string_size = brsftoa(pArguments->r[real_counter], (UDINT)temp_string);
						concat_string_size = MIN(destSize, concat_string_size);
						strncat(dst, temp_string, destSize);
						real_counter++;
						dst += concat_string_size;
						destSize -= concat_string_size;
					}
					src++;
					break;
					
				// Insert string 
				case 's':
					// Only take a value if an array entry exists 
					if (string_counter < ARRAY_ENTRIES(pArguments->s))
					{
						if (pArguments->s[string_counter]) 
						{
							strncat(dst, (char*)pArguments->s[string_counter], destSize);
							concat_string_size = MIN(destSize, strlen((char*)pArguments->s[string_counter]));
							dst += concat_string_size;
							destSize -= concat_string_size;
						}
						string_counter++;
					}
					src++;
					break;
					
				// Insert percent 
				case '%':
					*dst++ = '%';
					src++;
					destSize--;
					break;
					
				// ELSE 
				default:
					// Ignore the character 
					src++;
					break;
			}
		}
		else
		{
			*dst++ = *src++;
			destSize--;
		}
	}
	
	// Add the end of string 
	*dst = '\0';
	
	return dst - destination;
}
