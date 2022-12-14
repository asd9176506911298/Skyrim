#pragma once

#include <Windows.h>
#include <vector>

namespace mem 
{
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);
	uintptr_t FindDMAAdy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int>offsets);

	void Patch(BYTE* dst, BYTE* src, unsigned int size);
	void Nop(BYTE* dst, unsigned int size);
	uintptr_t FindDMAAdy(uintptr_t ptr, std::vector<unsigned int>offsets);


}