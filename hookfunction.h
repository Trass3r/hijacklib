#pragma once
#include "stdafx.h"

#include <windows.h>
#include <assert.h>
#include <type_traits>

static void overWriteMem(ptrdiff_t oldRef, void* newFn)
{
	ptrdiff_t p = reinterpret_cast<ptrdiff_t>(newFn);

	SIZE_T bytesWritten = 0;
	BOOL res = WriteProcessMemory(GetCurrentProcess(),
		(void*)oldRef, &p, sizeof(p), &bytesWritten);
	assert(res);
	assert(bytesWritten == sizeof(p));
}

static void replaceFn(ptrdiff_t oldFn, void* newFn)
{
	ptrdiff_t p = reinterpret_cast<ptrdiff_t>(newFn);

#if _M_X64
	// 48 b8 35 08 40 00 00 00 00 00   mov rax, 0x0000000000400835
	// ff e0                           jmp rax
	unsigned char codeBytes[12] = { 0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0xff, 0xe0 };
	memcpy(&codeBytes[2], &p, sizeof(void*));
#elif _M_IX86
	// E9 00000000   jmp rel  displacement relative to next instruction
	unsigned char codeBytes[5] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
	p -= ptrdiff_t(oldFn) + sizeof(codeBytes);
	memcpy(&codeBytes[1], &p, sizeof(void*));
#else
#error "The following code only works for x86 and x64!"
#endif

	SIZE_T bytesWritten = 0;
	BOOL res = WriteProcessMemory(GetCurrentProcess(),
		(void*)oldFn, codeBytes, sizeof(codeBytes), &bytesWritten);
	assert(res);
	assert(bytesWritten == sizeof(codeBytes));
}

//! helper for getting address of member function
template <typename T>
static inline void* memFn2ptr(T t)
{
	static_assert(std::is_member_function_pointer<T>::value, "");
	static_assert(sizeof(T) == sizeof(void*), "");
	union B
	{
		T t;
		void* p;
	};
	B b;
	b.t = t;
	return b.p;
}
