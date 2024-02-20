#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <deque>
#include <ctime>
#include <utility>
#include <algorithm>

class PmergeMe
{
    public :
        PmergeMe();
        ~PmergeMe();
        void gather(int nb);
        void displayBefore(void);
        void displayAfter(void);
        bool isEven();
        void toPair();
        void sortPair();
        void generateJacob();
        void sortMeV(std::vector<std::pair<int, int> > &vecPair, int begin, int endr);
        void mergeMeV(std::vector<std::pair<int, int> >& vecPair, int begin, int mid, int end);
        void sortMeD(std::deque<std::pair<int, int> > &vecPair, int begin, int endr);
        void mergeMeD(std::deque<std::pair<int, int> >& vecPair, int begin, int mid, int end);
        int jacobsthal(int n);
        void generatePosition();
        void assemble(char **argv, int argc);
        void getIntegerSequence(char **argv);
        int binarySearchV(std::vector<int> tab, int target, int begin, int end);
        int binarySearchD(std::deque<int> tab, int target, int begin, int end);
        void sortPair2();
        void finalStack();


    private :
        std::vector<int> vector;
        std::deque<int> deque;

        std::vector<std::pair<int, int> > vecPair;
        std::deque<std::pair<int, int> > deqPair;

        std::vector<int> finalTabV;
        std::deque<int> finalTabD;

        std::vector<int> mainStackV;
        std::vector<int> pendingStackV;

        std::deque<int> mainStackD;
        std::deque<int> pendingStackD;

        std::vector<int> jacobStack;

        std::vector<int> tmpPositionV;
        std::deque<int> tmpPositionD;

        int lastOdd;
        int last;

    protected :

};

#endif