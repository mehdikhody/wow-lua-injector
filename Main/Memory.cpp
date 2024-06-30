#include "Memory.h"

Memory::Memory(HANDLE hProcess) {
	this->hProcess = hProcess;
}

Memory::~Memory() {
}

void Memory::Free(DWORD address) {
	if (!VirtualFreeEx(hProcess, (LPVOID)address, 0, MEM_RELEASE)) {
		std::cerr << "Error: Freeing memory: " << GetLastError() << "\n";
	}
}

std::string Memory::ReadString(DWORD address, SIZE_T size) {
	std::vector<BYTE> buffer(size);
	SIZE_T read = 0;

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