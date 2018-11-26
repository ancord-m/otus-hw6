#include <iostream>

#include "command_collector.h"

int main(int argc, char const *argv[])
{
	CommandCollector commandCollector(3);


	for(std::string line; std::getline(std::cin, line); ) {
		commandCollector.captureCommand(line);	
	}
	


	return 0;	
}