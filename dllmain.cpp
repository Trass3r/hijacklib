#include "stdafx.h"

#include <windows.h>
#include <assert.h>

extern int myhookfoo(int a);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	void* pOrgFn = (void*)0x004116f0; // func to overwrite
	ptrdiff_t p = (ptrdiff_t)myhookfoo;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
#if _M_X64
		// 48 b8 35 08 40 00 00 00 00 00   mov rax, 0x0000000000400835
		// ff e0                           jmp rax
		unsigned char codeBytes[12] = { 0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0xff, 0xe0 };
		memcpy(&codeBytes[2], &p, sizeof(void*));
#elif _M_IX86
		// E9 00000000   jmp rel  displacement relative to next instruction
		unsigned char codeBytes[5] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
		p -= (ptrdiff_t)pOrgFn + sizeof(codeBytes);
		memcpy(&codeBytes[1], &p, sizeof(void*));
#else
#error "The following code only works for x86 and x64!"
#endif

		SIZE_T bytesWritten = 0;
		BOOL res = WriteProcessMemory(GetCurrentProcess(),
			pOrgFn, codeBytes, sizeof(codeBytes), &bytesWritten);
		assert(res);
		assert(bytesWritten == sizeof(codeBytes));
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

