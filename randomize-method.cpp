#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "randomize-method.h"


dataframe get_data_set()
{
	dataframe data(NUM_DATAPOINTS, make_pair("no_truth", std::vector<double>(NUM_FEATS)));
	std::ifstream infile(input_datafile.c_str());
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
	int rand_dataidx = randint(0, dataframe_size(data));
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


ftplen build_feature_pathlen(std::vector<double> query, dataframe data, doubleframe *df)
{	
	 IsolationForest iff = build_Isolation_forest(df);

	 float base_pathlen = get_path_length(query, iff);
	 std::cout << "base len: " << base_pathlen << std::endl;
	 ftplen query_feat_lens;
	
	 for (int i=0; i<query.size(); i++)
	 {
	 	std::vector<double> updated_query = switch_feature(i, data, query);

		// float updated_pathlen = get_path_length(updated_query, iff);
		float updated_pathlen = max_float(float(0), get_path_length(updated_query, iff));
		printf("feature %d pathlen: %f\n", i, updated_pathlen);
	 	query_feat_lens.push_back(std::make_pair(i, updated_pathlen));
	 }
	
	return query_feat_lens;
}


void build_explanation_file()
{
	return;
}
