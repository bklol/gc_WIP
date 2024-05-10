#pragma once
#include "platform.h"
#include "stdint.h"
#include "utils/module.h"

namespace modules
{
	inline CModule *server;
}

typedef CUtlStringToken WorldGroupId_t;

namespace addresses
{
	void Initialize();
	inline void (FASTCALL *Init_GC_SERVER_SYSTEM)(void* pSystem);
	inline void (FASTCALL *Hello_SERVER_GC)(void* pGC);
}

namespace sigs
{
#ifdef _WIN32
	inline const byte *IGameSystem_InitAllSystems_pFirst = (byte *)"\x48\x8B\x1D\x2A\x2A\x2A\x2A\x48\x85\xDB\x0F\x84\x2A\x2A\x2A\x2A\xBE\x2A\x2A\x2A\x2A\x0F\x1F\x00\x48\x8B\x7B\x10";
	inline const byte *Hello_SERVER_GC = (byte *)"\x40\x55\x41\x56\x48\x8D\x6C\x24\x2A\x48\x81\xEC\x88\x00\x00\x00";
#else
	inline const byte *IGameSystem_InitAllSystems_pFirst = (byte *)"\x4C\x8B\x35\x2A\x2A\x2A\x2A\x4D\x85\xF6\x75\x2D\xE9\x2A\x2A\x2A\x2A\x0F\x1F\x40\x00\x48\x8B\x05";
	inline const byte *Hello_SERVER_GC = (byte *)"\x55\x48\x89\xE5\x41\x55\x41\x54\x53\x48\x83\xEC\x58\x0F\xB6\x05";
#endif
}