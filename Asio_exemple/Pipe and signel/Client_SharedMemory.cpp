/* power of memory mapped file */

#include <Windows.h>
#include <cstdio>



int main() {

	puts("Client Chat\n");

	HANDLE  handle = CreateFileMappingW(INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		256,
		L"memory"
	);

	LPVOID address = MapViewOfFile(handle,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		0
	);

	// Creating Event
	HANDLE hEvent = CreateEvent(NULL,
		FALSE,
		FALSE,
		L"memory");

	for (;;) {
		WaitForSingleObject(hEvent, INFINITE);
		printf("%s", (char*)address);
	}


	CloseHandle(handle);
	return 0;
}
