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

#ifdef LINUX
typedef void *HANDLE; // Pyogenics: Glad I use linux.
#define INVALID_HANDLE_VALUE NULL
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
