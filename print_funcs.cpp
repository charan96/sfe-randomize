#include "constants.h"
#include "print_funcs.h"


void print_dataframe(dataframe df)
{
	for (int i=0; i<df.size(); i++)
	{
		std::vector<double> feats = df[i].second;
		std::cout << df[i].first;
		
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


/* void print_explanations(std::vector<std::map<int, float> > mymap)
{
	ftplen myvec = map_to_vector_pair(mymap);
	std::vector<int> ord_feats = ordered_feats(myvec);

	std::cout << "id, ";

	for (int i=0; i<ord_feats.size() - 1; i++)
		std::cout << "rank" << i << ", ";
	std::cout << "rank" << ord_feats.size() << std::endl;
}
*/
