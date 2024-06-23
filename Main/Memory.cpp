#include "Memory.h"
#include <iostream>

Memory::Memory(HANDLE hProcess) {
	this->hProcess = hProcess;
}

Memory::~Memory() {
}

template <typename T>
DWORD Memory::Allocate(DWORD size) {
	LPVOID lpAddress = VirtualAllocEx(hProcess, nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (lpAddress == nullptr) {
		std::cerr << "Error: Allocating memory: " << GetLastError() << "\n";
		return 0;
	}

	return reinterpret_cast<DWORD>(lpAddress);
}

void Memory::Free(DWORD address) {
	if (!VirtualFreeEx(hProcess, (LPVOID)address, 0, MEM_RELEASE)) {
		std::cerr << "Error: Freeing memory: " << GetLastError() << "\n";
	}
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

BYTE Memory::ReadByte(DWORD address) {
	BYTE value = 0;
	SIZE_T read;
	if (!ReadProcessMemory(hProcess, (LPCVOID)address, &value, sizeof(BYTE), &read)) {
		std::cerr << "Error: Reading memory: " << GetLastError() << "\n";
	}

	if (read != sizeof(BYTE)) {
		std::cerr << "Error: Reading memory: " << GetLastError() << "\n";
	}

	return value;
}

uint8_t Memory::ReadUInt8(DWORD address) {
	uint8_t value = 0;
	SIZE_T read;
	if (!ReadProcessMemory(hProcess, (LPCVOID)address, &value, sizeof(uint8_t), &read)) {
		std::cerr << "Error: Reading memory: " << GetLastError() << "\n";
	}

	if (read != sizeof(uint8_t)) {
		std::cerr << "Error: Reading memory: " << GetLastError() << "\n";
	}

	return value;
}

uint16_t Memory::ReadUInt16(DWORD address) {
	uint16_t value = 0;
	SIZE_T read;
	if (!ReadProcessMemory(hProcess, (LPCVOID)address, &value, sizeof(uint16_t), &read)) {
		std::cerr << "Error: Reading memory: " << GetLastError() << "\n";
	}

	if (read != sizeof(uint16_t)) {
		std::cerr << "Error: Reading memory: " << GetLastError() << "\n";
	}

	return value;
}

uint32_t Memory::ReadUInt32(DWORD address) {
	uint32_t value = 0;
	SIZE_T read;
	if (!ReadProcessMemory(hProcess, (LPCVOID)address, &value, sizeof(uint32_t), &read)) {
		std::cerr << "Error: Reading memory: " << GetLastError() << "\n";
	}

	if (read != sizeof(uint32_t)) {
		std::cerr << "Error: Reading memory: " << GetLastError() << "\n";
	}

	return value;
}

std::string Memory::ReadString(DWORD address, SIZE_T size) {
	std::vector<BYTE> buffer(size);
	SIZE_T read;

	if (!ReadProcessMemory(hProcess, (LPCVOID)address, buffer.data(), size, &read)) {
		std::cerr << "Error: Reading memory: " << GetLastError() << "\n";
	}

	if (read != size) {
		std::cerr << "Error: Reading memory: " << GetLastError() << "\n";
	}

	std::string result(buffer.begin(), buffer.end());
	size_t pos = result.find('\0');
	if (pos != std::string::npos) {
		result = result.substr(0, pos);
	}

	return result;
}