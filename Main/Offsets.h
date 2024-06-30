#pragma once
#include <windows.h>

namespace Offsets {
	const DWORD WowVersion = 0x8AD851;
	const DWORD AuthState = 0x9CE474;
	const DWORD GameState = 0x7D078A;
	const DWORD CharacterName = 0x879D18;
	const DWORD CharacterClass = 0x879E89;
	const DWORD Lua_DoString = 0x419210;
	const DWORD Lua_GetLocalizedText = 0x3225E0;
	const DWORD Detour = 0xBF0F0;
	const DWORD Overwritten[9] = {
		0x55,
		0x8B,
		0xEC,
		0x81,
		0xEC,
		0xF8,
		0x00,
		0x00,
		0x00
	};
}