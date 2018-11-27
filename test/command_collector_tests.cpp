#define BOOST_TEST_MODULE command_collector

#include <boost/test/unit_test.hpp>
#include "command_collector.h"
#include "ibulk_updater.h"
#include <algorithm>
#include <iostream>

class TestListener : public iBulkUpdater {
public:
	Bulk actualBulk;

	TestListener(CommandCollector *cc) {
		cc->subscribe(this);
	}

	void update(const Bulk &receivedBulk) override {
		actualBulk.clear();
		actualBulk.reserve(receivedBulk.size());
		std::copy(receivedBulk.cbegin(), receivedBulk.cend(), actualBulk.begin());
	}	
};


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
	CommandCollector cmdClctr(3);
	TestListener tl(&cmdClctr);

	cmdClctr.captureCommand("cmd1");
	cmdClctr.captureCommand("cmd2");
	cmdClctr.captureCommand("cmd3");

	BOOST_CHECK(false == tl.actualBulk.empty());

	for(auto i : tl.actualBulk) {
		std::cout << "e" << std::endl;
	}

}

BOOST_AUTO_TEST_SUITE_END()