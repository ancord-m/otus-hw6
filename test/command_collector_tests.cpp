#define BOOST_TEST_MODULE command_collector

#include <boost/test/unit_test.hpp>
#include "command_collector.h"

BOOST_AUTO_TEST_SUITE(command_collector)

BOOST_AUTO_TEST_CASE(BlockSizeEqualsOne_OneCmdCaptured_OneBlockCreated)
{
	int blockSize = 1;
	CommandCollector cmdClctr(blockSize);

	cmdClctr.captureCommand("commmand");

	BOOST_CHECK_EQUAL(1, cmdClctr.getBlocksQuantity());
	/*
	1. выставить размер блока
	2. подготовить новый блок
	2. собрать команды
	3. завершить блок
	*/	
}

BOOST_AUTO_TEST_SUITE_END()