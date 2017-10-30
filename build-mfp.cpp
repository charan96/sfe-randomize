#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "randomize-method.h"
#include "build-mfp.h"


int compute_mfp(std::vector<double> query, std::vector<int> ordered_feats, dataframe data, doubleframe *df, IsolationForest *iff)
{
	double nominal_depth = avg_depth_of_all_datapoints(iff->pathLength(df));	
	int ctr = 0;

	printf("ord feats: \n");
	print_vector(ordered_feats);

	for (int i=0; i<ordered_feats.size(); i++)
	{
		double qdepth = get_path_length(query, *iff);
		std::vector<double> updated_qdepths;

		for (int j=0; j<30; j++)
		{
			std::vector<double> updated_query = switch_feature(subvector(ordered_feats, i + 1), data, query);
			updated_qdepths.push_back(get_path_length(updated_query, *iff));
		}

		
		// for (int n=0; n<query.size(); n++)
		//	printf("%f, %f\n", query.at(n), updated_query.at(n));
		
		//if (updated_qdepth > (nominal_depth - 1))
		//	break;
		
		printf("qdepth: %f\tup_qdepth: %f\t nom_depth: %f\n\n", qdepth, vector_avg(updated_qdepths), nominal_depth);
		ctr++;
	}

	return ctr;
}
