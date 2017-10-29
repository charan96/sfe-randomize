#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "randomize-method.h"
#include <algorithm>


dataframe get_data_set(std::string input_file)
{
	dataframe data(get_lines_in_file(input_file) - 1, make_pair("no_truth", std::vector<double>(get_num_cols_in_file(INFILE) - 2)));
	std::ifstream infile(input_file.c_str());
	std::string line, firstline;
	int ctr = 0;

	getline(infile, firstline);

	while(getline(infile, line))
	{
		std::vector<std::string> split_line = split(line, ',');
		
		data[ctr].first = split_line[0];
		data[ctr].second = str_to_double_vector(split_line);

		ctr++;
	}

	return data;
}


std::vector<double> switch_feature(int feat_num, dataframe data, std::vector<double> query)
{
	int rand_dataidx = randint(0, get_lines_in_file(INFILE) - 2);
	query.at(feat_num) = data.at(rand_dataidx).second.at(feat_num);
	
	return query;
}


std::vector<int> build_avg_feat_lens(std::vector<double> query, dataframe data, doubleframe *df, IsolationForest *iff)
{
	std::map<int, float> hello;
	float base_pathlen = get_path_length(query, *iff);
	std::vector<int> omitted_feats;


	while (omitted_feats.size() < query.size())
	{
		std::map<int, float> avg_switched_feature_query_lengths;
		// initialize to 0
		for (int i=0; i<query.size(); i++)
		{
			// if (!omitted_feats.contains(i))
			if (std::find(omitted_feats.begin(), omitted_feats.end(), i) == omitted_feats.end())
				avg_switched_feature_query_lengths[i] = float(0);
		}


		for (int i=0; i<NUM_REPS; i++)
		{
			std::map<int, float> switched_feature_query_lengths;
			for (int k=0; k<query.size(); k++)
			{
				if (std::find(omitted_feats.begin(), omitted_feats.end(), k) == omitted_feats.end())
				{
					std::vector<double> updated_query = switch_feature(k, data, query);

					float updated_pathlen = max_float(float(0), base_pathlen - get_path_length(updated_query, *iff));
					switched_feature_query_lengths[k] = updated_pathlen;
				}
			}
			
			for (int j=0; j<query.size(); j++)
			{
				if (std::find(omitted_feats.begin(), omitted_feats.end(), j) == omitted_feats.end())
					avg_switched_feature_query_lengths[j] += switched_feature_query_lengths[j];
			}
		}

		for (int i=0; i<query.size(); i++)
		{
			if (std::find(omitted_feats.begin(), omitted_feats.end(), i) == omitted_feats.end())
				avg_switched_feature_query_lengths[i] /= NUM_REPS;
		}

		ftplen myvec = map_to_vector_pair(avg_switched_feature_query_lengths);
		std::vector<int> ord_feats = ordered_feats(myvec);
		omitted_feats.push_back(ord_feats.front());
	}
	
	// return avg_switched_feature_query_lengths;
	return omitted_feats;
}


std::vector<std::vector<int> > get_ranked_features(std::string qfile, dataframe nominal_df, doubleframe *df)
{
	dataframe qdata = get_data_set(qfile);
	std::vector<std::vector<int> > feats;
	
	IsolationForest iff = build_Isolation_forest(df);
	std::vector<std::string> refidx;
	int anomaly_ctr = 1;

	// std::ofstream ref_file(REF_FILE.c_str());
	// ref_file << "idx,anoIdx,ano_score" << std::endl;

	for (int i=0; i<qdata.size(); i++)
	{
		std::vector<double> qpoint = qdata.at(i).second;

		if (iff.instanceScore(vector_to_dub_ptr(qpoint)) > 0.4)		// assuming lower score means anomaly
		{
			refidx.push_back(std::to_string(anomaly_ctr) + "," + std::to_string(i + 1) + "," + std::to_string(iff.instanceScore(vector_to_dub_ptr(qpoint))));
			anomaly_ctr++;
		}
		
		/* std::map<int, float> qpoint_avg_lens_map = build_avg_feat_lens(qpoint, nominal_df, df, &iff);

		ftplen myvec = map_to_vector_pair(qpoint_avg_lens_map);
		std::vector<int> ord_feats = ordered_feats(myvec);

		feats.push_back(ord_feats);
		*/
		feats.push_back(build_avg_feat_lens(qpoint, nominal_df, df, &iff));
		// printf("%d\/%d, %f\n", i + 1, qdata.size(), iff.instanceScore(vector_to_dub_ptr(qpoint)));		// status printout
		std::cout << i+1 << '/' << qdata.size() << ',' << iff.instanceScore(vector_to_dub_ptr(qpoint)) << std::endl;
	}

	write_refidx_file(refidx);

	return feats;
}


void write_refidx_file(std::vector<std::string> refidx)
{
	std::ofstream ref_file(REF_FILE.c_str());

	ref_file << "idx,anoIdx,anoScore" << std::endl;		// anoIdx starts at 6; for example, anoIdx=6 is the 6th datapoint

	for (int i=0; i<refidx.size(); i++)
		ref_file << refidx[i] << std::endl;
	
	ref_file.close();

	return;
}


/* write the ranked features to the file */
void build_expl_file(std::vector<std::vector<int> > ranked_feats)
{
	std::ofstream outfile(OUTFILE.c_str());

	// header
	outfile << "id, ";
	
	for (int i=1; i<ranked_feats.at(0).size(); i++)
		outfile << "Rank" << i << ", ";
	outfile << "Rank" << ranked_feats.at(0).size() << std::endl;

	for (int id=0; id<ranked_feats.size(); id++)
	{
		outfile << id + 1 << ", ";

		for (int i=0; i<ranked_feats.at(id).size() - 1; i++)
			outfile << ranked_feats.at(id).at(i) + 1 << ", ";

		outfile << ranked_feats.at(id).at(ranked_feats.at(id).size() - 1) + 1 << std::endl;
	}

	outfile.close();
	std::cout << "finished writing to file" << std::endl;
	
	return;
}

