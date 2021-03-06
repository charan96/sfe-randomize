#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "iforest/IsolationForest.hpp"
#include "iforest/utility.hpp"


std::vector<double> str_to_double_vector(std::vector<std::string> vec)
{
	std::vector<double> dub_vector(vec.size() - COL_START);
	
	for (int i=COL_START;i<vec.size();i++)
	{
		dub_vector[i - COL_START] = std::stod(vec.at(i));
		// printf("%0.15f\n", dub_std::vector[i]);
	}

	return dub_vector;
}


int get_lines_in_file(std::string filename)
{
	std::ifstream infile(filename.c_str());
	std::string line;
	int ctr = 0;

	while(std::getline(infile, line))
		ctr++;

	return ctr;
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


/* sort descending */
bool sort_by_second(const std::pair<int, double> &a, const std::pair<int, double> &b)
{
	// return (a.second < b.second);	/* for ascending sort */
	return (a.second > b.second);
}


ftplen sort_vector_pair(ftplen vec)
{
	sort(vec.begin(), vec.end(), sort_by_second);

	return vec;
}


double vector_avg(std::vector<double> vec)
{
	double sum = 0.0; 
	
	for (int i=0; i<vec.size(); i++)
		sum += vec.at(i);

	return sum / vec.size();
}


double max_double(double a, double b)
{
	if (a > b)
		return a;
	else if (a < b)
		return b;
	else
		return a;
}


ftplen map_to_vector_pair(std::map<int, double> mymap)
{
	ftplen vec;

	for (int i=0; i<mymap.size(); i++)
		vec.push_back(std::make_pair(i, mymap[i]));

	return vec;
}


std::vector<int> get_keys(std::map<int, double> mymap)
{
	std::vector<int> vec;

	for (std::map<int, double>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		vec.push_back(it->first);

	return vec;
}

/* FIXME: fix double frame to ignore 1st col */
doubleframe* build_doubleframe(std::string input_name, int metacols)
{
	// d(int) *skip_cols = new int[1];
	// skip_cols[0] = metacols;

	ntstringframe* csv = read_csv((char *)input_name.c_str(), true, false, false);
	// ntstringframe *metadata = split_frame(ntstring, csv, skip_cols, true);
	doubleframe* dt = conv_frame(double, ntstring, csv);

	/* for (int k=0; k<dt->ncol; k++)
		std::cout << dt->data[0][k] << std::endl;
	printf("\n");
	*/
	for (int inst=0; inst<dt->nrow; inst++)
	{
		/* std::vector<double> new_inst;
		for (int i=0; i<dt->ncol; i++)
		{
			if (i == metacols)
				continue;
			new_inst.push_back(dt->data[inst][i]);
		}

		dt->data[inst] = vector_to_dub_ptr(new_inst);*/

		dt->data[inst] = &dt->data[inst][metacols + 2];  //FIXME: works for only removing first col
	}		

	dt->ncol-=2;

	return dt;
}


IsolationForest build_Isolation_forest(doubleframe* df)
{
	// IsolationForest iff(ntree,dt,nsample,maxheight,stopheight,rsample);
	IsolationForest iff(100, df, 1024, 0, false, true);
	return iff;
}


double* vector_to_dub_ptr(std::vector<double> vec)
{
	double *ptr_vec = vec.data();
	return ptr_vec;
}


std::vector<int> ordered_feats(ftplen vec)
{
	vec = sort_vector_pair(vec);
	std::vector<int> ord_feats;

	for (int i=0; i<vec.size(); i++)
		ord_feats.push_back(vec.at(i).first);

	return ord_feats;
}


double get_path_length(std::vector<double> inst, IsolationForest &iff)
{
	double *query = vector_to_dub_ptr(inst);
	std::vector<double> plens = iff.pathLength(query);
	
	return vector_avg(plens);
}


int get_num_cols_in_file(std::string filename)
{
	std::ifstream file(filename.c_str());
	std::string line;

	if(std::getline(file, line))
		file.close();

	return split(line, ',').size();
}


