#ifndef PRINT_H
#define PRINT_H

#include "iforest/IsolationForest.hpp"

template <typename T>
void print_vector(std::vector<T> vec)
{
	std::cout << "printing vector: " << std::endl;

	for (int i=0; i<vec.size(); i++)
		std::cout << vec.at(i) << std::endl;

	std::cout << std::endl;
}


template <typename T1, typename T2>
void print_map(std::map<T1, T2> mymap)
{
	std::cout << "key\t" << "value" << std::endl;

	for (int i=0; i<mymap.size(); i++)
		std::cout<< i << "\t" << mymap[i] << std::endl;
}


void print_dataframe(dataframe df);
void print_vector_pair(ftplen vec);
void print_explanations(std::vector<std::vector<int> > ranked_feats);
void print_doubleframe(doubleframe *df);

#endif
