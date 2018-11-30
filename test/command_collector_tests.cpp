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
		std::copy(receivedBulk.cbegin(), receivedBulk.cend(), std::back_inserter(actualBulk));
	}	
};

class TestHelper
{
	static bool wasExpectedBulkCleared;

	static bool wasCommandSequenceCleared;
	
	public:

		static Bulk expectedBulk;

		static Bulk commandSequence;

		static void mustActualBulkBeEmpty(bool value, const Bulk &actualBulk)
		{
			BOOST_CHECK(value == actualBulk.empty());
		}

		static void compareExpectedAndActualBulks(const Bulk &actualBulk)
		{
			BOOST_CHECK( 
				true == std::equal(expectedBulk.begin(), expectedBulk.end(),
				    			   actualBulk.begin(), actualBulk.end())
			);
		}


		static void prepareCommandSequenceToBeSent() { wasCommandSequenceCleared = false; }

		template<typename T, typename... Args>
		static void prepareCommandSequenceToBeSent(T command, Args... args)
		{
			if(!wasCommandSequenceCleared)
			{
				commandSequence.clear();
				wasCommandSequenceCleared = true;
			}

			commandSequence.push_back(command);
			prepareCommandSequenceToBeSent(args...);
		}

		static void prepareExpectedCommandsToBeCapturedIntoBulk() { wasExpectedBulkCleared = false; };

		template<typename T, typename... Args>
		static void prepareExpectedCommandsToBeCapturedIntoBulk(T command, Args... args)
		{
			if(!wasExpectedBulkCleared) 
			{
				expectedBulk.clear();
				wasExpectedBulkCleared = true;
			}

			expectedBulk.push_back(command);
			prepareExpectedCommandsToBeCapturedIntoBulk(args...);
		}

		static void performCommandCaptureBy(CommandCollector &commandCollector)
		{
			for(auto cmd : commandSequence)
			{
				commandCollector.captureCommand(cmd);
			}
		}
};

Bulk TestHelper::expectedBulk;

Bulk TestHelper::commandSequence;

bool TestHelper::wasExpectedBulkCleared = true;

bool TestHelper::wasCommandSequenceCleared = true;

BOOST_AUTO_TEST_SUITE(command_collector)

/*
тесты:
+ блок завершается при достижении N
? блок завершается при EOF сигнале
- если получен {, то N игнорируется, данные собираюся до }
- предыдущий блок завершается при получении  первого { и поступающие данные складываются в новый блок
- блок завершается при получении }
- если блок начали с {, то второе открытие { не закрывает блок
- аналогично, блок закончится тогда, когда встретится ровно столько }, сколько {
- если данные закончились до }, то блок игнорируется

*/

BOOST_AUTO_TEST_CASE(BlockCreated_WhenCommandQuantityEquals_N)
{
	int N = 3;
	CommandCollector commandCollector(N);
	TestListener tl(&commandCollector);

	TestHelper::prepareCommandSequenceToBeSent("cmd1", "cmd2", "cmd3");
	TestHelper::prepareExpectedCommandsToBeCapturedIntoBulk("cmd1", "cmd2", "cmd3");

	TestHelper::performCommandCaptureBy(commandCollector);	

	TestHelper::mustActualBulkBeEmpty(false, tl.actualBulk);
	TestHelper::compareExpectedAndActualBulks(tl.actualBulk);
}

BOOST_AUTO_TEST_CASE(N_commandsCaptured_N_plus_one_was_ignored)
{
	int N = 3;
	CommandCollector commandCollector(N);
	TestListener tl(&commandCollector);

	TestHelper::prepareCommandSequenceToBeSent("cmd1", "cmd2", "cmd3", "cmd4");
	TestHelper::prepareExpectedCommandsToBeCapturedIntoBulk("cmd1", "cmd2", "cmd3");

	TestHelper::performCommandCaptureBy(commandCollector);

	TestHelper::mustActualBulkBeEmpty(false, tl.actualBulk);
	TestHelper::compareExpectedAndActualBulks(tl.actualBulk);
}

BOOST_AUTO_TEST_CASE(BlockNotCreated_CommandQuantityLessThan_N)
{
	int N = 3;
	CommandCollector cmdClctr(N);
	TestListener tl(&cmdClctr);

	cmdClctr.captureCommand("cmd1");
	cmdClctr.captureCommand("cmd2");
	
	BOOST_CHECK(true == tl.actualBulk.empty());
}

BOOST_AUTO_TEST_CASE(CommandsInsideCurlyBraces_N_limitIgnored)
{
	int N = 3;

	CommandCollector commandCollector(N);
	TestListener tl(&commandCollector);

	TestHelper::prepareCommandSequenceToBeSent(
		"{", "cmd1", "cmd2", "cmd3", "cmd4", "cmd5", "}"
	);
	TestHelper::prepareExpectedCommandsToBeCapturedIntoBulk(
		"cmd1", "cmd2", "cmd3", "cmd4", "cmd5"
	);

	TestHelper::performCommandCaptureBy(commandCollector);

	TestHelper::mustActualBulkBeEmpty(false, tl.actualBulk);
	TestHelper::compareExpectedAndActualBulks(tl.actualBulk);
}

BOOST_AUTO_TEST_SUITE_END()