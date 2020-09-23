#define WIN32_LEAN_AND_MEAN
#include "Thread.h"
#include <stdio.h>
#include <stdlib.h>

int global = 1;
static int MethodCount = 0;

int Thread(void (*method)())
{
    HANDLE handle; //스레드를 접근하기 위한 손잡이 개념
    DWORD threadId;
    //printf("");
    handle = CreateThread(NULL, 0, method, (LPVOID)MethodCount++, 0, &threadId);
    if (handle)
    {
        //printf("Thread launched %d\n", MethodCount);
        CloseHandle(handle);
    }
    Sleep(100);
    return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc(LPVOID n)
{
    
}
// 참고 : https://doorbw.tistory.com/27 [Tigercow.Door]