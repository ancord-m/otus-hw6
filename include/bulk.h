#ifndef BULK_H
#define BULK_H

#include <vector>
#include <string>
#include <chrono>
#include <memory>

class Bulk
{
	public:
		Bulk()
		{
			time_stamp_updated = false;
			bulk.reserve(100);
		}

		decltype(auto) get(void)
		{
			return std::make_shared<std::vector<std::string>>(bulk);
		}

		void updateTimeStamp(void)
		{
			time_stamp_updated = true;
			created_at = std::chrono::system_clock::now();
		}

		bool wasTimeStampUpdated(void)
		{
			return time_stamp_updated;
		}

		void clear(void)
		{
			time_stamp_updated = false;
			bulk.clear();
		}

	private:
		std::chrono::system_clock::time_point created_at;
		std::vector<std::string> bulk;
		bool time_stamp_updated;
};

#endif /* bulk.h */