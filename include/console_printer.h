#ifndef CONSOLE_PRINTER_H
#define CONSOLE_PRINTER_H

#include <iostream>

#include "aliases.h"
#include "ibulk_updater.h"
#include "command_collector.h"

class ConsolePrinter : public iBulkUpdater
{
	public:
		ConsolePrinter(CommandCollector *cc);

	   ~ConsolePrinter() = default;	

		void update(const Bulk &receivedBulk) override;
};

#endif