#pragma once
#include <windows.h>
// DWORD�� ������� = long
// WINAPI : Windows�� API
// LPVOID : ms���� ����ϴ� void* 
DWORD WINAPI ThreadFunc(LPVOID);
int Thread(void (*method)());