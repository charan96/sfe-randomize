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


void print_explanations(std::vector<std::vector<int> > ranked_feats)
{
	std::cout << "id, ";

	for (int i=0; i<ranked_feats.at(0).size() - 1; i++)
		std::cout << "rank" << i << ", ";
	std::cout << "rank" << ranked_feats.at(0).size() - 1 << std::endl;

	for (int id=0; id<ranked_feats.size(); id++)
	{
		std::cout << id << ", ";

		for (int i=0; i<ranked_feats.at(id).size() - 1; i++)
			std::cout << ranked_feats.at(id).at(i) << ", ";

		std::cout << ranked_feats.at(id).at(ranked_feats.at(id).size() - 1) << std::endl;
	}

	return;
}

