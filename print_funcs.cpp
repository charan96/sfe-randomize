#include "constants.h"
#include "print_funcs.h"


void print_dataframe(dataframe df)
{
	for (int i=0; i<df.size(); i++)
	{
		vector<double> feats = df[i].second;
		cout << df[i].first;
		
		for (int j=0; j<df[i].second.size(); j++)
			printf(",%0.15f", df[i].second.at(j));

		printf("\n");
	}
}


void print_vector_pair(ftplen vec)
{
	printf("idx\tvec.first\tvec.sec\n");

	for (int i=0; i<vec.size(); i++)
		printf("%d\t%d\t%f\n", i, vec.at(i).first, vec.at(i).second);
}

