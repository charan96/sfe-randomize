#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "randomize-method.h"


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
	int rand_dataidx = randint(0, get_lines_in_file(INFILE) - 1);
	query.at(feat_num) = data.at(rand_dataidx).second.at(feat_num);
	
	return query;
}


std::map<int, float> build_avg_feat_lens(std::vector<double> query, dataframe data, doubleframe *df)
{
	std::map<int, float> avg_switched_feature_query_lengths;
	IsolationForest iff = build_Isolation_forest(df);
	float base_pathlen = get_path_length(query, iff);

	// initialize to 0
	for (int i=0; i<query.size(); i++)
		avg_switched_feature_query_lengths[i] = float(0);

	for (int i=0; i<NUM_REPS; i++)
	{
		// if (avg_switched_feature_query_lengths.count(i) == 1)
		//	avg_switched_feature_query_lengths[i] = 0;

		std::map<int, float> switched_feature_query_lengths;
		for (int k=0; k<query.size(); k++)
		{
			std::vector<double> updated_query = switch_feature(k, data, query);

			float updated_pathlen = max_float(float(-5000), base_pathlen - get_path_length(updated_query, iff));
			switched_feature_query_lengths[k] = updated_pathlen;
		}
		
		for (int j=0; j<query.size(); j++)
			avg_switched_feature_query_lengths[j] += switched_feature_query_lengths[j];
	}

	for (int i=0; i<query.size(); i++)
		avg_switched_feature_query_lengths[i] /= NUM_REPS;

	return avg_switched_feature_query_lengths;
}


//std::vector<std::vector<int> > ranked_features()
//{
//}
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

/*
void build_explanation_file(dataframe data)
{
	std::ofstream outfile(OUTFILE.c_str());

	// header
	outfile << "id, ";

	for (int i=0; i<ord_feats.size() - 1; i++)
		outfile << "rank" << i << ", ";
	outfile << "rank" << ord_feats.size() << std::endl;


	for (int id=0; id<data.size(); id++)
	{
		if ((data.at(i).first).compare("anomaly") == 0)
		{
			build_avg_feat_lens(query, data, df)

	return;
} */
