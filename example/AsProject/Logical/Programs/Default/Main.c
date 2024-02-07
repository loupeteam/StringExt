
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#include "string.h"

void _INIT ProgramInit(void)
{

}

void _CYCLIC ProgramCyclic(void)
{
	if(calldtoa) {
		calldtoa = 0;
		prve = &rve;
		pString = stringdtoa(val, mode, ndigits, &decpt, &sign, &prve);
		if(pString) {
			len = strlen(pString);
			strcpy(string, pString);
		}
			
	}
}

void _EXIT ProgramExit(void)
{

}

