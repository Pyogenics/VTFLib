/*
 * VTFLib
 * Copyright (C) 2005-2011 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

// ============================================================
// NOTE: This file is commented for compatibility with Doxygen.
// ============================================================
/*!
	\file StdAfx.h
	\brief Application framework header plus VTFLib custom data types.
*/

#ifndef STDAFX_H
#define STDAFX_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <cstring>

#include "VTFLibTypes.h"

#ifdef _WIN32
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
/* Visibility */
//XXX: Maybe this should be under _MSC_VER (duplicate in other places)
#	ifdef VTFLIB_EXPORTS
#		define VTFLIB_API __declspec(dllexport)
#	else
#		define VTFLIB_API __declspec(dllimport)
#	endif
#else
#	include "WIN32POSIXAbstraction.h"
#endif

#ifdef _MSC_VER
#	if _MSC_VER >= 1600 // Visual Studio 2010
#		define STATIC_ASSERT(condition, message) static_assert(condition, message)
#	else
#		define STATIC_ASSERT(condition, message) typedef char __C_ASSERT__[(condition) ? 1 : -1]
#	endif
#	if _MSC_VER >= 1400
#		define _CRT_SECURE_NO_WARNINGS
#		define _CRT_NONSTDC_NO_DEPRECATE
#	endif
#elif __GNUC__ >= 4
#	define VTFLIB_API __attribute__((visibility("default"))) //XXX: Stupid compiler specific code (GCC)
#else
#	define VTFLIB_API
#endif

#endif //STDAFX_H
