#include <windows.h>

#include "Mutex.h"

HANDLE hDllModule = NULL;

#pragma unmanaged
BOOL APIENTRY DllMain (HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	hDllModule = hModule;
	return TRUE;
}
