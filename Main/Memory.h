#pragma once
#include <string>
#include <Windows.h>

class Memory
{
public:
	Memory(HANDLE handle);

	DWORD Allocate(SIZE_T size);
	void Free(DWORD address);

	template <typename T>
	void Write(DWORD address, T value);

	template <typename T>
	T Read(DWORD address);

	std::string ReadString(DWORD address, SIZE_T size);

private:
	HANDLE handle;
};

template <typename T>
void Memory::Write(DWORD address, T value) {
	SIZE_T written = 0;
	if (!WriteProcessMemory(handle, (LPVOID)address, &value, sizeof(T), &written)) {
		std::cerr << "Error: Unable to write to memory.\n";
	}

	if (written != sizeof(T)) {
		std::cerr << "Error: Unable to write the correct number of bytes to memory.\n";
	}
}

template <typename T>
T Memory::Read(DWORD address) {
	T buffer{};
	SIZE_T read = 0;
	if (!ReadProcessMemory(handle, (LPCVOID)address, &buffer, sizeof(T), &read)) {
		std::cerr << "Error: Unable to read from memory.\n";
	}

	if (read != sizeof(T)) {
		std::cerr << "Error: Unable to read the correct number of bytes from memory.\n";
	}

	return buffer;
}

