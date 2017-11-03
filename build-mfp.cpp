#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "randomize-method.h"
#include "build-mfp.h"


int compute_mfp_from_expl_file(std::vector<double> query, std::vector<int> ordered_feats, dataframe data, doubleframe *df, IsolationForest *iff)
{
	double nominal_depth = avg_depth_of_all_datapoints(iff->pathLength(df));	
	int ctr = 1;

	for (int i=0; i<ordered_feats.size(); i++)
	{
		std::vector<double> updated_qdepths;

		for (int j=0; j<MFP_REPS; j++)
		{
			std::vector<double> updated_query = switch_feature(subvector(ordered_feats, i + 1), data, query);
			updated_qdepths.push_back(double_vector_avg(iff->pathLength(vector_to_dub_ptr(updated_query))));
		}

		// printf("qscore: %f\tupd_qscore: %f\t nom_score: %f\n\n", double_vector_avg(iff->pathLength(vector_to_dub_ptr(query))), double_vector_avg(updated_qdepths), nominal_depth);

		if (double_vector_avg(updated_qdepths) > ((1.0 - TOLERANCE) * nominal_depth))		// 10% tolerance 
			break;
		ctr++;
	}

	return ctr;
}


int compute_mfp_while_building_expls(std::vector<double> query, std::vector<int> ordered_feats, dataframe data, doubleframe *df, IsolationForest *iff)
{
	double nominal_depth = avg_depth_of_all_datapoints(iff->pathLength(df));
	int ctr = 1;

	for (int i=0; i<ordered_feats.size(); i++)
	{
		std::vector<double> updated_qdepths;

		for (int j=0; j<MFP_REPS; j++)
		{
			std::vector<double> updated_query = switch_feature(subvector(ordered_feats, i + 1), data, query);
			updated_qdepths.push_back(double_vector_avg(iff->pathLength(vector_to_dub_ptr(updated_query))));
		}

		if (double_vector_avg(updated_qdepths) > ((1.0 - TOLERANCE) * nominal_depth))                // tolerance given as 0.1 for 10% tolerance level; adjust in constants.h
			break;
		ctr++;
	}

	return ctr;
}