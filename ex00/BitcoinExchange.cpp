# include "BitcoinExchange.hpp"       

Btc::Btc() 
{
    this->flag = 1;
    int i = 0;
    std::ifstream file ("./data.csv");
    if (!file.is_open())
    {
        this->flag = 0;
        return;
    }
    std::string line;
    while(std::getline(file, line))
    {
        if (i == 0)
        {
            i = 1;
            continue;
        }
        size_t pos = line.find(',');
        if (pos == std::string::npos)
        {
            std::cerr << "Error: Invalid Paramter" << std::endl;
            continue;
        }
        std::string date = line.substr(0, pos);
        double value;
        try
        {
            value = std::stod(line.substr(pos + 1));
        }
        catch(const std::exception& a)
        {
           (void)a;
           std::cerr << "Error : could not transform value in float nor int" << std::endl;
           continue;
        }
        this->setData(date, value);
    }
    file.close();        
}

Btc::~Btc() {}

Btc::Btc(Btc const & copy)
{
    *this = copy;
}

Btc &Btc::operator=(Btc const & copy)
{
    this->data =copy.data;
    return(*this);
}

float Btc::findExchance(const std::string & date)
{
    std::map<std::string, float>::iterator it = data.lower_bound(date);
    if (it->first != date && it != data.begin())
    {
            --it;
    }
    if (it != data.end())
        return it ->second;
    else if(!data.empty())
        return it->second;
    return -1.0;
}

void Btc::setData(std::string date, float value)
{
    this->data.insert(std::make_pair(date, value));
}

std::map<std::string, float> Btc::getData()
{
    return(this->data);
}

std::vector<std::string> Btc::split(std::string str, char c)
{
    std::vector<std::string> v_substr;
    std::string substr = "";

    for (size_t i = 0; i < str.length(); i++)
    {
        if(str[i] != c)
        {
            substr += str[i];
        }
        else
        {
            v_substr.push_back(substr);
            while (str[i] == c)
            {
                i++;
            }
            i--;
            substr = "";
        }
    }
    v_substr.push_back(substr);
    return (v_substr);
}

void Btc::readIn(std::string path)
{
    int i = 0;
    std::ifstream file2(path);
    if (!file2.is_open())
    {
        this->flag = -1;
        return;
    }
    std::string line;
    std::vector<std::string> v_line;
    while(std::getline(file2,line))
    {
        if(i == 0)
        {
            i = 1;
            continue;
        }
        v_line = this->split(line, '|');
        if (v_line[1].length() == 0 || v_line.size() < 2)
        {
            std::cout << "Error: bad input => " << v_line[0] << std::endl;
            continue;
        }
        float f = this->findExchance(v_line[0]);
        if (f != -1)
        {
            try
            {
                if (std::stod(v_line[1]) > 1000)
                {
                    std::cout << "Error: too large a number" << std::endl;
                }
                else if (std::stod(v_line[1]) < 0)
                {
                    std::cout << "Error: not a positive number." << std::endl;
                } 
                else
                    std::cout << v_line[0] << " => " << v_line[1] << " = " << std::stod(v_line[1]) * f << std::endl;
            }
            catch(const std::exception& e)
            {
                (void)e;
                std::cout << "Error: Not a number" << std::endl;
                continue;
            }
            
        }
    }
    file2.close();
}