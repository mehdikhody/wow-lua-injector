#include <iostream>
#include "Process.h"


int main() {
	ProcessList list = Process::GetProcessesByName("Wow.exe");
	if (list.empty()) {
		std::cerr << "No processes found" << std::endl;
		return 1;
	}

	for (const auto& process : list) {
		std::cout << "Process ID: " << process->GetId() << std::endl;
		std::cout << "Process Handle: " << process->GetHandle() << std::endl;
		std::cout << "Process Base Address: " << process->GetBaseAddress() << std::endl;
		std::cout << std::endl;
	}

	return 0;
}