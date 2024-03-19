# include "BitcoinExchange.hpp"       

static double stod(const std::string & str)
{
	double num;
	std::stringstream ss(str);

	ss >> num;
	return (num);
}

static int stoi(const std::string & str)
{
	int num;
	std::stringstream ss(str);

	ss >> num;
	return (num);
}

Btc::Btc() 
{
    int i = 0;
    std::ifstream file ("./data.csv");
    if (!file.is_open())
        return;
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
            value = stod(line.substr(pos + 1));
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

float Btc::findExchange(const std::string & date)
{
    std::map<std::string, float>::iterator it = data.lower_bound(date);
    if (it->first != date && it != data.begin())
    {
            --it;
    }
    if (it != data.end())
        return it->second;
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

int Btc::isDate(const std::string & date)
{
	int d, m, y;

	size_t pos = date.find('-');
	size_t pos1 = date.find('-', pos + 1);

	if (pos == std::string::npos || pos1 == std::string::npos
	|| date.find_first_not_of("0123456789.-") != std::string::npos)
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return -1;
	}
	y = stoi(date.substr(0,pos));
	if (y  < 2009 || y > 2024)
	{
		std::cout << "Error: incorrect year => " << date << std::endl;
		return -1;
	}
	m = stoi(date.substr(pos + 1, pos1));
	if (m < 1 || m > 12)
	{
		std::cout << "Error: incorrect mouth => " << date << std::endl;
		return -1;
	}
	d = stoi(date.substr(pos1 + 1));
	if ( d < 1 || d > 31 || (d == 31 && (m == 2 || m == 4 || m == 6 || m == 9 || m == 11))
	|| (d > 28 && m == 2 && y % 4 != 0) || (d > 29 && m == 2  && y % 4 == 0))
	{
		std::cout << "Error: incorrect day => " << date << std::endl;
		return -1;
	}
	return 0;
}

int Btc::isValue(const std::string & v)
{
	if(v.empty() || v.find_first_not_of("0123456789.-") != std::string::npos
	|| v.at(0) == '.' || v.find('.', v.length() - 1) != std::string::npos)
		std::cout << "Error: incorrect number => " << v << std::endl;
	else if (v.at(0) == '-')
		std::cout << "Error: not a positive number." << std::endl;
	else if (v.length() > 10 || (v.length() == 10 && v > "2147483647"))
		std::cout << "Error: too large of a number." << std::endl;
	else
		return 0;
	return -1;

}

void Btc::readIn(std::string path)
{
    int i = 0;
    std::ifstream file2(path.c_str());
    if (!file2.is_open())
    {
 	std::cout << "Error: could not open file" << std::endl;
        return;
    }
    std::string line;
    while(std::getline(file2,line))
    {
        if(i == 0)
        {
            i = 1;
            continue;
        }
	line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        size_t pos = line.find('|');
	std::string date = line.substr(0, pos);
	std::string value = line.substr(pos + 1);
	if (Btc::isDate(date) == -1)
	       continue;
	else if (pos == std::string::npos)
	{
		std::cout << "Error: bad input. Nothing after '|'." << std::endl;
	       	continue;	
	}
	else if (Btc::isValue(value)== -1)
		continue;
	float v = stod(value);
	float rate = Btc::findExchange(date);
	std::cout << date << " => " << v << " = " << v * rate << std::endl;
    }
    file2.close();
}
