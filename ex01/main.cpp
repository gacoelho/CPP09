# include "RPN.hpp"


int main(int argc, char **argv)
{
    if (argc != 2 || !RPN::valid_exp(argv[1]))
    {
        std::cout << "Error : Bad Input" << std::endl;
        return (0);
    }
    try
    {
        std::cout << RPN::cal(argv[1]) << std::endl;
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << "\n";
    }
    return 0;
}