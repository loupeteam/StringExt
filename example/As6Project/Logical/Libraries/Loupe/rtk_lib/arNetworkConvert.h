
/* AR network conversion functions
   The syntax and behavior of these functions is equal to the corresponding POSIX IPv4 functions */


#ifndef _AR_NETWORK_CONVERT_H_
#define _AR_NETWORK_CONVERT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <arInternetTypes.h>


/* Convert a string representation of an internet address "src" (given in decimal values only - e.g. 192.168.0.1)
 * to its binary form "dst" (being a pointer to AR_IN_ADDR for family = AR_AF_INET respectively).   
 * Returns 1 on success, 0 if the string was not a valid address, or <0 on error */
int arinet_pton(int family, const char* src, void* dst);

/* Convert the network address "src" (being a pointer to AR_IN_ADDR for family = AR_AF_INET respectively) into a
 * character string (dst, size). "dst" is a pointer to the buffer with length "size". After the function call the buffer
 * contains the string representation of the address in decimal values (e.g. 192.168.0.1).
 * Return dst on success, or NULL on error */
const char* arinet_ntop(int family, const void* src, char* dst, int size);

/* Convert a short value (2 bytes) from host byte-order to net byte-order */
uint16_t arhtons(uint16_t val);

/* Convert a long value (4 bytes) from host byte-order to net byte-order */
uint32_t arhtonl(uint32_t val);

/* Convert a short value (2 bytes) from net byte-order to host byte-order */
uint16_t arntohs(uint16_t val);

/* Convert a long value (4 bytes) from net byte-order to host byte-order */
uint32_t arntohl(uint32_t val);


#if AR_CORE
#include <private/arNetworkConvertP.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
