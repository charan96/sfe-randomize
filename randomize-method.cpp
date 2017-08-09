#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "randomize-method.h"


dataframe get_data_set()
{
	dataframe data(get_lines_in_file(INFILE) - 1, make_pair("no_truth", std::vector<double>(NUM_FEATS)));
	std::ifstream infile(INFILE.c_str());
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
	int rand_dataidx = randint(0, get_lines_in_file(INFILE) - 1);
	query.at(feat_num) = data.at(rand_dataidx).second.at(feat_num);
	
	return query;
}


std::vector<int> ordered_feats(ftplen vec)
{
	vec = sort_vector_pair(vec);
	std::vector<int> ord_feats;

	for (int i=0; i<vec.size(); i++)
		ord_feats.push_back(vec.at(i).first);

	return ord_feats;
}


std::map<int, float> build_feature_pathlen(std::vector<double> query, dataframe data, doubleframe *df)
{	
	 IsolationForest iff = build_Isolation_forest(df);

	 float base_pathlen = get_path_length(query, iff);
	 std::cout << "base len: " << base_pathlen << std::endl;
	 std::map<int, float> query_feat_lens;
	
	 for (int i=0; i<query.size(); i++)
	 {
	 	std::vector<double> updated_query = switch_feature(i, data, query);

		float updated_pathlen = max_float(float(0), base_pathlen - get_path_length(updated_query, iff));
		// float updated_pathlen = base_pathlen - get_path_length(updated_query, iff);
		query_feat_lens[i] = updated_pathlen;
	 }
	
	return query_feat_lens;
}


std::map<int, float> build_avg_feat_lens(std::vector<double> query, dataframe data, doubleframe *df)
{
	std::map<int, float> avg_feat_lens;

	for (int i=0; i<query.size(); i++)
		avg_feat_lens[i] = float(0);

	for (int i=0; i<NUM_REPS; i++)
	{
		// if (avg_feat_lens.count(i) == 1)
		//	avg_feat_lens[i] = 0;

		std::map<int, float> query_feat_lens = build_feature_pathlen(query, data, df);
		
		for (int j=0; j<query.size(); j++)
			avg_feat_lens[j] += query_feat_lens[j];
	}

	for (int i=0; i<query.size(); i++)
		avg_feat_lens[i] /= NUM_REPS;

	return avg_feat_lens;
}


void build_explanation_file(std::map<int, float> mymap)
{
	std::ofstream outfile(OUTFILE.c_str());

	ftplen myvec = map_to_vector_pair(mymap);
	std::vector<int> ord_feats = ordered_feats(myvec);

	// header
	outfile << "id, ";

	for (int i=0; i<ord_feats.size() - 1; i++)
		outfile << "rank" << i << ", ";

	outfile << "rank" << ord_feats.size() << std::endl;

	// temp var id
	int id = 0;

	// add for loop for going through queries
	outfile << id << ", ";

	for (int i=0; i<ord_feats.size() - 1; i++)
		outfile << ord_feats.at(i) << ", ";

	outfile << ord_feats.at(ord_feats.size() - 1) << std::endl;

	outfile.close();
	return;
}
