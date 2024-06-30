#include "Character.h"
#include "Offsets.h"
#include "Process.h"

Character::Character(std::shared_ptr<Process> process) {
	this->process = process;
}

Character::~Character() {
}

std::string Character::GetName() {
	DWORD dwCharacterNameAddress = process->GetBaseAddress() + Offsets::CharacterName;
	return process->memory->ReadString(dwCharacterNameAddress, 30);
}

CharacterClass Character::GetClass() {
	DWORD dwCharacterClassAddress = process->GetBaseAddress() + Offsets::CharacterClass;
	BYTE characterClass = process->memory->Read<BYTE>(dwCharacterClassAddress);

	switch (characterClass) {
	case 1: return CharacterClass::Warrior;
	case 2: return CharacterClass::Paladin;
	case 3: return CharacterClass::Hunter;
	case 4: return CharacterClass::Rogue;
	case 5: return CharacterClass::Priest;
	case 6: return CharacterClass::DeathKnight;
	case 7: return CharacterClass::Shaman;
	case 8: return CharacterClass::Mage;
	case 9: return CharacterClass::Warlock;
	case 10: return CharacterClass::Monk;
	case 11: return CharacterClass::Druid;
	case 12: return CharacterClass::DemonHunter;
	default: return CharacterClass::Unknown;
	}
}

std::string Character::GetClassName() {
	CharacterClass characterClass = GetClass();

	switch (characterClass) {
	case CharacterClass::Warrior: return "Warrior";
	case CharacterClass::Paladin: return "Paladin";
	case CharacterClass::Hunter: return "Hunter";
	case CharacterClass::Rogue: return "Rogue";
	case CharacterClass::Priest: return "Priest";
	case CharacterClass::DeathKnight: return "Death Knight";
	case CharacterClass::Shaman: return "Shaman";
	case CharacterClass::Mage: return "Mage";
	case CharacterClass::Warlock: return "Warlock";
	case CharacterClass::Monk: return "Monk";
	case CharacterClass::Druid: return "Druid";
	case CharacterClass::DemonHunter: return "Demon Hunter";
	default: return "Unknown";
	}
}