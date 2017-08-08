#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "iforest/IsolationForest.hpp"
#include "iforest/utility.hpp"


std::vector<double> str_to_double_vector(std::vector<std::string> vec)
{
	std::vector<double> dub_vector(vec.size() - 1);

	for (int i=1;i<vec.size();i++)
	{
		dub_vector[i - 1] = std::stod(vec.at(i));
		// printf("%0.15f\n", dub_std::vector[i]);
	}

	return dub_vector;
}


int dataframe_size(dataframe df)
{
	return 58000;
	//return NUM_DATAPOINTS;
}


int randint(int start, int end)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(start, end);

	return distr(eng);
}


std::vector<std::string> split(std::string str, char delim)
{
	std::vector<std::string> vec;
	std::stringstream ss(str);

	std::string tok;

	while(getline(ss, tok, delim))
		vec.push_back(tok);

	return vec;
}


bool sort_by_second(const std::pair<int, float> &a, const std::pair<int, float> &b)
{
	return (a.second < b.second);
}


ftplen sort_vector_pair(ftplen vec)
{
	sort(vec.begin(), vec.end(), sort_by_second);

	return vec;
}


float vector_avg(std::vector<double> vec)
{
	double sum = 0.0; 
	
	for (int i=0; i<vec.size(); i++)
		sum += vec.at(i);

	return sum / vec.size();
}


float max_float(float a, float b)
{
	if (a > b)
		return a;
	else if (a < b)
		return b;
	else
		return a;
}


/************************************************/
/************** UNDER CONSTRUCTION **************/
/************************************************/
doubleframe* build_doubleframe(std::string input_name)
{
	ntstringframe* csv = read_csv((char *)input_name.c_str(), true, false, false);
	doubleframe* dt = conv_frame(double, ntstring, csv);

	return dt;
}


IsolationForest build_Isolation_forest(doubleframe* df)
{
	// IsolationForest iff(ntree,dt,nsample,maxheight,stopheight,rsample);
	IsolationForest iff(100, df, 2048, 0, false, true);
	return iff;
}


double* vector_to_dub_ptr(std::vector<double> vec)
{
	double *ptr_vec = vec.data();
	return ptr_vec;
}


float get_path_length(std::vector<double> inst, IsolationForest &iff)
{
	double *query = vector_to_dub_ptr(inst);
	std::vector<double> plens = iff.pathLength(query);
	
	return vector_avg(plens);
}

