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

/*
тесты:
- блок завершается при достижении N
- блок завершается при EOF сигнале
- если получен {, то N игнорируется, данные собираюся до }
- предыдущий блок завершается при получении  первого { и поступающие данные складываются в новый блок
- блок завершается при получении }
- если блок начали с {, то второе открытие { не закрывает блок
- аналогично, блок закончится тогда, когда встретится ровно столько }, сколько {
- если данные закончились до }, то блок игнорируется

*/

BOOST_AUTO_TEST_CASE(BlockCreated_WhenCommandQuantityEquals_N)
{
	int blockSize = 3;
	CommandCollector cmdClctr(blockSize);

	cmdClctr.captureCommand("cmd1");
	BOOST_CHECK_EQUAL(0, cmdClctr.getBlocksQuantity());

	cmdClctr.captureCommand("cmd2");
	BOOST_CHECK_EQUAL(0, cmdClctr.getBlocksQuantity());

	cmdClctr.captureCommand(EOF);

	BOOST_CHECK_EQUAL(1, cmdClctr.getBlocksQuantity());
}

BOOST_AUTO_TEST_SUITE_END()