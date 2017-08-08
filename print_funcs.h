#ifndef PRINT_H
#define PRINT_H

template <typename T>
void print_vector(std::vector<T> vec)
{
	for (int i=0; i<vec.size(); i++)
		std::cout << vec.at(i) << std::endl;
}


void print_dataframe(dataframe df);
void print_vector_pair(ftplen vec);

#endif
