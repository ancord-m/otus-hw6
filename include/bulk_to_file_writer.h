#ifndef BULK_TO_FILE_WRITER_H
#define BULK_TO_FILE_WRITER_H

#include "aliases.h"
#include "ibulk_updater.h"
#include "command_collector.h"

class BulkToFileWriter : public iBulkUpdater
{
	public:
		BulkToFileWriter(CommandCollector *);
	   ~BulkToFileWriter() = default; 

	   void update(const Bulk &) override;
};

#endif