#include "RPN.hpp"
#include <sstream>

RPN::RPN() : res(0), size(0)
{

}

RPN::RPN(const RPN& obj)
{
    *this = obj;
    return ;
}

RPN::~RPN()
{

}

bool RPN::isOperator(std::string c)
{
    if (c == "+" || c == "-" || c == "/" || c == "*")
        return (true);
    return (false);
}

int RPN::gather(std::string argv)
{
    std::stringstream ss(argv);
    std::string key;

    while (ss >> key)
    {
        if (isOperator(key) == false)
        {
            int nb(0);
            if (std::istringstream(key) >> nb)
                stack.push(nb);
            else
            {
                std::cerr << "Error : not a number" << std::endl;
                exit(1);
            }
        }
        else
        {
            if (stack.size() < 2)
            {
                std::cerr << "Error: review the RPN meaning" << std::endl;
                exit(1);
            }
            // std::cout << " y a ca dans la stack : " << stack.top() << std::endl;
            int num2 = stack.top();
            stack.pop();
            // std::cout << " y a ca dans la stack : " << stack.top() << std::endl;
            int num1 = stack.top();
            stack.pop();
            // std::cout << " " << key[0] << " " << std::endl;
            res = calcul(num1, num2, key[0]);
            stack.push(res);
        }
    }
    size = stack.size();
    return size;
}

RPN& RPN::operator=(const RPN& obj)
{
    if (this != &obj)
    {
        this->stack = obj.stack;
        this->res = obj.res;
    }
    return (*this);
}

int RPN::calcul(int num1, int num2, char c)
{
    switch (c)
    {
        case '+':
            return (num1 + num2);
            break;
        case '-':
            return (num1 - num2);
            break;
        case '/':
            if (num2 == 0)
            {
                std::cerr << "Error: division is impossible by zero" << std::endl;
                exit(1);
            }
            return (num1 / num2);
            break;
        case '*':
            return (num1 * num2);
            break;
    }
    return (res);
}

int RPN::getRes(void) const
{
    return (this->res);
}

std::ostream& operator<<(std::ostream& o, const RPN& i)
{
    o << i.getRes();
    return o;
}

