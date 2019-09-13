#include <ctime>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

#include "bulk_to_file_writer.h"
#include "resulting_bulk_formatter.h"


BulkToFileWriter::BulkToFileWriter(std::shared_ptr<CommandCollector> cc)
{
	cc->subscribe(this);
}

void BulkToFileWriter::update(const Bulk& receivedBulk)
{
	std::ofstream output;

	output.open(generateFileName(receivedBulk));

	if(output.is_open())
	{
		output << generateResultingBulkString(receivedBulk);
	}

	output.close();
}

std::string BulkToFileWriter::generateFileName(const Bulk& bulk)
{
	std::time_t time_stamp 		= std::chrono::system_clock::to_time_t(bulk.getTimeStamp());
	std::string time_stamp_str 	= std::to_string(time_stamp);
	
	return prefix + time_stamp_str + extention;
}