#pragma once
#include <windows.h>
DWORD WINAPI ThreadFunc(LPVOID);
// DWORD�� ������� = long
// WINAPI : Windows�� API
// LPVOID : ms���� ����ϴ� void* 
int Thread(void (*method)());