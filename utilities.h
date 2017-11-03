#ifndef UTILITIES_H
#define UTILITIES_H

#include "iforest/IsolationForest.hpp"

std::vector<double> str_to_double_vector(std::vector<std::string> vec);		/* convert string vector to double vector */
int randint(int start, int end);						/* random integer in range; inclusive */

std::vector<std::string> split(std::string str, char delim);			/* split string based on delimiter */
bool sort_by_second(const std::pair<int, float> &a, const std::pair<int, float> &b);	/* helper function to sort_vector_pair */

ftplen sort_vector_pair(ftplen vec);						/* sort vector of pairs (ftplen) based on second value in pair; asc/desc sorting based on sort_by_second function */
float get_path_length(std::vector<double> inst, IsolationForest &iff);		/* path length in the isolation forest for the passed in instance/datapoint */

doubleframe* build_doubleframe(std::string input_name, int metacols);				/* build doubleframe (from iforest code) from the passed in file name  and skip metacols*/
IsolationForest build_Isolation_forest(doubleframe* df);			/* build the isolation forest object from the doubleframe ptr */

double* vector_to_dub_ptr(std::vector<double> vec);				/* convert double vector to double array using ptr */
std::vector<int> ordered_feats(ftplen vec);					/* sort the ftplen object and sort it using sort_vector_pair and return only the feature names */

float max_float(float a, float b);						/* max of two floats */
ftplen map_to_vector_pair(std::map<int, float> mymap);				/* convert */

std::vector<int> get_keys(std::map<int, float> mymap);				/* */
int get_lines_in_file(std::string filename);					/* number of lines in a given file passed in as file name */

float vector_avg(std::vector<double> vec);					/* get the average of the double vector */
int get_num_cols_in_file(std::string filename);

double avg_depth_of_all_datapoints(std::vector<std::vector<double> > path_lengths);
std::vector<int> subvector(std::vector<int> vec, int num_elements);

std::vector<std::vector<int> > read_bench_expl_file(std::string input_file);
std::vector<std::vector<double> > get_all_datapoints(dataframe data);

std::vector<int> get_anomalies_idx(dataframe data);

#endif
