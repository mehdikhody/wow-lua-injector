#include "Process.h"
#include <psapi.h>

#pragma comment(lib, "psapi.lib")

Process::Process(DWORD processId, HANDLE hProcess) {
	this->hProcess = hProcess;
	this->processId = processId;
	baseAddress = GetBaseAddress();
	memory = new Memory(hProcess);
	character = new Character(memory, baseAddress);
}

Process::~Process() {
	delete memory;
	delete character;
	CloseHandle(hProcess);
}

HANDLE Process::GetProcessHandle() const {
	return hProcess;
}

DWORD Process::GetProcessId() const {
	return processId;
}

DWORD Process::GetBaseAddress() {
	if (baseAddress == 0) {
		HMODULE hModules[1024];
		DWORD cbNeeded;
		if (EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded)) {
			baseAddress = (DWORD) hModules[0];
		}
	}

	return baseAddress;
}

std::vector<Process*> Process::GetProcessesByName(const char* ProcessName) {
	std::vector<Process*> processes;
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	if (EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
		cProcesses = cbNeeded / sizeof(DWORD);
		for (unsigned int i = 0; i < cProcesses; i++) {
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, aProcesses[i]);
			if (hProcess) {
				char szProcessName[MAX_PATH] = "<unknown>";
				HMODULE hMod;
				DWORD cbNeeded;
				if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
					GetModuleBaseNameA(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(char));
					if (strcmp(szProcessName, ProcessName) == 0) {
						processes.push_back(new Process(aProcesses[i], hProcess));
					}
					else {
						CloseHandle(hProcess);
					}
				}
				else {
					CloseHandle(hProcess);
				}
			}
		}
	}

	return processes;
}