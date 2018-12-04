#include "bulk_to_file_writer.h"

BulkToFileWriter::BulkToFileWriter(CommandCollector *cc)
{
	cc->subscribe(this);
}

void BulkToFileWriter::update(const Bulk &receivedBulk)
{

}