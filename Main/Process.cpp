#include <iostream>
#include "Process.h"
#include <psapi.h>

Process::Process(DWORD id, HANDLE handle) :
	id(id),
	handle(handle),
	baseAddress(0),
	memory(std::make_shared<Memory>(handle))
{
	HMODULE hModules[1024];
	DWORD cbNeeded;
	if (!EnumProcessModules(handle, hModules, sizeof(hModules), &cbNeeded)) {
		return;
	}

	baseAddress = reinterpret_cast<DWORD>(hModules[0]);
}

Process::~Process() {
	CloseHandle(handle);
}

DWORD Process::GetId() const {
	return id;
}

HANDLE Process::GetHandle() const {
	return handle;
}

DWORD Process::GetBaseAddress() const {
	return baseAddress;
}

std::shared_ptr<Memory> Process::GetMemory() const {
	return memory;
}

ProcessList Process::GetProcesses() {
	ProcessList processes;
	DWORD processIds[1024];
	DWORD cbNeeded;
	if (!EnumProcesses(processIds, sizeof(processIds), &cbNeeded)) {
		std::cerr << "Error: Unable to get process list.\n";
		return processes;
	}

	DWORD count = cbNeeded / sizeof(DWORD);
	for (DWORD i = 0; i < count; i++) {
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processIds[i]);
		if (handle == NULL) {
			continue;
		}

		processes.push_back(std::make_shared<Process>(processIds[i], handle));
	}

	return processes;
}

ProcessList Process::GetProcessesByName(const std::string& name) {
	ProcessList processes = GetProcesses();
	ProcessList filteredProcesses;

	for (auto& process : processes) {
		char buffer[1024] = "<unknown>";
		if (!GetModuleBaseNameA(process->GetHandle(), NULL, buffer, sizeof(buffer))) {
			CloseHandle(process->GetHandle());
			continue;
		}

		if (strcmp(buffer, name.c_str()) == 0) {
			filteredProcesses.push_back(process);
		}
		else {
			CloseHandle(process->GetHandle());
		}
	}

	return filteredProcesses;
}

ProcessItem Process::GetProcessById(DWORD id) {
	ProcessList processes = GetProcesses();
	for (auto& process : processes) {
		if (process->GetId() == id) {
			return process;
		}

		CloseHandle(process->GetHandle());
	}

	return nullptr;
}