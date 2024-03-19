# include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    (void)argv;
    if (argc != 2)
    {
        std::cout << "Error : could not open file." << std::endl;
        return 0;
    }
    Btc btc;
    btc.readIn(argv[1]);
}