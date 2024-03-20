#ifndef PMERGEME_HPP
# define PMERGEM_HPP
# include <exception>
# include <string>
# include <list>
# include <vector>
# include <iostream>

class PmergeMe
{
	public:
		PmergeMe(void);
		PmergeMe(const PmergeMe & copy);
		PmergeMe &operator=(const PmergeMe & copy);
		~PmergeMe(void);
	   		
		void sortVec(int argc, char **argv);
		void sortList(int argc, char **argv);
		
		class IE_Exception : public std::exception
		{
			public:
				virtual const char* what() const throw();

		};
};
unsigned int f_stou(const std::string & str);
#endif
