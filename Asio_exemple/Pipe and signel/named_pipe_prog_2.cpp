#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>

#pragma comment(lib, "user32.lib")

#define BUF_SIZE     256
TCHAR   szName[] = TEXT("Global\\MyFileMap");


int main() {
	std::cout << "Second Process 2\n";

	HANDLE      hMapFile;
	LPCTSTR     pBuf;

	hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,						// read/write access
		FALSE,										// do not inherit the name
		szName										// name of mapping object
	);

	if (hMapFile == NULL) {
		std::wcout << L"Could not open file mapping object " << GetLastError() << '\n';
		std::cin.get();
		return 1;
	}

	pBuf = (LPTSTR)MapViewOfFile(
		hMapFile,									// handle to map object
		FILE_MAP_ALL_ACCESS,						// read/write permission
		0,
		0,
		BUF_SIZE
	);

	if (pBuf == NULL) {
		std::wcout << L"Could not map view file" << GetLastError() << "\n";

		CloseHandle(hMapFile);
		std::cin.get();
		return 1;
	}

	MessageBox(NULL, pBuf, TEXT("Process 2"), MB_OK);

	UnmapViewOfFile(pBuf);

	CloseHandle(hMapFile);

	std::cout << "End of program";
	std::cin.get();
	return 0;
}