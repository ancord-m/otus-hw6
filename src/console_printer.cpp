#include "console_printer.h"

ConsolePrinter::ConsolePrinter(CommandCollector *cc)
{
	cc->subscribe(this);
}

void ConsolePrinter::update(const Bulk &receivedBulk)
{
	std::cout << "bulk: ";

	for(auto b_it = receivedBulk.cbegin(); b_it != receivedBulk.cend(); ++b_it)
	{
		if(b_it != receivedBulk.cbegin())
		{
			std::cout << ", ";
		}

		std::cout << *b_it;		
	}

	std::cout << std::endl;
}