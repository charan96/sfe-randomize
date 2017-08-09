#ifndef UTILITIES_H
#define UTILITIES_H

#include "iforest/IsolationForest.hpp"

std::vector<double> str_to_double_vector(std::vector<std::string> vec);
int randint(int start, int end);
std::vector<std::string> split(std::string str, char delim);
bool sort_by_second(const std::pair<int, float> &a, const std::pair<int, float> &b);
ftplen sort_vector_pair(ftplen vec);
float get_path_length(std::vector<double> inst, IsolationForest &iff);
doubleframe* build_doubleframe(std::string input_name);
IsolationForest build_Isolation_forest(doubleframe* df);
double* vector_to_dub_ptr(std::vector<double> vec);
float max_float(float a, float b);
ftplen map_to_vector_pair(std::map<int, float> mymap);
std::vector<int> get_keys(std::map<int, float> mymap);
int get_lines_in_file(std::string filename);
// std::vector<double> get_vector_from_vector_pair(ftplen vec_pair);
// std::vector<double> add_vectors(std::vector<double> a, std::vector<double> b);

#endif
