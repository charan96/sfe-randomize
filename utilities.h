#ifndef UTILITIES_H
#define UTILITIES_H

vector<double> str_to_double_vector(vector<string> vec);
int randint(int start, int end);
vector<string> split(string str, char delim);
bool sort_by_second(const pair<int, float> &a, const pair<int, float> &b);
ftplen sort_vector_pair(ftplen vec);
float get_path_length(vector<double> query);

#endif
