#include <string>

class CommandCollector
{
	int commandBlockSize;
public:
	CommandCollector(int bs) : commandBlockSize(bs) {};
	void captureCommand(std::string command);
	int getBlocksQuantity(void);
};