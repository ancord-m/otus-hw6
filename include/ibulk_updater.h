#ifndef IBULK_UPDATER_H
#define IBULK_UPDATER_H

#include "bulk.h"

class iBulkUpdater {
public:
	virtual void update(const Bulk&) = 0;
	virtual ~iBulkUpdater() {};
};

#endif