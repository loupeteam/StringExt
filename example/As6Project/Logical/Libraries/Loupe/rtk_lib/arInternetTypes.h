
/* Base definition for AR socket and conversion functions */


#ifndef _AR_INTERNET_TYPES_H_
#define _AR_INTERNET_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
	
/* Protocols - used for arsocket, getsockopt, setsockopt */
#define AR_IPPROTO_IP			0			/* Internet Protocol version 4.  */
#define	AR_IPPROTO_ICMP			1			/* control message protocol */
#define AR_IPPROTO_TCP			6			/* tcp */
#define AR_IPPROTO_UDP			17			/* user datagram protocol */
#define AR_IPPROTO_RAW			255			/* raw IP packet */

/* values for AR_IN_ADDR struct */
#define AR_INADDR_ANY			0x00000000UL
#define AR_INADDR_BROADCAST		0xffffffffUL	/* must be masked */
#define AR_INADDR_NONE			0xffffffffUL	/* -1 return */
#define AR_INADDR_LOOPBACK		0x7f000001UL

/* Address families - used for arsocket, arinet_ntop, arinet_pton */
#define	AR_AF_UNSPEC			0			/* unspecified */
#define AR_AF_INET				2			/* internetwork: UDP, TCP, etc. */

/* Internet address (contains AR_INADDR_xxx values) */
typedef struct AR_IN_ADDR
{
	uint32_t addr;
} AR_IN_ADDR;


#ifdef __cplusplus
}
#endif

#endif
