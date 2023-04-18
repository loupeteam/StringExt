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


#ifndef strlcpy
	/*
 * '_cups_strlcpy()' - Safely copy two strings.
 */

	size_t					 /* O - Length of string */
	strlcpy(char *dst,		 /* O - Destination string */
			const char *src, /* I - Source string */
			size_t size)	 /* I - Size of destination string buffer */
	{
		size_t srclen; /* Length of source string */

		/*
  * Figure out how much room is needed...
  */

		size--;

		srclen = strlen(src);

		/*
  * Copy the appropriate amount...
  */

		if (srclen > size)
			srclen = size;

		memcpy(dst, src, srclen);
		dst[srclen] = '\0';

		return (srclen);
	}
#endif /* !HAVE_STRLCPY */

/*
 * Copy string pSrc to buffer dst of size dSize.  At most dSize-1
 * chars will be copied.  Always NUL terminates (unless dSize == 0).
 * Returns strlen(pSrc); if retval >= dSize, truncation occurred.
 */
unsigned long stringlcpy(unsigned long pDest, const unsigned long pSrc, unsigned long dSize)
{
	// We have access to this funtion but it does not appear in autocomplete or in AS help
	// This is a wrapper
	return strlcpy((char*) pDest, (char*) pSrc, dSize);
}
