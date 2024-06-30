#include <iostream>
#include "Memory.h"


Memory::Memory(HANDLE handle) : handle(handle) {
	// Initialize the memory class
}

DWORD Memory::Allocate(SIZE_T size) {
	LPVOID address = VirtualAllocEx(handle, NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (address == nullptr) {
		std::cerr << "Error: Unable to allocate memory.\n";
		return 0;
	}

	return reinterpret_cast<DWORD>(address);
}

void Memory::Free(DWORD address) {
	if (!VirtualFreeEx(handle, (LPVOID)address, 0, MEM_RELEASE)) {
		std::cerr << "Error: Unable to free memory.\n";
	}
}

std::string Memory::ReadString(DWORD address, SIZE_T size) {
	std::string buffer(size, '\0');
	if (!ReadProcessMemory(handle, (LPCVOID)address, &buffer[0], size, NULL)) {
		std::cerr << "Error: Unable to read string from memory.\n";
		return "";
	}

	return buffer;
}