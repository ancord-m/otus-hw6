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

		const std::vector<std::string>& get(void) const
		{
			return bulk;
		}

		std::vector<std::string>::const_iterator cbegin_iterator() const
		{
			return bulk.cbegin();
		}

		std::vector<std::string>::const_iterator cend_iterator() const
		{
			return bulk.end();
		}
	

		void push(std::string cmd)
		{
			bulk.push_back(cmd);
		}

		bool isEmpty(void) const
		{
			return bulk.empty();
		}

		void updateTimeStamp(void)
		{
			time_stamp_updated = true;
			created_at = std::chrono::system_clock::now();
		}

		const std::chrono::system_clock::time_point getTimeStamp(void) const
		{
			return created_at;
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