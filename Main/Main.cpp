#include <iostream>
#include "Offsets.h"
#include "Process.h"

int main() {
	std::vector<Process*> processes = Process::GetProcessesByName("Wow.exe");
	if (processes.size() == 0) {
		std::cout << "No process found" << std::endl;
		return 1;
	}

	for (Process* process : processes) {
		std::cout << "Process ID: " << process->GetProcessId() << "\n";
		std::cout << "Process Base Address: " << process->GetBaseAddress() << "\n";
		std::cout << "Character Name: " << process->character->GetName() << "\n";
		std::cout << "Character Class: " << process->character->GetClassName() << "\n\n";
		process->CloseProcess();
	}

	return 0;
}