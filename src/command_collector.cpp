#include <iostream>

#include "command_collector.h"

void CommandCollector::captureCommand(std::string command)
{
	std::cout << command << std::endl;
}

void CommandCollector::captureCommand(int command)
{
	std::cout << command << std::endl;
}

int CommandCollector::getBlocksQuantity(void)
{
	return 1;
}