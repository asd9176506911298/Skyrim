#pragma once
#include <Windows.h>

struct vec3 { float x, y, z; };

int ix;
extern DWORD EntlistJmpBack = 0x0;
DWORD EntityObjStart = 0x0;
bool alreadyThere = false;

class playerent;
class nameptrClass;

class playerent
{
public:
	char pad_0000[36]; //0x0000
	class nameptrClass* nameptr; //0x0024
	char pad_0028[12]; //0x0028
	vec3 coords; //0x0034
}; //Size: 0x0040


class nameptrClass
{
public:
	char pad_0000[136]; //0x0000
	char* name; //0x0088
}; //Size: 0x008C

playerent* ents[255];
playerent* entsptr;

__declspec(naked) void entityhook()
{
	__asm {
		mov edx, [esi + 0x34]
		mov eax, [esi + 0x38]
		mov EntityObjStart, esi
		pushad
	}

	__asm {
		mov eax, EntityObjStart
		mov entsptr, eax
	}
	
	if (entsptr == nullptr)
	{
		goto GIVE_UP;
	}

	alreadyThere = false;

	for (ix = 0; ix < 254; ix++)
	{
		if (ents[ix] == entsptr)
		{
			alreadyThere = true;
			break;
		}
	}

	if (alreadyThere)
	{
		goto GIVE_UP;
	}
	else
	{
		for (ix = 0; ix < 254; ix++)
		{
			if (ents[ix] == 0)
			{
				ents[ix] = entsptr;
				break;
			}
		}
	}

GIVE_UP:
	__asm {
		popad
		jmp[EntlistJmpBack]
	}
}