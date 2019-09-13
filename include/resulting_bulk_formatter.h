#ifndef RESULTING_BULK_FORMATTER_H
#define RESULTING_BULK_FORMATTER_H

#include "bulk.h"

class ResultingBulkFormatter
{
	public:
		ResultingBulkFormatter() = default;
	   ~ResultingBulkFormatter() = default;

		std::string generateResultingBulkString(const Bulk& bulk)
		{
			std::string result = "bulk: "; 

			for(auto b_it = bulk.cbegin_iterator(); b_it != bulk.cend_iterator(); ++b_it)
			{
				if(b_it != bulk.get().cbegin())
				{
					result += ", ";
				}

				result += *b_it;		
			}

			return result;
		}
};

#endif