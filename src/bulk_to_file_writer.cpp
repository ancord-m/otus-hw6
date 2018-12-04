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

void BulkToFileWriter::update(const Bulk &receivedBulk)
{
	std::ofstream output;

	output.open(generateFileName());

	if(output.is_open())
	{
		output << generateResultingBulkString(receivedBulk);
	}

	output.close();

	/*
	не могу заставить записать все log файлы в runtime, даже с задержкой. нужна ваша помощь
	*/

	std::chrono::milliseconds delay(100);

	std::this_thread::sleep_for(delay);
}

String BulkToFileWriter::generateFileName(void)
{
	return prefix + std::to_string(time(nullptr)) + extention;
}