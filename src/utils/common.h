#ifndef COMMON_H
#define CPMMON_H

#include "os.h"
#include "includes.h"
#include "print.h"
#if defined(__linux__) || defined(__GLIBC__)
#include <endian.h>
#include <byteswap.h>
#endif /*  __linux__ */

#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__DragonFly__) || \
	defined(__OpenBSD__)
#include <sys/type.h>
#include <sys/endian.h>
#define __BYTE_ORDER    _BYTE_ORDER
#define __LITTLE_ENDIAN _LITTLE_ENDIAN
#define __BIG_ENDIAN    _BIG_ENDIAN
#ifdef __OpenBSD__
#define bswap_16 swap16
#define bswap_32 swap32
#define bswap_64 swap64
#else /* __OpenBSD__ */
#define bswap_16 bswap16
#define bswap_32 bswap32
#define bswap_64 bswap64
#endif /* __OpenBSD__ */
#endif /* defined(__FreeBSD__) || defined(__NetBSD__) ||
	          * defined(__DragonFly__) || defined(__OpenBSD__) */

#ifdef __APPLE__
#include <sys/types.h>
#include <machine/endian.h>
#define __BYTE_ORDER    _BYTE_ORDER
#define __LITTLE_ENDIAN _LITTLE_ENDIAN
#define __BIG_ENDIAN    _BIG_ENDIAN
static inline unsigned short bswap_16(unsigned short v){
	return ((v & 0xff) << 8) | (v >> 8);
}

static inline unsigned int bswap_32(unsigned int v ){
	return ((v & 0xff) << 24) | ((v & 0xff00) << 8) |
		((v & 0xff0000) >> 8) | (v >>24);
}
#endif /* __APPLE__ */

#ifdef CONFIG_NATIVE_WINDOWS
#include<winsock.h>

typedef int socklen_t;

#ifndef MSG_DONTWAIT
#define MSG_DONTWAIT 0 /* not supported */
#endif

#endif /* CONFIG_NATIVE_WINDOWS */

#ifdef _MSC_VER
#define inline __inline

#undef vsnprintf
#define vsnprintf _vsnprintf
#undef close
#define close closesocket
#endif /* _MSC_VER */


/* Define platform specific integer types */

#ifdef _MSC_VER
typedef UINT64 u64;
typedef UINT32 u32;
typedef UINT16 u16;
typedef UINT8 u8;
typedef INT64 s64;
typedef INT32 s32;
typedef INT16 s16;
typedef INT8 s8;
#define WPA_TYPES_DEFINED
#endif /* _MSC_VER */

#ifdef __vxworks
typedef unsigned long long u64;
typedef UINT32 u32;
typedef UINT16 u16;
typedef UINT8 u8;
typedef long long s64;
typedef INT32 s32;
typedef INT16 s16;
typedef INT8 s8;
#define WPA_TYPES_DEFINED
#endif /* __vxworks */

#ifndef WPA_TYPES_DEFINED
#ifdef CONFIG_USE_INTTYPES_H
#include <inttypes.h>
#else
#include <stdint.h>
#endif
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef int64_t s64;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;
#define WPA_TYPES_DEFINED
#endif /* !WPA_TYPES_DEFINED */

/* Define platform specific byte swapping macros */

#if defined(__CYGWIN__) || defined(CONFIG_NATIVE_WINDOWS)

static inline unsigned short hack_swap_16(unsigned short v){
	        return ((v & 0xff) << 8) | (v >> 8);
}

static inline unsigned int hack_swap_32(unsigned int v)
{
	        return ((v & 0xff) << 24) | ((v & 0xff00) << 8) |
			                ((v & 0xff0000) >> 8) | (v >> 24);
}

#define le_to_host16(n) (n)
#define host_to_le16(n) (n)
#define be_to_host16(n) hack_swap_16(n)
#define host_to_be16(n) hack_swap_16(n)
#define le_to_host32(n) (n)
#define host_to_le32(n) (n)
#define be_to_host32(n) hack_swap_32(n)
#define host_to_be32(n) hack_swap_32(n)

#define WPA_BYTE_SWAP_DEFINED

#endif /* __CYGWIN__ || CONFIG_NATIVE_WINDOWS */
#endif /* COMMON_H */
