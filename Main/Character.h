#pragma once
#include <string>
#include "Memory.h"

enum class CharacterClass {
	Unknown,
	Warrior,
	Paladin,
	Hunter,
	Rogue,
	Priest,
	DeathKnight,
	Shaman,
	Mage,
	Warlock,
	Monk,
	Druid,
	DemonHunter
};

class Character {
public:
	Character(Memory* memory, DWORD baseAddress);
	~Character();

	std::string GetName();
	CharacterClass GetClass();
	std::string GetClassName();

private:
	Memory* memory;
	DWORD baseAddress;
};