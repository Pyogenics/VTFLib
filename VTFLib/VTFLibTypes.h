#ifndef VTFLIBTYPES_H
#define VTFLIBTYPES_H

#include <cstdint>

// Custom data types
typedef unsigned char	vlBool;				//!< Boolean value 0/1.
typedef char			vlChar;				//!< Single signed character.
typedef unsigned char	vlByte;				//!< Single unsigned byte.
typedef signed short	vlShort;			//!< Signed short floating point value.
typedef unsigned short	vlUShort;			//!< Unsigned short floating point value.
typedef signed int		vlInt;				//!< Signed integer value.
typedef unsigned int	vlUInt;				//!< Unsigned integer value.
typedef signed long		vlLong;				//!< Signed long number.
typedef unsigned long	vlULong;			//!< Unsigned long number.
typedef float			vlSingle;			//!< Floating point number
typedef double			vlDouble;			//!< Double number
typedef void			vlVoid;				//!< Void value.

typedef uint8_t		vlUInt8;
typedef uint16_t	vlUInt16;
typedef uint32_t	vlUInt32;
typedef uint64_t	vlUInt64;

typedef vlSingle		vlFloat;			//!< Floating point number (same as vlSingled).

#define vlFalse 0
#define vlTrue 1

//XXX: Maybe some of this plat stuff needs to be moved into a more appropriate place?
#ifdef LINUX
typedef void *HANDLE; // Pyogenics: Glad I use linux.
#define INVALID_HANDLE_VALUE NULL

#include <strings.h>
#define _stricmp strcasecmp
#define stricmp _stricmp

#define STATIC_ASSERT(X,Y) // Do nothing
#define APIENTRY

#define DLL_PROCESS_DETACH 0
#define DLL_PROCESS_ATTACH 1
#define DLL_THREAD_ATTACH 2
#define DLL_THREAD_DETACH 3
#endif

#ifdef WINDOWS
	#ifdef VTFLIB_EXPORTS
	#define VTFLIB_API __declspec(dllexport)
	#else
	#define VTFLIB_API __declspec(dllimport)
	#endif
#else
	#define VTFLIB_API __attribute__((visibility("default"))) //XXX: Stupid compiler specific code (GCC)
#endif

#endif //TYPES_H
