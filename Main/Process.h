#pragma once
#include <vector>
#include <windows.h>
#include "Memory.h"
#include "Character.h"

class Process {
public:
	Process(DWORD processId, HANDLE hProcess);
	~Process();

	Memory* memory;
	Character* character;

	HANDLE GetProcessHandle() const;
	DWORD GetProcessId() const;
	DWORD GetBaseAddress();

	static std::vector<Process*> GetProcessesByName(const char* ProcessName);
private:
	HANDLE hProcess;
	DWORD processId;
	DWORD baseAddress;
};