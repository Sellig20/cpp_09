#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <map>
#include <climits>
#include <iomanip>
#include <exception>

class BitcoinExchange
{
    public :
        BitcoinExchange();
        BitcoinExchange(std::string data);
        BitcoinExchange&	operator=(const BitcoinExchange& obj);
        bool    check_argv(std::string file);
        bool    _date(int year, int month, int day);
        bool    checkValue(float value);
        int     intLength(int nb);
        float   calcul(std::string& date, float nb);

    private :
        std::map<std::string, float> tabMap;
};

#endif
