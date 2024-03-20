#include "RPN.hpp"

static int f_stoi(const std::string & str)
{
    int num;
    std::stringstream ss(str);

    ss >> num;
    return num;
}

long int RPN::scal(const std::string & s, int n1, int n2)
{
    if(s == "+")
        return(n1 + n2);
    else if (s == "-")
        return(n1 - n2);
    else if (s == "*")
        return(n1 * n2);
    else if (s == "/")
    {
        if (n2 == 0)
            throw DBZ_Exception();
        else
            return(n1 / n2);
    }
    return (0);
}

RPN::RPN(void) {};

RPN::RPN(const RPN & copy)
{
    *this = copy;
}

RPN &RPN::operator=(const RPN &copy)
{
    (void)copy;
    return *this;
}

RPN::~RPN() {};

bool RPN::valid_exp(const std::string & exp)
{
        if (exp.find_first_not_of("0123456789+-/* ") == std::string::npos)
            return true;
        return false;
}

long int RPN::cal(const std::string & exp)
{
    int n1, n2, r;
    std::stringstream pfix(exp);
    std::stack<int> temp;
    std::string s;

    while (pfix >> s)
    {
        if (s == "+" || s == "-" || s == "/" || s == "*")
        {
            if (temp.size() < 2)
                throw NR_Exception();
            n1 = temp.top();
            temp.pop();
            n2 = temp.top();
            temp.pop();
            r = scal(s,n2,n1);
            temp.push(r);  
        }
        else 
            temp.push(f_stoi(s));
    }
    return temp.top();
}
const char * RPN::NR_Exception::what() const throw()
{
    return "RPN exception: No result. Something wrong in the format";
}

const char * RPN::DBZ_Exception::what() const throw()
{
    return  "RPN exception: division by zero";
}