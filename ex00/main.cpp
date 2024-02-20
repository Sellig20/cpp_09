#include "BitcoinExchange.cpp"
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
	BitcoinExchange BitCoin("data.csv");
	(void)argc;
	if (!argv[1])
	{
		std::cerr << "Error: file missing" << std::endl;
		return (0);
	}
	std::ifstream inFile(argv[1]);
	std::string line;
	std::getline(inFile, line);
	if (!inFile.is_open())
		return (std::cerr << "Error: opening the file", 0);
	if (inFile.peek() == std::ifstream::traits_type::eof())
		std::cout << "Error: file is empty" << std::endl;
	while (std::getline(inFile, line))
	{
		std::stringstream ss(line);
		std::string date;
		float value(0);
		getline(ss, date, '|');
		ss >> value;
		if (!value)
		{
			std::cerr << "Error: empty line" << std::endl;
			continue ;
		}
		try 
		{
			float rate(0);
			rate = BitCoin.calcul(date, value);
			if (rate == -1)
				continue;
			float res(0);
			res = rate * value;
			// std::cout << rate << " " << value << std::endl;
			std::cout << date << " => " << std::fixed << std::setprecision(2) << value << " = " << res << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what()  << std::endl;
		}
	}
	inFile.close();
}