#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if(argc == 1)
		return 1;
	PmergeMe pmm;
	try
	{
		for (int i = 1; i < argc; i += 1)
			if (std::string(argv[i]).find_first_not_of("0123456789 ") != std::string::npos)
				throw PmergeMe::IE_Exception();
		std::vector<unsigned int> tmp;
		for (int i = 1; i < argc; i+= 1)
			tmp.push_back(f_stou(argv[1]));
		std::vector<unsigned int>::iterator itr;
		std::vector<unsigned int>::iterator itr2;
		for (itr = tmp.begin(); itr != tmp.end(); itr++)
		{
			for(itr2 = itr + 1; itr2 != tmp.end(); itr2++)
				if (*itr2 == *itr)
					throw PmergeMe::IE_Exception();
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	pmm.sortVec(argc, argv);
	std::cout << std::endl;
	pmm.sortList(argc, argv);
	return 0;
}
