/*	$OpenBSD: strlcat.c,v 1.2 1999/06/17 16:28:58 millert Exp $	*/

/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


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

#ifndef strlcat
	/*
 * '_cups_strlcat()' - Safely concatenate two strings.
 */

	size_t					 /* O - Length of string */
	strlcat(char *dst,		 /* O - Destination string */
			const char *src, /* I - Source string */
			size_t size)	 /* I - Size of destination string buffer */
	{
		size_t srclen; /* Length of source string */
		size_t dstlen; /* Length of destination string */

		/*
  * Figure out how much room is left...
  */

		dstlen = strlen(dst);
		size -= dstlen + 1;

		if (!size)
			return (dstlen); /* No room, return immediately... */

		/*
  * Figure out how much room is needed...
  */

		srclen = strlen(src);

		/*
  * Copy the appropriate amount...
  */

		if (srclen > size)
			srclen = size;

		memcpy(dst + dstlen, src, srclen);
		dst[dstlen + srclen] = '\0';

		return (dstlen + srclen);
	}
#endif /* !HAVE_STRLCAT */

	/*
 * Appends src to string dst of size dSize (unlike strncat, dSize is the
 * full size of pDest, not space left).  At most dSize-1 characters
 * will be copied.  Always NUL terminates (unless dSize <= strlen(pDest)).
 * Returns strlen(pSrc) + MIN(dSize, strlen(initial pDest)).
 * If retval >= dSize, truncation occurred.
 */
	unsigned long stringlcat(unsigned long pDest, const unsigned long pSrc, unsigned long dSize)
	{
		char *dst = (char *)pDest;
		char *src = (char *)pSrc;
		char *d = dst;
		const char *s = src;
		unsigned long n = dSize;
		unsigned long dlen;

		/* Find the end of dst and adjust bytes left but don't go past end */
		while (n-- != 0 && *d != '\0')
			d++;
		dlen = d - dst;
		n = dSize - dlen;

		if (n == 0)
			return (dlen + strlen(s));
		while (*s != '\0')
		{
			if (n != 1)
			{
				*d++ = *s;
				n--;
			}
			s++;
		}
		*d = '\0';

		return (dlen + (s - src)); /* count does not include NUL */
}
