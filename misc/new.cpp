#include <iostream>
#include <vector>

int main()
{
	std::vector<int> vec = {10};
	std::cout << vec.size() << "\t" << vec.at(0) << std::endl;

	return 0;
}
