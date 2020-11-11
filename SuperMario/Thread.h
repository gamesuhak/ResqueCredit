#pragma once
#include <windows.h>
// DWORD는 더블워드 = long
// WINAPI : Windows의 API
// LPVOID : ms에서 사용하는 void* 
DWORD WINAPI ThreadFunc(LPVOID);
int Thread(void (*method)());