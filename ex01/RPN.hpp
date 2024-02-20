#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stdlib.h>
#include <stack>
#include <exception>
#include <string>

class RPN
{
    public :
        RPN();
        RPN(const RPN& obj);
        ~RPN();
        int gather(std::string argv);
        bool isOperator(std::string c);
        RPN& operator=(const RPN& obj);
        int calcul(int num1, int num2, char c);
        int getRes() const;

    private :
        int res;
        std::stack<int> stack;
        int size;
};

std::ostream& operator<<(std::ostream& o, const RPN& i);

#endif