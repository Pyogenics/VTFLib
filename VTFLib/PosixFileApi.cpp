#include <iostream>

#include "PosixFileApi.h"

bool fileExists(const char* fileName)
{
	bool exists = false;
	FILE* file = fopen(fileName, "r");
	if (file)
		exists = true;
	fclose(file);

	return exists;
}

HANDLE CreateFile(
	const char*		lpFileName,
	unsigned long		dwDesiredAccess,
  	unsigned long		dwShareMode,
	LPSECURITY_ATTRIBUTES	lpSecurityAttributes,
	unsigned long		dwCreationDisposition,
  	unsigned long		dwFlagsAndAttributes,
	HANDLE			hTemplateFile
)
{
	FILE* file;

	bool r = false;
	bool w = false;
	// Determine access mode
	if (dwDesiredAccess && GENERIC_READ == GENERIC_READ)
	{
		r = true;
	}
	if (dwDesiredAccess && GENERIC_WRITE == GENERIC_WRITE)
	{
		w = true;
	}

	char mode[4];

	if (r && w)
		strncpy(mode, "rb+", 3);
	else if (r)
		strncpy(mode, "rb", 3);
	else
		strncpy(mode, "wb", 3);

	switch (dwCreationDisposition)
	{
		// Create a new file if it doesn't exist already
		case CREATE_NEW:
			if (fileExists(lpFileName))
				break;
			file = fopen(lpFileName, "wb");
			fclose(file);
			file = fopen(lpFileName, mode);
			break;
		// Always create a new file
		case CREATE_ALWAYS:
			file = fopen(lpFileName, "wb");
			fclose(file);
			file = fopen(lpFileName, mode);
			break;
		// Only open the file if it exists
		case OPEN_EXISTING:
			if (fileExists(lpFileName))
				file = fopen(lpFileName, mode);
			break;
		// Open the file, creat it if it doesn't exist
		case OPEN_ALWAYS:
			if (!fileExists(lpFileName))
			{
				file = fopen(lpFileName, "wb");
				fclose(file);
			}
			file = fopen(lpFileName, mode);	
			break;
		// Open the file and clear it if it exists and only if GENERIC_WRITE is set
		case TRUNCATE_EXISTING:
			if ((dwDesiredAccess && GENERIC_WRITE != GENERIC_WRITE) || !fileExists(lpFileName))
				break;
			file = fopen(lpFileName, mode);
			break;
		//XXX: Fail gracefully
		default:
			break;
	}

	// Unimplemented features
	if (dwFlagsAndAttributes || lpSecurityAttributes || dwShareMode || hTemplateFile)
		std::cout << "Warning: CreateFile recieved args it doesn't implement.";

	return (HANDLE)file;
}

bool ReadFile(HANDLE hFile, void *lpBuffer, unsigned long nNumberOfBytesToRead, unsigned long *lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
{
	bool success = true;
	if(!fgets((char*)lpBuffer, nNumberOfBytesToRead, hFile))
		success = false;

	// Unimplemented features
	if (lpNumberOfBytesRead || lpOverlapped)
		std::cout << "Warning: ReadFile recieved args it doesn't implement.";

	return success;
}

bool WriteFile(HANDLE hFile, const void *lpBuffer, unsigned long nNumberOfBytesToWrite, unsigned long* lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
	bool success = false;
	char* trimmedBuffer = (char*)malloc(nNumberOfBytesToWrite+1); // Always +1 to include a null character for fputs
	memcpy(trimmedBuffer, lpBuffer, nNumberOfBytesToWrite);

	if (fputs(trimmedBuffer, hFile) != EOF)
		success = true;

	free(trimmedBuffer); // FREE THE BUFFER!

	return success;
}

unsigned long GetFileSize(HANDLE hFile, unsigned long* lpFileSizeHigh)
{
	unsigned long filePos = ftell(hFile);
	fseek(hFile, 0L, SEEK_END);
	unsigned long size = ftell(hFile);
	fseek(hFile, filePos, SEEK_SET);

	//XXX: Ignoring lpFileSizeHigh, why is this even a thing?

	return size;
}


unsigned long SetFilePointer(HANDLE hFile, long lDistanceToMove, long* lpDistanceToMoveHigh, unsigned long dwMoveMethod)
{
	switch (dwMoveMethod)
	{
		case FILE_BEGIN:
			fseek(hFile, lDistanceToMove, SEEK_SET);
			break;
		case FILE_CURRENT:
			fseek(hFile, lDistanceToMove, SEEK_CUR);
			break;
		case FILE_END:
			fseek(hFile, lDistanceToMove, SEEK_END);
			break;
	}

	return ftell(hFile);
}


bool CloseHandle(HANDLE handle)
{
	if (fclose(handle) == 0)
		return 1;
	else
		return 0;
}
