#include <iostream>
#include "convolution.h"

int main()
{
	// This is just a dummy example and it's nothing with the solution of the problem.

	std::vector<int> a{1,1,4,5,1,4},b{1,9,1,9,8,1,0};
	auto c=convolution(a,b);
	for(auto &i: c)
		std::cout<<i<<' ';
	std::cout<<'\n';
	return 0;
}
