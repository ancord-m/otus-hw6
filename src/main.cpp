#include <iostream>

#include "command_collector.h"
#include "console_printer.h"
#include "bulk_to_file_writer.h"

int main(int argc, char const *argv[])
{
	CommandCollector commandCollector(3);
	ConsolePrinter consolePrinter(&commandCollector);
	BulkToFileWriter bulkFileWriter(&commandCollector);
	
	for(std::string line; std::getline(std::cin, line); ) {
		commandCollector.captureCommandAndPerformAnalysis(line);	
	}

	commandCollector.tryToNotifyListenersWithLeftFinishedOrUnfinishedCurrentBulk();

	return 0;	
}