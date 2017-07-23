#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include<bits/stdc++.h>
#include <random>

using namespace std;

typedef vector<pair<string, vector<double> > > dataframe;
typedef vector<pair<int, float> > ftplen;
const int NUM_DATAPOINTS = 58000;
const int NUM_FEATS = 9;


/*************** PRINT FUNCTIONS ***************/
template <typename T>
void print_vector(vector<T> vec)
{
	for (int i=0; i<vec.size(); i++)
		cout << vec.at(i) << endl;
}


void print_dataframe(dataframe df)
{
	for (int i=0; i<df.size(); i++)
	{
		vector<double> feats = df[i].second;
		cout << df[i].first;
		
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


/*************** UTILITY FUNCTIONS ***************/
vector<double> str_to_double_vector(vector<string> vec)
{
	vector<double> dub_vector(vec.size() - 1);

	for (int i=1;i<vec.size();i++)
	{
		dub_vector[i - 1] = stod(vec.at(i));
		// printf("%0.15f\n", dub_vector[i]);
	}

	return dub_vector;
}


int randint(int start, int end)
{
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr(start, end);

	return distr(eng);
}


vector<string> split(string str, char delim)
{
	vector<string> vec;
	stringstream ss(str);

	string tok;

	while(getline(ss, tok, delim))
		vec.push_back(tok);

	return vec;
}


bool sort_by_second(const pair<int, float> &a, const pair<int, float> &b)
{
	return (a.second < b.second);
}


ftplen sort_vector_pair(ftplen vec)
{
	sort(vec.begin(), vec.end(), sort_by_second);

	return vec;
}


float get_path_length(vector<double> query)
{
	return randint(10, 200) / 29.3;
}


/*************** HELPER FUNCTIONS ***************/
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
	
	 	query_feat_lens.push_back(make_pair(i, get_path_length(updated_query)));
	 }
	
	// query_feat_lens = sort_vector_pair(query_feat_lens);
	
	return query_feat_lens;
}


/*************** MAIN FUNCTIONS ***************/
int main()
{
	dataframe data = get_data_set();
	// print_dataframe(data);

	vector<double> query = {0.961074390045098,-0.0125779430326821,2.65657571737471,
				-0.0344912414815925,1.17497576719637,-0.00739065642095547,
				0.908191661935069,-0.0412993573002382,-0.543937066541179};

	ftplen myvec = build_feat_pathlen(query, data);
	print_vector_pair(myvec);

	myvec = sort_vector_pair(myvec);
	print_vector_pair(myvec);

	vector<int> feats = ordered_feats(myvec);
	printf("\n");

	print_vector(feats);
	return 0;
}
