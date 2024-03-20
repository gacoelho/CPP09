#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <exception>
# include <iostream>
# include <sstream>
# include <stack>

class RPN
{
	public:
		RPN(void);
		RPN(const RPN & copy);
		RPN &operator=(const RPN & copy);
		~RPN(void);

		static bool valid_exp(const std::string & expr);
		static long int cal(const std::string& expr);
		static long int scal(const std::string & s, int n1, int n2);

		class NR_Exception : public std::exception
		{
			public:
				virtual const char * what() const throw();
		};
		class DBZ_Exception : public std::exception
		{
			public:
				virtual const char * what() const throw();
		};
};

#endif
