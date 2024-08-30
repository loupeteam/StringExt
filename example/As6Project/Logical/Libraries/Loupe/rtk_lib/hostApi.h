
#ifndef _HOST_API_H_
#define _HOST_API_H_

#include <rtkTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

enum HOST_ERROR
{
	HOST_ERR_PARAMETER = 29703, /* invalid parameter*/
	HOST_ERR_DOMAIN = 29705,    /* name can't be resolved */
	HOST_ERR_ADDRESS = 29706,   /* address can't be reloved */
	HOST_ERR_STRLEN = 29708,    /* buffersize */
};

/* Looks up the IP address (lpAddr) of the provided hostname (szName).
 * Returns ERR_OK on success, HOST_ERROR on failure */
WORD ARHostGetByName(const char* szName, ULONG* lpAddr);

/* Get the symbolic name of this machine. 
 * "dst" is a pointer to the buffer that will receive the name, and "size" is the size of the buffer
 * Returns 0 on success, -1 on error */
int argethostname(char* dst, int size);

#if AR_CORE
#include <private/hostApiP.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
