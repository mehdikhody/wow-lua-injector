#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <windows.h>

class Memory {
public:
	Memory(HANDLE hProcess);
	~Memory();

	template <typename T>
	DWORD Allocate(DWORD size = sizeof(T));

	void Free(DWORD address);

	template <typename T>
	void Write(DWORD address, T value);

	template <typename T>
	T Read(DWORD address);

	std::string ReadString(DWORD address, SIZE_T size);

private:
	HANDLE hProcess;
};

template <typename T>
DWORD Memory::Allocate(DWORD size) {
	LPVOID lpAddress = VirtualAllocEx(hProcess, nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (lpAddress == nullptr) {
		std::cerr << "Error: Allocating memory: " << GetLastError() << "\n";
		return 0;
	}

	return reinterpret_cast<DWORD>(lpAddress);
}

template <typename T>
void Memory::Write(DWORD address, T value) {
	SIZE_T written;
	if (!WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(T), &written)) {
		std::cerr << "Error: Writing memory: " << GetLastError() << "\n";
	}

	if (written != sizeof(T)) {
		std::cerr << "Error: Writing memory: " << GetLastError() << "\n";
	}
}

template <typename T>
T Memory::Read(DWORD address) {
	T value = 0;
	SIZE_T read = 0;
	if (!ReadProcessMemory(hProcess, (LPCVOID)address, &value, sizeof(T), &read)) {
		std::cerr << "Error: Reading memory: " << GetLastError() << "\n";
	}

	if (read != sizeof(T)) {
		std::cerr << "Error: Reading memory: " << GetLastError() << "\n";
	}

	return value;
}