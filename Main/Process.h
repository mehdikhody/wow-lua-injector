#pragma once
#include <memory>
#include <vector>
#include <windows.h>
#include "Memory.h"

class Process {
public:
	Process(DWORD processId, HANDLE hProcess);
	~Process();

	std::shared_ptr<Memory> memory;

	HANDLE GetProcessHandle() const;
	DWORD GetProcessId() const;
	DWORD GetBaseAddress();

	static std::vector<std::shared_ptr<Process>> GetProcessesByName(const std::string& processName);
private:
	HANDLE hProcess;
	DWORD processId;
	DWORD baseAddress;
};

typedef std::vector<std::shared_ptr<Process>> Processes;