#include <iostream>

#include "command_collector.h"

void CommandCollector::captureCommand(std::string command)
{
	if(0 != command.compare("{")) //&& 0 != command.compare("}"))
	{
		currentBulk.push_back(command);
	}	

	if(currentBulk.size() == commandBlockSize) notify();
}

void CommandCollector::subscribe(iBulkUpdater *listener)
{
	listeners.push_back(listener);
}

void CommandCollector::notify(void)
{
	for(auto l : listeners) {
		l->update(currentBulk);
	}
}