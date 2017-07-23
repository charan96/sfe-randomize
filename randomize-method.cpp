#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "randomize-method.h"


dataframe get_data_set()
{
	dataframe data(NUM_DATAPOINTS, make_pair("no_truth", vector<double>(NUM_FEATS)));
	
	ifstream infile("shuttle.preproc.csv");
	string line, firstline;
	int ctr = 0;

	getline(infile, firstline);

	while(getline(infile, line))
	{
		vector<string> split_line = split(line, ',');
		
		data[ctr].first = split_line[0];
		data[ctr].second = str_to_double_vector(split_line);

		ctr++;
	}

	return data;
}


vector<double> switch_feature(int feat_num, dataframe data, vector<double> query)
{
	int rand_dataidx = randint(0, data.size());
	
	query.at(feat_num) = data.at(rand_dataidx).second.at(feat_num);
	return query;
}


vector<int> ordered_feats(ftplen vec)
{
	vec = sort_vector_pair(vec);
	vector<int> ord_feats;

	for (int i=0; i<vec.size(); i++)
		ord_feats.push_back(vec.at(i).first);

	return ord_feats;
}


ftplen build_feat_pathlen(vector<double> query, dataframe data)
{
	 float base_pathlen = get_path_length(query);
	 ftplen query_feat_lens;
	
	 for (int i=0; i<query.size(); i++)
	 {
	 	vector<double> updated_query = switch_feature(i, data, query);

		float updated_pathlen = max(float(0), get_path_length(updated_query) - base_pathlen);
	 	query_feat_lens.push_back(make_pair(i, updated_pathlen));
	 }
	
	return query_feat_lens;
}


