#pragma once
#include <vector>
#include <memory>
#include <Windows.h>
#include "Memory.h"

class Process
{
public:
	Process(DWORD id, HANDLE handle);
	~Process();

	DWORD GetId() const;
	HANDLE GetHandle() const;
	DWORD GetBaseAddress() const;
	std::shared_ptr<Memory> GetMemory() const;

	static std::vector<std::shared_ptr<Process>> GetProcesses();
	static std::vector<std::shared_ptr<Process>> GetProcessesByName(const std::string& name);
	static std::shared_ptr<Process> GetProcessById(DWORD id);

private:
	DWORD id;
	HANDLE handle;
	DWORD baseAddress;
	std::shared_ptr<Memory> memory;
};

typedef std::shared_ptr<Process> ProcessItem;
typedef std::vector<ProcessItem> ProcessList;