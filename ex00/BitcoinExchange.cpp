#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(std::string data)
{
    std::string const fileName(data);
	std::ifstream flux2(fileName.c_str());
    std::string line;
	if (flux2)
	{
		while (getline(flux2, line))
		{
			std::stringstream ss(line);
			std::string date;
			ss >> date;
			float y = 0;
			int pos1 = date.find(',');
			std::string str = date.substr(pos1 + 1); //get value
			std::string str1 = date.erase(pos1); //get date
			y = atof(str.c_str());
			tabMap[str1] = y;
		}
	}
}

bool    BitcoinExchange::check_argv(std::string date)
{
	int year(0);
	int month(0);
	char separator;
	int day(0);
	std::istringstream ss(date);
	ss >> year >> separator >> month >> separator >> day;
	if (date.length() != 11)
	{
		std::cerr << "Error: bad input => " << date << std::endl;
		return false;
	}
	else if (_date(year, month, day) == false)
	{
		std::cerr << "Error: bad input => " << date << std::endl;
		return false;
	}
	return true;
}

int BitcoinExchange::intLength(int nb)
{
	int len = 0;
	if (nb == 0)
		len = 1;
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

bool BitcoinExchange::_date(int year, int month, int day)
{
	if (year > 2023 || month > 12 || day > 31)
	{
		return (false);
	}
	else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
	{
        return false;
    }
	else if (year <= 0 || month <= 0 || day <= 0)
	{
		return false;
	}
	else if (intLength(year) > 4 || intLength(year) < 0 || intLength(month) > 2 || intLength(day) > 2
		|| intLength(month) < 0 || intLength(day) < 0)
	{
		return (false);
	}
	else if (month == 2)
	{
		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
		{//if bissextile
			if (day > 29)
				return (false);
		}
		else
		{//if non bissextile
			if (day > 28)
				return (false);
		}
	}
	return (true);
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& obj)
{
	if (this != &obj)
		this->tabMap = obj.tabMap;
	return (*this);
}

bool BitcoinExchange::checkValue(float value)
{
	if (value == -2147483648 || value == 2147483648)
	{
		std::cerr << "Error: too large value" << std::endl;
		return (false);
	}
	else if (value < 0)
	{
		std::cerr << "Error: negative value" << std::endl;
		return (false);
	}
	else if (value > 1000)
	{
		std::cerr<< "Error : too large value" << std::endl;
		return (false);
	}
	return (true);
}

float BitcoinExchange::calcul(std::string& date, float nb)
{
	if (checkValue(nb) == false)
		return (-1);
	if (check_argv(date) == false)
		return (-1);
	std::map<std::string, float>::iterator it = tabMap.find(date);
	if (it == tabMap.end())
	{
		it = tabMap.lower_bound(date);
		if (it == tabMap.begin())
			it->second = 0;
		else
			--it;
	}
	return (it->second);
}
