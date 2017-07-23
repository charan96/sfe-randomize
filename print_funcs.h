#ifndef PRINT_H
#define PRINT_H

template <typename T>
void print_vector(vector<T> vec)
{
	for (int i=0; i<vec.size(); i++)
		cout << vec.at(i) << endl;
}


void print_dataframe(dataframe df);
void print_vector_pair(ftplen vec);

#endif
