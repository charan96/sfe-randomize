#include <iostream>
#include <vector>

std::vector<int> foo(std::vector<int> f)
{
	std::vector<int> newf;

	for (int k: f)
		newf.push_back(k * 10);
	
	return newf;
}


void printvec(std::vector<int> a)
{
	for (int i: a)
		std::cout << i << std::endl;

	printf("\n\n");
}


int main()
{
	std::vector<int> feats = {1,2,3,4,5};
	
	printvec(feats);
	feats = foo(feats);
	printvec(feats);
	return 0;
}
