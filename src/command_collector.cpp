#include <iostream>

#include "command_collector.h"

void CommandCollector::captureCommand(std::string command)
{
	
	if(isThisOpenningCurlyBrace(command))
	{
		openCurlyBrace();
		bulkFormedDynamicly(true);
	}
	else if(isThisClosingCurlyBrace(command))
	{
		closeCurlyBrace();
	}
	else
	{
		storeCommandIntoCurrentBulk(command);
	}


	if(doesBulkFormedDynamicly())
	{
		notify_IfAllCurlyBracesAreClosed();
	}
	else
	{
		notify_IfCommandBlockSizeIsReached();
	}		
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

bool CommandCollector::isThisOpenningCurlyBrace(String &command)
{
	return ( 0 == command.compare("{") );
}

bool CommandCollector::isThisClosingCurlyBrace(String &command)
{
	return ( 0 == command.compare("}") );
}

void CommandCollector::storeCommandIntoCurrentBulk(String command)
{
	currentBulk.push_back(command); //potential failire?
}

void CommandCollector::openCurlyBrace(void)
{
	++braceCounter;
}

void CommandCollector::closeCurlyBrace(void)
{
	--braceCounter;
}

void CommandCollector::bulkFormedDynamicly(bool v)
{
	formingCurrentBulkDynamicly = v;
}

bool CommandCollector::doesBulkFormedDynamicly(void)
{
	return formingCurrentBulkDynamicly;
}

void CommandCollector::notify_IfAllCurlyBracesAreClosed(void)
{
	std::cout << braceCounter << std::endl;

	if(0 == braceCounter)
	{
		bulkFormedDynamicly(false);
		notify();
	} 
}

void CommandCollector::notify_IfCommandBlockSizeIsReached(void)
{
	if(currentBulk.size() == commandBlockSize) notify();
}