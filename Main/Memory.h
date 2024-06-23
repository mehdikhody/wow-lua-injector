#pragma once
#include <vector>
#include <string>
#include <windows.h>

class Memory {
public:
	Memory(HANDLE hProccess);
	~Memory();

	template <typename T>
	DWORD Allocate(DWORD size = sizeof(T));

	void Free(DWORD address);

	template <typename T>
	void Write(DWORD address, T value);

	BYTE ReadByte(DWORD address);
	uint8_t ReadUInt8(DWORD address);
	uint16_t ReadUInt16(DWORD address);
	uint32_t ReadUInt32(DWORD address);
	std::string ReadString(DWORD address, SIZE_T size);

private:
	HANDLE hProcess;
};