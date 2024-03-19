#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <exception>

class RPN
{
	public;
	RPN(void);
	RPN(const RPN & copy);
	RPN &operator=(const RPN & copy);
	~RPN(void);

	static bool valid_exp(const std::string & expr);
	static long int cal(const std::string& expr);

	class NR_Exception : public std::exception
	{
		public:
			virtual const *what() const throw();
	};
	class DBZ_Exception : public std::exception
	{
		public:
			virtual const *what() const throw();
	};
};

#endif
