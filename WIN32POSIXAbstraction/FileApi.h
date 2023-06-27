//XXX: ONLY INCLUDE THIS ON NON WINDOWS SYSTEMS
#ifndef FILEAPI_H
#define FILEAPI_H

#ifndef __cplusplus
#	include <stdbool.h>
#endif

#include "WIN32POSIXAbstraction.h"

//https://learn.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-overlapped
typedef struct _OVERLAPPED {
	unsigned long Internal;
	unsigned long InternalHigh;
	union {
		struct {
			unsigned long Offset;
			unsigned long OffsetHigh;
		} DUMMYSTRUCTNAME;
		void *Pointer;
	} DUMMYUNIONNAME;
	HANDLE hEvent;
} OVERLAPPED, *LPOVERLAPPED;

//https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/aa379560(v=vs.85)
typedef struct _SECURITY_ATTRIBUTES {
	unsigned long nLength;
	void *lpSecurityDescriptor;
	bool bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

//https://learn.microsoft.com/en-us/windows/win32/secauthz/access-mask
#define GENERIC_READ 0x80000000
#define GENERIC_WRITE 0x40000000
#define GENERIC_EXECUTE 0x20000000
#define GENERIC_ALL 0x10000000

//https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
#define FILE_SHARE_DELETE 0x00000004
#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002

#define CREATE_NEW 1
#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define OPEN_ALWAYS 4
#define TRUNCATE_EXISTING 5

#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#define FILE_ATTRIBUTE_ARCHIVE 0x20
#define FILE_ATTRIBUTE_ENCRYPTED 0x4000
#define FILE_ATTRIBUTE_HIDDEN 0x2
#define FILE_ATTRIBUTE_NORMAL 0x80
#define FILE_ATTRIBUTE_OFFLINE 0x1000
#define FILE_ATTRIBUTE_READONLY 0x1
#define FILE_ATTRIBUTE_SYSTEM 0x4
#define FILE_ATTRIBUTE_TEMPORARY 0x100

#define FILE_FLAG_BACKUP_SEMANTICS 0x02000000
#define FILE_FLAG_DELETE_ON_CLOSE 0x04000000
#define FILE_FLAG_NO_BUFFERING 0x20000000
#define FILE_FLAG_OPEN_NO_RECALL 0x00100000
#define FILE_FLAG_OPEN_REPARSE_POINT 0x00200000
#define FILE_FLAG_OVERLAPPED 0x40000000
#define FILE_FLAG_POSIX_SEMANTICS 0x01000000
#define FILE_FLAG_RANDOM_ACCESS 0x10000000
#define FILE_FLAG_SESSION_AWARE 0x00800000
#define FILE_FLAG_SEQUENTIAL_SCAN 0x08000000
#define FILE_FLAG_WRITE_THROUGH 0x80000000

#define SECURITY_SQOS_PRESENT
#define SECURITY_ANONYMOUS
#define SECURITY_CONTEXT_TRACKING
#define SECURITY_DELEGATION
#define SECURITY_EFFECTIVE_ONLY
#define SECURITY_IDENTIFICATION
#define SECURITY_IMPERSONATION

HANDLE CreateFile(
	const char                *lpFileName,
	unsigned long                 dwDesiredAccess,
  	unsigned long                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	unsigned long                 dwCreationDisposition,
  	unsigned long                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile
);

//https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile
bool ReadFile(HANDLE hFile, void *lpBuffer, unsigned long nNumberOfBytesToRead, unsigned long *lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);

//https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile
bool WriteFile(HANDLE hFile, const void *lpBuffer, unsigned long nNumberOfBytesToWrite, unsigned long* lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);

//https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfilesize
unsigned long GetFileSize(HANDLE hFile, unsigned long* lpFileSizeHigh);

//https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-setfilepointer
unsigned long SetFilePointer(HANDLE hFile, long lDistanceToMove, long* lpDistanceToMoveHigh, unsigned long dwMoveMethod);

#define FILE_BEGIN 0
#define FILE_CURRENT 1
#define FILE_END 2

//https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
bool CloseHandle(HANDLE handle);

#endif //FILEAPI_H
