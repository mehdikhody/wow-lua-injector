#include <iostream>
#include "Process.h"

int main() {
	Processes processes = Process::GetProcessesByName("Wow.exe");
	if (processes.empty()) {
		std::cout << "No process found" << std::endl;
		return 1;
	}

	for (std::shared_ptr<Process> process : processes) {
		std::cout << "Process ID: " << process->GetProcessId() << "\n";
		std::cout << "Process Base Address: " << process->GetBaseAddress() << "\n";
		std::cout << "\n\n";
	}

	return 0;
}