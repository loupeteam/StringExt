
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#include "string.h"
#include <stdio.h>


/* Self test for HexStringToUDINT() and UDINTToHexString().
	Set hexTest to run it; hexTestFail must come back 0. */

typedef struct hexCase_typ {
	char*			Input;
	signed long		ExpectStatus;	/* 0, or the STREXT_ERR_enum value expected */
	unsigned long	ExpectValue;	/* only checked when ExpectStatus is 0 */
} hexCase_typ;

static const hexCase_typ hexCases[] = {

	/* Every accepted prefix */
	{ "0xFF",			0,	0xFF		},
	{ "0XFF",			0,	0xFF		},
	{ "16#FF",			0,	0xFF		},
	{ "$FF",			0,	0xFF		},
	{ "FF",				0,	0xFF		},

	/* Case, padding and white space */
	{ "0xdeadbeef",		0,	0xDEADBEEF	},
	{ "0xDEADBEEF",		0,	0xDEADBEEF	},
	{ "16#000000FF",	0,	0xFF		},
	{ "  0x10  ",		0,	0x10		},
	{ "0x00000000",		0,	0			},
	{ "0",				0,	0			},

	/* Full range - the case HexStringToDINT() saturates on */
	{ "0xFFFFFFFF",		0,	0xFFFFFFFF	},
	{ "0x80000000",		0,	0x80000000	},

	/* Out of range */
	{ "0x100000000",	STREXT_ERR_RANGE,			0 },
	{ "0xFFFFFFFFF",	STREXT_ERR_RANGE,			0 },

	/* Malformed */
	{ "",				STREXT_ERR_INVALID_FORMAT,	0 },
	{ "0x",				STREXT_ERR_INVALID_FORMAT,	0 },
	{ "16#",			STREXT_ERR_INVALID_FORMAT,	0 },
	{ "0xGG",			STREXT_ERR_INVALID_FORMAT,	0 },
	{ "0xFF junk",		STREXT_ERR_INVALID_FORMAT,	0 },
	{ "-0x10",			STREXT_ERR_INVALID_FORMAT,	0 },
	{ "+0x10",			STREXT_ERR_INVALID_FORMAT,	0 },
	{ "0x0xFF",			STREXT_ERR_INVALID_FORMAT,	0 },

};


static void runHexTest(void)
{
	unsigned long	i;
	unsigned long	Value;
	signed long		Status;
	char			Formatted[16];

	hexTestPass=	0;
	hexTestFail=	0;
	strcpy((char*)hexTestFirstFail, "");


	/* Parsing */

	for(i=0; i<(sizeof(hexCases)/sizeof(hexCases[0])); i++){

		Value=	0xA5A5A5A5;

		Status=	HexStringToUDINT( (unsigned long)hexCases[i].Input, (unsigned long)&Value );

		if(		(Status == hexCases[i].ExpectStatus)
			&&	((Status != 0) || (Value == hexCases[i].ExpectValue))
			&&	((Status == 0) || (Value == 0xA5A5A5A5))	/* value untouched on failure */
			){

			hexTestPass++;

		}
		else{

			hexTestFail++;

			if(strlen((char*)hexTestFirstFail) == 0){
				strncpy((char*)hexTestFirstFail, hexCases[i].Input, 79);
			}

		}

	}


	/* Null pointers */

	if( HexStringToUDINT( 0, (unsigned long)&Value ) == STREXT_ERR_INVALID_INPUT ) hexTestPass++; else hexTestFail++;
	if( HexStringToUDINT( (unsigned long)"0xFF", 0 ) == STREXT_ERR_INVALID_INPUT ) hexTestPass++; else hexTestFail++;


	/* Formatting - each prefix, minimal and padded */

	if( (UDINTToHexString( 0xFF, (unsigned long)Formatted, sizeof(Formatted), 0, STREXT_HEXPREFIX_NONE ) == 2)
		&& (strcmp(Formatted, "FF") == 0) ) hexTestPass++; else hexTestFail++;

	if( (UDINTToHexString( 0xFF, (unsigned long)Formatted, sizeof(Formatted), 0, STREXT_HEXPREFIX_0X ) == 4)
		&& (strcmp(Formatted, "0xFF") == 0) ) hexTestPass++; else hexTestFail++;

	if( (UDINTToHexString( 0xFF, (unsigned long)Formatted, sizeof(Formatted), 8, STREXT_HEXPREFIX_IEC ) == 11)
		&& (strcmp(Formatted, "16#000000FF") == 0) ) hexTestPass++; else hexTestFail++;

	if( (UDINTToHexString( 0xFF, (unsigned long)Formatted, sizeof(Formatted), 4, STREXT_HEXPREFIX_DOLLAR ) == 5)
		&& (strcmp(Formatted, "$00FF") == 0) ) hexTestPass++; else hexTestFail++;

	if( (UDINTToHexString( 0, (unsigned long)Formatted, sizeof(Formatted), 0, STREXT_HEXPREFIX_NONE ) == 1)
		&& (strcmp(Formatted, "0") == 0) ) hexTestPass++; else hexTestFail++;

	if( (UDINTToHexString( 0xFFFFFFFF, (unsigned long)Formatted, sizeof(Formatted), 8, STREXT_HEXPREFIX_0X ) == 10)
		&& (strcmp(Formatted, "0xFFFFFFFF") == 0) ) hexTestPass++; else hexTestFail++;


	/* Buffer too small, and nothing written when it does not fit */

	strcpy(Formatted, "untouched");

	if( (UDINTToHexString( 0xFFFFFFFF, (unsigned long)Formatted, 5, 8, STREXT_HEXPREFIX_0X ) == STREXT_ERR_BUFFER_TOO_SMALL)
		&& (strcmp(Formatted, "untouched") == 0) ) hexTestPass++; else hexTestFail++;

	if( UDINTToHexString( 0xFF, 0, 16, 0, STREXT_HEXPREFIX_0X ) == STREXT_ERR_INVALID_INPUT ) hexTestPass++; else hexTestFail++;

	if( UDINTToHexString( 0xFF, (unsigned long)Formatted, sizeof(Formatted), 0, 99 ) == STREXT_ERR_INVALID_INPUT ) hexTestPass++; else hexTestFail++;


	/* Round trip every value the formatter can produce at each prefix */

	for(i=0; i<4; i++){

		if(		(UDINTToHexString( 0x12AB34CD, (unsigned long)Formatted, sizeof(Formatted), 8, (unsigned char)i ) > 0)
			&&	(HexStringToUDINT( (unsigned long)Formatted, (unsigned long)&Value ) == 0)
			&&	(Value == 0x12AB34CD)
			){

			hexTestPass++;

		}
		else{

			hexTestFail++;

		}

	}

}


/* Self test for formatString().
	Set formatTest to run it; formatTestFail must come back 0.

	The format of each case is copied into a scratch buffer whose remaining
	bytes are filled with 'X' after the terminator. A formatter that walks
	past the terminator - as a trailing bare '%' once did - drags that filler
	into the destination, so the expected-output compare catches it. */

typedef struct formatCase_typ {
	char*	Format;
	char*	Expect;
} formatCase_typ;

static const formatCase_typ formatCases[] = {

	/* Trailing bare '%' - no command character follows it */
	{ "value: %",		"value: "	},
	{ "%",				""			},
	{ "trail %d%",		"trail 42"	},
	{ "%%%",			"%"			},

	/* Ordinary substitutions */
	{ "no format",		"no format"	},
	{ "%d items",		"42 items"	},
	{ "%d and %d",		"42 and -7"	},
	{ "%s=%b",			"abc=TRUE"	},

	/* Escaped percent, and an unknown command character */
	{ "100%% done",		"100% done"	},
	{ "a%zb",			"ab"		},

};


static void runFormatTest(void)
{
	unsigned long		i;
	unsigned long		j;
	StrExtArgs_typ		Args;
	char				Scratch[64];
	char				Dest[80];
	signed long			Length;

	formatTestPass=	0;
	formatTestFail=	0;
	strcpy((char*)formatTestFirstFail, "");

	for(i=0; i<(sizeof(formatCases)/sizeof(formatCases[0])); i++){

		memset(&Args, 0, sizeof(Args));
		Args.i[0]=	42;
		Args.i[1]=	-7;
		Args.b[0]=	1;
		Args.s[0]=	(unsigned long)"abc";

		/* Fill with junk, then lay the format in - everything after the
			terminator stays 'X' and must never reach the destination */
		for(j=0; j<sizeof(Scratch); j++) Scratch[j]= 'X';

		/* A format longer than the scratch buffer would overrun it and
			leave no filler to detect an over-read with */
		if(strlen(formatCases[i].Format) >= sizeof(Scratch)){

			formatTestFail++;
			continue;

		}

		strcpy(Scratch, formatCases[i].Format);

		memset(Dest, 0, sizeof(Dest));

		Length=	formatString(Dest, sizeof(Dest), Scratch, &Args);

		if(		(strcmp(Dest, formatCases[i].Expect) == 0)
			&&	(Length == (signed long)strlen(formatCases[i].Expect))
			){

			formatTestPass++;

		}
		else{

			formatTestFail++;

			if(strlen((char*)formatTestFirstFail) == 0){
				strncpy((char*)formatTestFirstFail, formatCases[i].Format, 79);
			}

		}

	}


	/* Null pointers */

	if( formatString(Dest, sizeof(Dest), "abc", 0) == STREXT_ERR_INVALID_INPUT ) formatTestPass++; else formatTestFail++;
	if( formatString(0, sizeof(Dest), "abc", &Args) == STREXT_ERR_INVALID_INPUT ) formatTestPass++; else formatTestFail++;
	if( formatString(Dest, sizeof(Dest), 0, &Args) == STREXT_ERR_INVALID_INPUT ) formatTestPass++; else formatTestFail++;


	/* Trailing '%' reached with only the reserved null byte left. The loop
		still has room to enter the '%' branch, so this is a genuine
		pre-fix failure - the old code stepped onto the filler and copied it */

	for(j=0; j<sizeof(Scratch); j++) Scratch[j]= 'X';
	strcpy(Scratch, "abcdef%");

	memset(Dest, 0, sizeof(Dest));
	if( (formatString(Dest, 8, Scratch, &Args) == 6) && (strcmp(Dest, "abcdef") == 0) ) formatTestPass++; else formatTestFail++;


	/* Destination fills before the format character is ever reached */

	memset(Dest, 0, sizeof(Dest));
	if( (formatString(Dest, 4, Scratch, &Args) == 3) && (strcmp(Dest, "abc") == 0) ) formatTestPass++; else formatTestFail++;


	/* Only the reserved null byte fits - nothing is written at all */

	for(j=0; j<sizeof(Scratch); j++) Scratch[j]= 'X';
	strcpy(Scratch, "%");

	memset(Dest, 0, sizeof(Dest));
	if( (formatString(Dest, 1, Scratch, &Args) == 0) && (strcmp(Dest, "") == 0) ) formatTestPass++; else formatTestFail++;

}


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

	if(hexTest) {
		hexTest = 0;
		runHexTest();
	}

	if(formatTest) {
		formatTest = 0;
		runFormatTest();
	}

	
	
}

void _EXIT ProgramExit(void)
{

}

