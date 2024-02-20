#include "PmergeMe.hpp"

void PmergeMe::generateJacob()
{
    unsigned long int size;
    unsigned long int jacob;
    int index(3);

    if (lastOdd)
    {
        pendingStackV.push_back(lastOdd);
        pendingStackD.push_back(lastOdd);
    }
    size = pendingStackV.size();
    size = pendingStackD.size();
    while ((jacob = jacobsthal(index)) < size - 1)
    {
        jacobStack.push_back(jacob);
        index++;
    }
}

void PmergeMe::generatePosition()
{
    unsigned long int lastPos(1); //suivra la derniere position inseree dans mon vecteur tab
    unsigned long int i(0);
    unsigned long int value(1); //je stocke les nombres de Jacob
    unsigned long int actualPos(0);

    if (pendingStackV.empty())
        return ;
    if (pendingStackD.empty())
        return ;
    generateJacob();
    while (i < jacobStack.size()) //value prend les positions de jacobstack une a une
    {
        value = jacobStack.at(i);
        tmpPositionV.push_back(value);
        tmpPositionD.push_back(value);
        actualPos = value - 1;
        while (actualPos > lastPos)
        {
            tmpPositionV.push_back(actualPos);
            tmpPositionD.push_back(actualPos);
            actualPos--;
        }
        lastPos = value;
        i++;
    }
    while (value < pendingStackV.size())
    {
        value++;
        tmpPositionV.push_back(value);
    }
    while (value < pendingStackD.size())
    {
        value++;
        tmpPositionD.push_back(value);
    }
}

int PmergeMe::binarySearchV(std::vector<int> tab, int target, int begin, int end)
{
    int mid(0);

    while (begin <= end)
    {
        mid = begin + (end - begin) / 2;
        if (target == tab.at(mid))
            return (mid);
        if (target > tab.at(mid))
            begin = mid + 1;
        else
            end = mid - 1;
    }
    if (target > tab.at(mid))
    {
        return (mid + 1);
    }
    return (mid);
}

int PmergeMe::binarySearchD(std::deque<int> tab, int target, int begin, int end)
{
    int mid(0);

    while (begin <= end)
    {
        mid = begin + (end - begin) / 2;
        if (target == tab.at(mid))
            return (mid);
        if (target > tab.at(mid))
            begin = mid + 1;
        else
            end = mid - 1;
    }
    if (target > tab.at(mid))
        return (mid + 1);
    return (mid);
}

int PmergeMe::jacobsthal(int n)
{
    if (n == 0)
        return (0);
    if (n == 1)
        return (1);
    return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

////for binary search :
// std::cout << "target = " << target << std::endl;
// std::cout << "tab.at(mid) = " << tab.at(mid) << std::endl;
// std::cout << "mid = " << mid << std::endl;
