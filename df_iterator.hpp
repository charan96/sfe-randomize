#include "constants.h"

class df_iter
{
	dataframe df;
	int index;

	public:
		df_iter(dataframe dframe)
		{
			df = dframe;
		}

		void first()
		{
			index = 0;
		}

		void next()
		{
			index++;
		}

		bool isDone()
		{
			return index == df.size();
		}
	
		std::string cur_item_label()
		{
			return df[index].first;
		}

		std::vector<double> cur_item_vec()
		{
			return df[index].second;
		}
};

