#include <iostream>

#include "command_collector.h"
#include "console_printer.h"

int main(int argc, char const *argv[])
{
	CommandCollector commandCollector(3);
	ConsolePrinter consolePrinter(&commandCollector);
	
	for(std::string line; std::getline(std::cin, line); ) {
		commandCollector.captureCommand(line);	
	}

	commandCollector.tryToNotifyListenersWithLeftFinishedOrUnfinishedCurrentBulk();

	return 0;	
}