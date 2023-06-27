#include <iostream>

#include "PosixFileApi.h"

bool fileExists(char* fileName)
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
