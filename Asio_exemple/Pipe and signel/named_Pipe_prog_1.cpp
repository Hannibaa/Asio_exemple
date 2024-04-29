/*
           CREATING NAMED SHARED MEMORY

  FIRST PROCESS
    The first process creates the file mapping object by calling the CreatFileMapping function
  with INVALID_HANDLE_VALUE and a name for the object. By using the PAGE_READWRITE flag, the 
  process has read/write permission to the memory through any file views that are created.

    Then the process uses file mapping object handle that CreateFileMapping returns in a call
  to MapViewOfFile to create a view of the file in the process address space. The MapViewOfFile
  function returns a pointer  to the file view, pBuf. The process then uses the CopyMemory function 
  to write a string to the view that can be accessed by other processes.

    Prefixing the file mapping object names with "Global\" allows processes to communicate with each
  other even if they are in defferent terminal server sessions. This requirees that the first process
  must have the SeCreateGlobalPrivilege privilege.

    When the process no longer needs access to the file mapping object, it should call the CloseHandle
  function. When all handles are closes, the system can free the section of the paging file that the 
  object uses.
*/

#include <Windows.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include "MyLib/Console_Library/escape_code.h"


#define      BUF_SIZE     256

TCHAR  szName[] = TEXT("Global\\MyFileMap");
TCHAR  szMsg[] = TEXT("Message from first Process");


int main() {
    std::cout << "First Process\n";
	
    HANDLE   hMapFile;
    LPCTSTR  pBuf;

    // 1. 
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,                                 // use paging file
        NULL,                                                 // default security
        PAGE_READWRITE,                                       // read/write access
        0,                                                    // maximum object size (high-order DWORD)
        BUF_SIZE,                                             // maximum object size (low-order DWORD)
        szName                                                // name of mapping object
    );

    if (hMapFile == NULL) {
        std::wcout << L"Could not create file mapping object" << GetLastError() << '\n';
        std::cin.get();
        return 1;
    }

    pBuf = (LPTSTR)MapViewOfFile(
        hMapFile,                           // handle to map object
        FILE_MAP_ALL_ACCESS,                // read/write permission
        0,
        0,
        BUF_SIZE
    );

    if (pBuf == NULL) {
        std::wcout << L"Could not map view of file" << GetLastError() << L'\n';

        CloseHandle(hMapFile);
        std::cin.get();
        return 1;
    }


    CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
    _getch();

    UnmapViewOfFile(pBuf);

    CloseHandle(hMapFile);
    std::cout << "End of program";
    std::cin.get();

    return 1;
}