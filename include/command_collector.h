#include <string>
#include <vector>

#include "aliases.h"
#include "ibulk_updater.h"

class CommandCollector
{
	int commandBlockSize;
	
	std::vector<iBulkUpdater *> listeners;
	int braceCounter;
	bool formingCurrentBulkDynamicly;

	bool isThisOpenningCurlyBrace(String &command);
	bool isThisClosingCurlyBrace(String &command);
	void storeCommandIntoCurrentBulk(String command);
	void openCurlyBrace(void);
	void closeCurlyBrace(void);
	void bulkFormedDynamicly(bool);
	bool doesBulkFormedDynamicly(void);
	void notify_IfAllCurlyBracesAreClosed(void);
	void notify_IfCommandBlockSizeIsReached(void);


public:
	CommandCollector(int bs) :
		commandBlockSize(bs),
		braceCounter(0),
		formingCurrentBulkDynamicly(false)
	{ 
		currentBulk.reserve(100); 
	};

   ~CommandCollector() = default;	

	void captureCommand(std::string command);
	void subscribe(iBulkUpdater *listener);
	void notify(void);
	Bulk currentBulk;
};