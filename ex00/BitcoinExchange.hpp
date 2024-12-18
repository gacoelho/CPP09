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
public:
    Btc();
    Btc(const Btc &copy);
    Btc& operator=(const Btc & copy);
    ~Btc();
    float findExchange(const std::string& filename);
    int isDate(const std::string & date);
    int isValue(const std::string & value);
    void setData(std::string date, float value);
    void readIn(std::string path);
    std::map<std::string, float> getData();
};


#endif
