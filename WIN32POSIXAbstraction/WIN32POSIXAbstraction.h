#ifndef WIN32POSIXABSTRACTION_H
#define WIN32POSIXABSTRACTION_H

#ifdef __cplusplus
#	include <cstdio>
#else
#	include <stdio.h>
#endif

/* HANDLE */
typedef FILE* HANDLE; // This is practically a file
#define INVALID_HANDLE_VALUE NULL
/* Stricmp */
#include <strings.h>
#define _stricmp strcasecmp
#define stricmp _stricmp
/* DLL */
#define APIENTRY
#define DLL_PROCESS_DETACH 0
#define DLL_PROCESS_ATTACH 1
#define DLL_THREAD_ATTACH 2
#define DLL_THREAD_DETACH 3
/**/
#define STATIC_ASSERT(X,Y) // Do nothing

#endif //WIN32POSIXABSTRACTION_H
