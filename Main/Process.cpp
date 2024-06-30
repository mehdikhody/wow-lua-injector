#include "Process.h"
#include <psapi.h>

#pragma comment(lib, "psapi.lib")

Process::Process(DWORD processId, HANDLE hProcess) {
	this->hProcess = hProcess;
	this->processId = processId;
	GetBaseAddress();

	memory = std::make_shared<Memory>(hProcess);
}

Process::~Process() {
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

Processes Process::GetProcessesByName(const std::string& processName) {
	Processes processes;
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
					if (strcmp(szProcessName, processName.c_str()) == 0) {
						processes.push_back(std::make_shared<Process>(aProcesses[i], hProcess));
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