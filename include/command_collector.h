#include <string>
#include <vector>

#include "aliases.h"

class CommandCollector
{
	int commandBlockSize;
	Bulk currentBulk;

public:
	CommandCollector(int bs) : commandBlockSize(bs) { currentBulk.reserve(100); };
   ~CommandCollector() = default;	

	void captureCommand(std::string command);
	void captureCommand(int command);
	int getBlocksQuantity(void);
};