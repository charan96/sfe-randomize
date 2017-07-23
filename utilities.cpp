#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"


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


/************************************************/
/************** UNDER CONSTRUCTION **************/
/************************************************/
float get_path_length(vector<double> query)
{
	return randint(10, 200) / 29.3;
}

