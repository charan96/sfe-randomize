#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "randomize-method.h"
#include "build-mfp.h"
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


std::vector<double> switch_feature(std::vector<int> feat_num, dataframe data, std::vector<double> query)
{
	int rand_dataidx = randint(0, get_lines_in_file(INFILE) - 2);

	for (int k: feat_num)
		query.at(k) = data.at(rand_dataidx).second.at(k);               //FIXME: DANGEROUS; change k - 1 to k

	return query;
}


std::pair<int, std::vector<int> > build_avg_feat_lens(std::vector<double> query, dataframe data, doubleframe *df, IsolationForest *iff)
{
	double base_pathlen = double_vector_avg(iff->pathLength(vector_to_dub_ptr(query)));
	std::vector<int> omitted_feats;

	while (omitted_feats.size() < query.size())
	{
		std::map<int, double> avg_switched_feature_query_lengths;

		for (int i=0; i<query.size(); i++)
		{
			// if (!omitted_feats.contains(i))
			if (std::find(omitted_feats.begin(), omitted_feats.end(), i) == omitted_feats.end())
				avg_switched_feature_query_lengths[i] = double(0);
		}

		for (int i=0; i<query.size(); i++)
		{
			if (std::find(omitted_feats.begin(), omitted_feats.end(), i) == omitted_feats.end())
			{
				for (int reps=0; reps<NUM_REPS; reps++)
				{
					std::vector<int> switch_features_vector = omitted_feats;
					switch_features_vector.push_back(i);
					
					std::vector<double> updated_query = switch_feature(switch_features_vector, data, query);
					avg_switched_feature_query_lengths[i] += (base_pathlen - double_vector_avg(iff->pathLength(vector_to_dub_ptr(updated_query))));
				}

				avg_switched_feature_query_lengths[i] /= NUM_REPS;
			}
		}

		ftplen myvec = map_to_vector_pair(avg_switched_feature_query_lengths);
		std::vector<int> ord_feats = ordered_feats(myvec);
		omitted_feats.push_back(ord_feats.front());

		if (compute_mfp_while_building_expls(query, omitted_feats, data, df, iff))
			break;
		printf("\n\n");
	}

	int mfp = omitted_feats.size();
	omitted_feats = fill_up_remaining_feats(omitted_feats, query.size());

	std::pair<int, std::vector<int> > mfp_ord_feats_pair = std::make_pair(mfp, omitted_feats);

	return mfp_ord_feats_pair;
}


std::vector<std::vector<int> > get_ranked_features(std::string qfile, dataframe nominal_df, doubleframe *df)
{
	dataframe qdata = get_data_set(qfile);
	std::vector<std::vector<int> > feats;
	
	IsolationForest iff = build_Isolation_forest(df);
	std::vector<std::string> refidx;
	std::vector<double> avg_mfp;

	std::ofstream mfp_file(MFP_FILE.c_str());
	mfp_file << "idx, MFP" << std::endl;

	for (int i=0; i<qdata.size(); i++)
	{
		std::vector<double> qpoint = qdata.at(i).second;
		
		std::pair<int, std::vector<int> > mfp_ord_feats_pair = build_avg_feat_lens(qpoint, nominal_df, df, &iff);
	
		// remove if statement for writing MFP for all datapoints to file
		if (qdata.at(i).first == "anomaly")
		{
			avg_mfp.push_back(mfp_ord_feats_pair.first);
			mfp_file << i << ", " << mfp_ord_feats_pair.first << std::endl;
		}

		feats.push_back(mfp_ord_feats_pair.second);

		std::cout << i + 1 << '/' << qdata.size() << ',' << iff.instanceScore(vector_to_dub_ptr(qpoint)) << std::endl;

		if (i==40)
			break;
	}

	std::cout << "Average MFP (Sequential): " << double_vector_avg(avg_mfp) << std::endl;

	mfp_file.close();
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

