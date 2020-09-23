#pragma once
#include <windows.h>
DWORD WINAPI ThreadFunc(LPVOID);
// DWORD는 더블워드 = long
// WINAPI : Windows의 API
// LPVOID : ms에서 사용하는 void* 
int Thread(void (*method)());