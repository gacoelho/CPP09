#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>


class Btc
{
private:
    std::map <std::string, float> data;
    int flag;
public:
    Btc();
    Btc(const Btc &copy);
    Btc& operator=(const Btc & copy);
    ~Btc();
    float findExchance(const std::string& filename);
    void setData(std::string date, float value);
    void readIn(std::string path);
    
    std::map<std::string, float> getData();
    std::vector<std::string> split(std::string str, char c);
};


#endif