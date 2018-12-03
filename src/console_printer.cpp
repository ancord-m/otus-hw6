#include "console_printer.h"

ConsolePrinter::ConsolePrinter(CommandCollector *cc)
{
	cc->subscribe(this);
}

void ConsolePrinter::update(const Bulk &receivedBulk)
{
	std::cout << "bulk: ";
	for(auto b : receivedBulk)
	{
		std::cout << b << ", ";
	}
}