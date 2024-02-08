
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#include "string.h"
#include <stdio.h>


//unsigned long bur_heap_size=0xFFFFF;
/****************************************************************
Copyright (C) 1997, 1998 Lucent Technologies
All Rights Reserved

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appear in all
copies and that both that the copyright notice and this
permission notice and warranty disclaimer appear in supporting
documentation, and that the name of Lucent or any of its entities
not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

LUCENT DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
IN NO EVENT SHALL LUCENT OR ANY OF ITS ENTITIES BE LIABLE FOR ANY
SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
****************************************************************/

/* Try to deduce arith.h from arithmetic properties. */

#define fprintf( f, fmt , ... ) sprintf(str[i++], fmt, ##__VA_ARGS__)
#define printf(fmt , ... ) sprintf(str[i++], fmt, ##__VA_ARGS__)
	
//
//static int dalign;
//typedef struct
//Akind {
//	char *name;
//	int   kind;
//} Akind;
//
//static Akind
//	IEEE_8087	= { "IEEE_8087", 1 },
//	IEEE_MC68k	= { "IEEE_MC68k", 2 },
//	IBM		= { "IBM", 3 },
//	VAX		= { "VAX", 4 },
//	CRAY		= { "CRAY", 5};
//
//Akind * Lcheck()
//{
//	union {
//		double d;
//		long L[2];
//	} u;
//	struct {
//		double d;
//		long L;
//	} x[2];
//
//	if (sizeof(x) > 2*(sizeof(double) + sizeof(long)))
//		dalign = 1;
//	u.L[0] = u.L[1] = 0;
//	u.d = 1e13;
//	if (u.L[0] == 1117925532 && u.L[1] == -448790528)
//		return &IEEE_MC68k;
//	if (u.L[1] == 1117925532 && u.L[0] == -448790528)
//		return &IEEE_8087;
//	if (u.L[0] == -2065213935 && u.L[1] == 10752)
//		return &VAX;
//	if (u.L[0] == 1267827943 && u.L[1] == 704643072)
//		return &IBM;
//	return 0;
//}
//
//Akind * icheck()
//{
//	union {
//		double d;
//		int L[2];
//	} u;
//	struct {
//		double d;
//		int L;
//	} x[2];
//
//	if (sizeof(x) > 2*(sizeof(double) + sizeof(int)))
//		dalign = 1;
//	u.L[0] = u.L[1] = 0;
//	u.d = 1e13;
//	if (u.L[0] == 1117925532 && u.L[1] == -448790528)
//		return &IEEE_MC68k;
//	if (u.L[1] == 1117925532 && u.L[0] == -448790528)
//		return &IEEE_8087;
//	if (u.L[0] == -2065213935 && u.L[1] == 10752)
//		return &VAX;
//	if (u.L[0] == 1267827943 && u.L[1] == 704643072)
//		return &IBM;
//	return 0;
//}
//
//char *emptyfmt = "";	/* avoid possible warning message with printf("") */
//
//Akind *
//	ccheck()
//{
//	union {
//		double d;
//		long L;
//	} u;
//	long Cray1;
//
//	/* Cray1 = 4617762693716115456 -- without overflow on non-Crays */
//	Cray1 = printf(emptyfmt) < 0 ? 0 : 4617762;
//	if (printf(emptyfmt, Cray1) >= 0)
//		Cray1 = 1000000*Cray1 + 693716;
//	if (printf(emptyfmt, Cray1) >= 0)
//		Cray1 = 1000000*Cray1 + 115456;
//	u.d = 1e13;
//	if (u.L == Cray1)
//		return &CRAY;
//	return 0;
//}
//
//int
//	fzcheck()
//{
//	double a, b;
//	int i;
//
//	a = 1.;
//		b = .1;
//	for(i = 155;; b *= b, i >>= 1) {
//		if (i & 1) {
//			a *= b;
//			if (i == 1)
//				break;
//		}
//	}
//	b = a * a;
//	return b == 0.;
//}
//
//int
//	main_arith()
//{
//	Akind *a = 0;
//	int Ldef = 0;
//	FILE *f;
//
//#ifdef WRITE_ARITH_H	/* for Symantec's buggy "make" */
//	f = fopen("arith.h", "w");
//	if (!f) {
//		printf("Cannot open arith.h\n");
//		return 1;
//	}
//#else
//	f = stdout;
//#endif
//
//	if (sizeof(double) == 2*sizeof(long))
//		a = Lcheck();
//	else if (sizeof(double) == 2*sizeof(int)) {
//		Ldef = 1;
//		a = icheck();
//	}
//	else if (sizeof(double) == sizeof(long))
//		a = ccheck();
//	if (a) {
//		fprintf(f, "#define %s\n#define Arith_Kind_ASL %d\n",
//			a->name, a->kind);
//		if (Ldef)
//			fprintf(f, "#define Long int\n#define Intcast (int)(long)\n");
//		if (dalign)
//			fprintf(f, "#define Double_Align\n");
//		if (sizeof(char*) == 8)
//			fprintf(f, "#define X64_bit_pointers\n");
//#ifndef NO_LONG_LONG
//		if (sizeof(long long) < 8)
//#endif
//		fprintf(f, "#define NO_LONG_LONG\n");
//		if (a->kind <= 2 && fzcheck())
//			fprintf(f, "#define Sudden_Underflow\n");
//		return 0;
//	}
//	fprintf(f, "/* Unknown arithmetic */\n");
//	return 1;
//}

/****************************************************************

The author of this software is David M. Gay.

Copyright (C) 2005 by David M. Gay
All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that the copyright notice and this permission notice and warranty
disclaimer appear in supporting documentation, and that the name of
the author or any of his current or former employers not be used in
advertising or publicity pertaining to distribution of the software
without specific, written prior permission.

THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.  IN
NO EVENT SHALL THE AUTHOR OR ANY OF HIS CURRENT OR FORMER EMPLOYERS BE
LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY
DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

****************************************************************/

/* Please send bug reports to David M. Gay (dmg at acm dot org,
 * with " at " changed at "@" and " dot " changed to ".").	*/

/* Program to compute quiet NaNs of various precisions (float,	*/
/* double, and perhaps long double) on the current system,	*/
/* provided the system uses binary IEEE (P754) arithmetic.	*/
/* Note that one system's quiet NaN may be a signaling NaN on	*/
/* another system.  The IEEE arithmetic standards (P754, P854)	*/
/* do not specify how to distinguish signaling NaNs from quiet	*/
/* ones, and this detail varies across systems.	 The computed	*/
/* NaN values are encoded in #defines for values for an		*/
/* unsigned 32-bit integer type, called Ulong below, and	*/
/* (for long double) perhaps as unsigned short values.  Once	*/
/* upon a time, there were PC compilers for Intel CPUs that	*/
/* had sizeof(long double) = 10.  Are such compilers still	*/
/* distributed?							*/

//#include <stdio.h>
//#define IEEE_8087
//#define Arith_Kind_ASL 1
//
//#ifndef Long
//#define Long long
//#endif
//
//typedef unsigned Long Ulong;
//
//#undef HAVE_IEEE
//#ifdef IEEE_8087
//#define _0 1
//#define _1 0
//#define HAVE_IEEE
//#endif
//#ifdef IEEE_MC68k
//#define _0 0
//#define _1 1
//#define HAVE_IEEE
//#endif
//
//#define UL (unsigned long)
//
//int
//	main_qnan(void)
//	{
//#ifdef HAVE_IEEE
//	typedef union {
//	float f;
//	double d;
//	Ulong L[4];
//#ifndef NO_LONG_LONG
//	unsigned short u[5];
//	long double D;
//#endif
//	} U;
//	U a, b, c;
//	int i;
//	
//	a.L[0] = b.L[0] = 0x7f800000;
//	c.f = a.f - b.f;
//	// printf("#define f_QNAN 0x%u\n", UL c.L[0]);
//	// sprintf(str[i++], "#define f_QNAN 0x%u\n", UL c.L[0]);
//	a.L[_0] = b.L[_0] = 0x7ff00000;
//	a.L[_1] = b.L[_1] = 0;
//	c.d = a.d - b.d;	/* quiet NaN */
//	// printf("#define d_QNAN0 0x%u\n", UL c.L[0]);
//	// printf("#define d_QNAN1 0x%u\n", UL c.L[1]);
//
//#ifdef NO_LONG_LONG
//	for(i = 0; i < 4; i++)
//	//printf("#define ld_QNAN%d 0xffffffff\n", i);
//	for(i = 0; i < 5; i++)
//	//printf("#define ldus_QNAN%d 0xffff\n", i);
//#else
//	b.D = c.D = a.d;
//	// if (printf(emptyfmt) < 0)
//	// c.D = 37;	/* never executed; just defeat optimization */
//	a.L[2] = a.L[3] = 0;
//	a.D = b.D - c.D;
//	for(i = 0; i < 4; i++)
//	// printf("#define ld_QNAN%d 0x%lx\n", i, UL a.L[i]);
//	for(i = 0; i < 5; i++)
//	// printf("#define ldus_QNAN%d 0x%x\n", i, a.u[i]);
//#endif
//#endif /* HAVE_IEEE */
//	return 0;
//	}


void _INIT ProgramInit(void)
{
	//main_arith();
	//main_qnan();
}


void _CYCLIC ProgramCyclic(void)
{
//	if(calldtoa)
//		main_qnan();
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

