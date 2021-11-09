
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "StringExt.h"

#ifdef __cplusplus
	};
#endif

#if !defined(_SG4) || defined(_NOT_BR)
#include "bur.h"
#include "NOT_BR.h"
#endif


#include <string.h>


unsigned long appendArrayIndex(unsigned long Value, unsigned long pString)
{

	/************************************************/
	/* Check for invalid inputs						*/
	/************************************************/

	if( pString == 0 ){
		
		return 0;
		
	} // Check for null pointer //

	STRING	TempString[12];

	/************************************************/
	/* Convert UDINT to a string					*/
	/************************************************/

	brsitoa(Value, (UDINT)TempString);
	
	/************************************************/
	/* Append Brackets and index					*/
	/************************************************/
	
	strcat((STRING*)pString, "[");
	strcat((STRING*)pString, TempString);
	strcat((STRING*)pString, "]");	

	return pString;
	
}
