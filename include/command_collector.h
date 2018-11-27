#include <string>
#include <vector>

#include "aliases.h"
#include "ibulk_updater.h"

class CommandCollector
{
	int commandBlockSize;
	Bulk currentBulk;
	std::vector<iBulkUpdater *> listeners;

public:
	CommandCollector(int bs) : commandBlockSize(bs) { currentBulk.reserve(100); };
   ~CommandCollector() = default;	

	void captureCommand(std::string command);

	int getBlocksQuantity(void);

	void subscribe(iBulkUpdater *listener);
	void notify(void);
};