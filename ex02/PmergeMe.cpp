#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <list>
#include <sstream>
#include "PmergeMe.hpp"

#define MICROSECOND 100000

unsigned int f_stou(const std::string &str)
{
	unsigned int num;
	std::stringstream ss(str);
	ss >> num;
	return (num);
}

PmergeMe::PmergeMe(void) {};

PmergeMe::PmergeMe(const PmergeMe & copy)
{
	*this = copy;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& copy)
{
	(void)copy;
	return *this;
}

PmergeMe::~PmergeMe(void) {};

static void printVec(std::vector<unsigned int>& vec)
{ 
	std::vector<unsigned int>::const_iterator itr;
	for (itr = vec.begin(); itr != vec.end(); itr++)
		std::cout << *itr << " ";
	std::cout << std::endl;
}

static std::vector<unsigned int> mergeVecs(std::vector<unsigned int> & n1, std::vector<unsigned int> & n2)
{
	std::vector<unsigned int> r;

	while (!n1.empty() && !n2.empty())
	{
		if(n1.front() <= n2.front())
		{
			r.push_back(n1.front());
			n1.erase(n1.begin());
		}
		else
		{
			r.push_back(n2.front());
			n2.erase(n2.begin());
		}
	}
	
	while (!n1.empty())
	{
		r.push_back(n1.front());
		n1.erase(n1.begin());
	}
	while (!n2.empty())
	{
		r.push_back(n2.front());
		n2.erase(n2.begin());
	}

	return r;
}

static std::vector<unsigned int> mergeInsertVec(std::vector<unsigned int> & v)
{
	if (v.size() <= 1)
	{
		return v;
	}

	int mid = v.size() / 2;
	std::vector<unsigned int> n1(v.begin(), v.begin() + mid);
	std::vector<unsigned int> n2(v.begin() + mid, v.end());

	n1 = mergeInsertVec(n1);
	n2 = mergeInsertVec(n2);

	return (mergeVecs(n1, n2));
}


void PmergeMe::sortVec(int argc, char **argv)
{
	std::vector<unsigned int> stor;
	for (int i = 1; i < argc; i += 1)
	{
		stor.push_back(f_stou(argv[i]));
	}
	std::cout << "<vec>Before: ";
	printVec(stor);
	std::clock_t start = std::clock();
	stor = mergeInsertVec(stor);
	double time_taken = static_cast<double>(std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC) * MICROSECOND;
	std::cout << "<vec>After: ";
	printVec(stor);
	std::cout << "Time to process a range of " << argc - 1
	<< " elements " << "with std::vector<unsigned int> : "
	<< time_taken << " µs" << std::endl;
}

static void printList(std::list<unsigned int> & lst)
{
	std::list<unsigned int>::const_iterator itr;
	for (itr = lst.begin(); itr != lst.end(); itr++)
		std::cout << *itr << " ";
	std::cout << std::endl;
}
static std::list<unsigned int> mergeLists(std::list<unsigned int> & n1, std::list<unsigned int> & n2)
{
	std::list<unsigned int> r;

	while (!n1.empty() && !n2.empty())
	{
		if(n1.front() <= n2.front())
		{
			r.push_back(n1.front());
			n1.erase(n1.begin());
		}
		else
		{
			r.push_back(n2.front());
			n2.erase(n2.begin());
		}
	}
	
	while (!n1.empty())
	{
		r.push_back(n1.front());
		n1.erase(n1.begin());
	}
	while (!n2.empty())
	{
		r.push_back(n2.front());
		n2.erase(n2.begin());
	}

	return r;
}

static std::list<unsigned int> mergeInsertList(std::list<unsigned int> & v)
{
	if (v.size() <= 1)
	{
		return v;
	}

	int mid = v.size() / 2;
	std::list<unsigned int> n1;
	std::list<unsigned int> n2;

	for (int i = 0; i < mid; i++)
	{
		n1.push_back(v.front());
		v.pop_front();
	}
	n2 = v;
	n1 = mergeInsertList(n1);
	n2 = mergeInsertList(n2);

	return (mergeLists(n1, n2));
}


void PmergeMe::sortList(int argc, char **argv)
{
	std::list<unsigned int> stor;
	for (int i = 1; i < argc; i += 1)
	{
		stor.push_back(f_stou(argv[i]));
	}
	std::cout << "<list>Before: ";
	printList(stor);
	std::clock_t start = std::clock();
	stor = mergeInsertList(stor);
	double time_taken = static_cast<double>(std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC) * MICROSECOND;
	std::cout << "<list>After: ";
	printList(stor);
	std::cout << "Time to process a range of " << argc - 1
	<< " elements " << "with std::list<unsigned int> : "
	<< time_taken << " µs" << std::endl;
}

const char* PmergeMe::IE_Exception::what() const throw()
{
	return "PmergeMe exception: invalid element";
}
