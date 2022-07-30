// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include "hook.h"
#include "patternscanInternal.h"
#include "Hooks_reclass.h"

DWORD WINAPI InitHooks(HMODULE hModule)
{
    void* entityAddy = ScanModIn((char*)"\x8b\x56\x00\x8b\x46\x00\x8b\x4e\x00\x8d\x7e", (char*)"xx?xx?xx?xx", "TESV.exe");
    EntlistJmpBack = (DWORD)entityAddy + 6;
    Detour32((BYTE*)entityAddy, (BYTE*)entityhook, 6);

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitHooks, hModule, 0, 0);
        if (hThread) CloseHandle(hThread);
    }
    return TRUE;
}

