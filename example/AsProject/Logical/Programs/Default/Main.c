
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#include "string.h"
#include <stdio.h>

void _INIT ProgramInit(void)
{
}


void _CYCLIC ProgramCyclic(void)
{
	if(calldtoa) {
		calldtoa = 0;
		
		pString = stringdtoa(val, (char*)buffer, ndigits, sizeof(buffer));
		if(pString) {
			len = strlen((char*)pString);
			strcpy((char*)string, (char*)pString);
		}
			
	}

	
	
}

void _EXIT ProgramExit(void)
{

}

