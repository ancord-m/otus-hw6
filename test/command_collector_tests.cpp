#define BOOST_TEST_MODULE command_collector

#include <boost/test/unit_test.hpp>
#include "command_collector.h"
#include "ibulk_updater.h"
#include <algorithm>
#include <iostream>

class TestListener : public iBulkUpdater {
public:
	Bulk actualBulk;
	

	TestListener(CommandCollector *cc)
	{
		cc->subscribe(this);
	}

	void update(const Bulk& receivedBulk) override
	{
		actualBulk = receivedBulk;
	}	
};

class TestHelper
{
	bool wasExpectedBulkCleared;
	bool wasCommandSequenceCleared;
	
	public:
		TestHelper()
		{
			wasExpectedBulkCleared    = true;
			wasCommandSequenceCleared = true;			
		}

	   ~TestHelper() = default;	

		Bulk expectedBulk;
		Bulk commandSequence;

		void mustActualBulkBeEmpty(bool value, const Bulk& actualBulk)
		{
			BOOST_CHECK(value == actualBulk.isEmpty());
		}

		void compareExpectedAndActualBulks(const Bulk& actualBulk)
		{
			BOOST_CHECK(expectedBulk.get() == actualBulk.get());
		}

		void prepareCommandSequenceToBeSent() { wasCommandSequenceCleared = false; }

		template<typename T, typename... Args>
		void prepareCommandSequenceToBeSent(T command, Args... args)
		{
			if(!wasCommandSequenceCleared)
			{
				commandSequence.clear();
				wasCommandSequenceCleared = true;
			}

			commandSequence.push(command);
			prepareCommandSequenceToBeSent(args...);
		}

		void prepareExpectedCommandsToBeCapturedIntoBulk() { wasExpectedBulkCleared = false; };

		template<typename T, typename... Args>
		void prepareExpectedCommandsToBeCapturedIntoBulk(T command, Args... args)
		{
			if(!wasExpectedBulkCleared) 
			{
				expectedBulk.clear();
				wasExpectedBulkCleared = true;
			}

			expectedBulk.push(command);
			prepareExpectedCommandsToBeCapturedIntoBulk(args...);
		}

		void performCommandCaptureBy(CommandCollector& commandCollector)
		{
			for(auto cmd : commandSequence.get())
			{
				commandCollector.captureCommandAndPerformAnalysis(cmd);
			}
		}
};

BOOST_FIXTURE_TEST_SUITE(command_collector, TestHelper)

BOOST_AUTO_TEST_CASE(BlockCreated_WhenCommandQuantityEquals_N)
{
	int N = 3;
	CommandCollector commandCollector(N);
	TestListener tl(&commandCollector);

	prepareCommandSequenceToBeSent("cmd1", "cmd2", "cmd3");
	prepareExpectedCommandsToBeCapturedIntoBulk("cmd1", "cmd2", "cmd3");

	performCommandCaptureBy(commandCollector);	

	mustActualBulkBeEmpty(false, tl.actualBulk);
	compareExpectedAndActualBulks(tl.actualBulk);
}

BOOST_AUTO_TEST_CASE(N_commandsCaptured_N_plus_one_was_ignored)
{
	int N = 3;
	CommandCollector commandCollector(N);
	TestListener tl(&commandCollector);

	prepareCommandSequenceToBeSent("cmd1", "cmd2", "cmd3", "cmd4");
	prepareExpectedCommandsToBeCapturedIntoBulk("cmd1", "cmd2", "cmd3");

	performCommandCaptureBy(commandCollector);

	mustActualBulkBeEmpty(false, tl.actualBulk);
	compareExpectedAndActualBulks(tl.actualBulk);
}

BOOST_AUTO_TEST_CASE(BlockNotCreated_CommandQuantityLessThan_N)
{
	int N = 3;
	CommandCollector commandCollector(N);
	TestListener tl(&commandCollector);

	prepareCommandSequenceToBeSent("cmd1", "cmd2");

	performCommandCaptureBy(commandCollector);
	
	mustActualBulkBeEmpty(true, tl.actualBulk);
}

BOOST_AUTO_TEST_CASE(CommandsInsideCurlyBraces_N_limitIgnored)
{
	int N = 3;
	CommandCollector commandCollector(N);
	TestListener tl(&commandCollector);

	prepareCommandSequenceToBeSent(
		"{", "cmd1", "cmd2", "cmd3", "cmd4", "cmd5", "}"
	);
	prepareExpectedCommandsToBeCapturedIntoBulk(
		"cmd1", "cmd2", "cmd3", "cmd4", "cmd5"
	);

	performCommandCaptureBy(commandCollector);

	mustActualBulkBeEmpty(false, tl.actualBulk);
	compareExpectedAndActualBulks(tl.actualBulk);
}

BOOST_AUTO_TEST_CASE(CommandsSurroundedBySeveralPairsOfCurlyBraces_OnlyFirstAndLastMatters)
{
	int N = 3;
	CommandCollector commandCollector(N);
	TestListener tl(&commandCollector);

	prepareCommandSequenceToBeSent(
		"{", "cmd1", "cmd2", "{", "cmd3", "{", "}", "cmd4", "cmd5", "}", "}"
	);
	prepareExpectedCommandsToBeCapturedIntoBulk(
		"cmd1", "cmd2", "cmd3", "cmd4", "cmd5"
	);

	performCommandCaptureBy(commandCollector);

	mustActualBulkBeEmpty(false, tl.actualBulk);
	compareExpectedAndActualBulks(tl.actualBulk);
}


BOOST_AUTO_TEST_CASE(CommandsFinishedBeforeLastClosingCurlyBrace_BulkIsEmpty)
{
	int N = 3;
	CommandCollector commandCollector(N);
	TestListener tl(&commandCollector);

	prepareCommandSequenceToBeSent(
		"{", "cmd1", "cmd2", "{", "cmd3", "{", "}", "cmd4", "cmd5", "}"
	);

	performCommandCaptureBy(commandCollector);

	mustActualBulkBeEmpty(true, tl.actualBulk);
	compareExpectedAndActualBulks(tl.actualBulk);
}

BOOST_AUTO_TEST_CASE(CommandsFinishedBeforeClosingCurlyBrace_BulkIsEmpty)
{
	int N = 3;
	CommandCollector commandCollector(N);
	TestListener tl(&commandCollector);

	prepareCommandSequenceToBeSent(
		"{", "cmd1", "cmd2", "cmd3", "cmd4", "cmd5"
	);

	performCommandCaptureBy(commandCollector);

	mustActualBulkBeEmpty(true, tl.actualBulk);
	compareExpectedAndActualBulks(tl.actualBulk);
}

BOOST_AUTO_TEST_CASE(PreviousBulkWasFinishedForcibly_AtFirstOpeningCurlyBrace)
{
	int N = 5;
	CommandCollector commandCollector(N);
	TestListener tl(&commandCollector);

	prepareCommandSequenceToBeSent(
		"cmd1", "cmd2", "\n", "{", "cmd4", "cmd5"
	);

	prepareExpectedCommandsToBeCapturedIntoBulk(
		"cmd1", "cmd2", "\n"
	);

	performCommandCaptureBy(commandCollector);

	mustActualBulkBeEmpty(false, tl.actualBulk);
	compareExpectedAndActualBulks(tl.actualBulk);
}

BOOST_AUTO_TEST_SUITE_END()