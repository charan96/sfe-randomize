#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <random>

using namespace std;

typedef vector<pair<string, vector<double> > > dataframe;
const int NUM_DATAPOINTS = 58000;
const int NUM_FEATS = 9;

template <typename T>
void print_vector(vector<T> vec)
{
	for (int i=0; i<vec.size(); i++)
		cout << vec.at(i) << endl;
}


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


vector<string> split(string str, char delim)
{
	vector<string> vec;
	stringstream ss(str);

	string tok;

	while(getline(ss, tok, delim))
		vec.push_back(tok);

	return vec;
}


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


int get_randint(int start, int end)
{
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr(start, end);

	return distr(eng);
}


vector<double> switch_feature(int feat_num, dataframe data, vector<double> query)
{
	int rand_dataidx = get_randint(0, data.size());
	
	query.at(feat_num) = data.at(rand_dataidx).second.at(feat_num);
	return query;
}


void get_ord_feats(vector<double> query)
{
	return;
}


int main()
{
	dataframe data = get_data_set();
	// print_dataframe(data);
	
	return 0;
}
