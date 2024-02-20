#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : lastOdd(0), last(0)
{

}

PmergeMe::~PmergeMe()
{

}

void PmergeMe::gather(int nb)
{
    vector.push_back(nb);
    deque.push_back(nb);
}

void PmergeMe::displayBefore(void)
{
    std::cout << "Before: <vector> ";
    for (std::vector<int>::iterator it = vector.begin(); it < vector.end(); it++)
    {
        std::cout << *it << " ";
        last = *it;
    }
    std::cout << std::endl;

    std::cout << "Before: <deque> ";
    for (std::deque<int>::iterator it = deque.begin(); it < deque.end(); it++)
    {
        std::cout << *it << " ";
        last = *it;
    }
    std::cout << std::endl;
}

void PmergeMe::displayAfter(void)
{
    std::cout << std::endl;
    std::cout << "After: <vector> ";
    for (std::vector<int>::iterator it = finalTabV.begin(); it < finalTabV.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "After: <deque> ";
    for (std::vector<int>::iterator it = finalTabV.begin(); it < finalTabV.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

bool PmergeMe::isEven(void)
{
    int nbV(0);
    int nbD(0);
    nbV = vector.size() % 2;
    nbD = deque.size() % 2;
    if (nbV == 0)
        return (true);
    if (nbD == 0)
        return (true);
    for (std::vector<int>::iterator it = vector.begin(); it < vector.end(); it++)
    {
        lastOdd = *it;
    }
    vector.pop_back();
    for (std::deque<int>::iterator it = deque.begin(); it < deque.end(); it++)
    {
        lastOdd = *it;
    }
    deque.pop_back();
    return (false);
}

void PmergeMe::toPair(void)
{
    isEven();
    std::vector<int>::iterator itV = vector.begin();
    std::deque<int>::iterator itD = deque.begin();

    while (itV < vector.end())
    {
        if (*itV < (*(itV + 1)))
            std::swap(*itV, *(itV + 1));
        vecPair.push_back(std::make_pair(*itV, *(itV + 1)));
        itV+=2;
    }
    while (itD < deque.end())
    {
        if (*itD < (*(itD + 1)))
            std::swap(*itD, *(itD + 1));
        deqPair.push_back(std::make_pair(*itD, *(itD + 1)));
        itD+=2;
    }
}

bool comparePair(const std::pair<int,int>& pair, const std::pair<int, int>& nextPair)
{
    if (pair.first != nextPair.first)
        return pair.first < nextPair.first;
    else
        return pair.second < nextPair.second;
}

void PmergeMe::mergeMeV(std::vector<std::pair<int, int> >& vecPair, int begin, int mid, int end)
{
    std::vector<std::pair<int, int> >leftTab(vecPair.begin() + begin, vecPair.begin() + mid + 1);
    //right tab = premiere moitie du tableau de paire
    std::vector<std::pair<int, int> >rightTab(vecPair.begin() + mid + 1, vecPair.begin() + end + 1);
    //left tab = deuxieme moitie a partir du milieu + 1

    unsigned long int lTi(0);
    unsigned long int rTi(0);
    unsigned long int sT(begin);
    while (lTi < leftTab.size() && rTi < rightTab.size()) // on parcourt nos deux tab
    {
        //a la recherche de la plus petite paire pour la metre au debut de notre futur sorted tab
        if (leftTab[lTi].first <= rightTab[rTi].first) // si LEFT est plus petit, on lui fout dedans
        {
            vecPair[sT] = leftTab[lTi];
            lTi++;
        }
        else // sinon on lui fout le droite
        {
            vecPair[sT] = rightTab[rTi];
            rTi++;
        }
        sT++; //on reecrit le tableau avec les bons elements tries
    }
    while (lTi < leftTab.size())
    {
        vecPair[sT] = leftTab[lTi];
        lTi++;
        sT++;
    }
    while (rTi < rightTab.size())
    {
        vecPair[sT] = rightTab[rTi];
        rTi++;
        sT++;
    }
}

void PmergeMe::mergeMeD(std::deque<std::pair<int, int> >& deqPair, int begin, int mid, int end)
{
    std::deque<std::pair<int, int> >leftTab(deqPair.begin() + begin, deqPair.begin() + mid + 1);
    //left tab = premiere moitie du tableau de paire jusqua milieu
    std::deque<std::pair<int, int> >rightTab(deqPair.begin() + mid + 1, deqPair.begin() + end + 1);
    //right tab = deuxieme moitie a partir du milieu + 1 jusqua fin


    unsigned long int lTi(0);
    unsigned long int rTi(0);
    unsigned long int sT(begin);
    lTi = 0;
    rTi = 0;

    //right tab = premiere moitie du tableau de paire
    while (lTi < leftTab.size() && rTi < rightTab.size()) // on parcourt nos deux tab. permet de selectionner la + petite pour le debut
    {
        //a la recherche de la plus petite paire pour la mettre au debut de notre futur sorted tab
        if (leftTab[lTi].first <= rightTab[rTi].first) // si LEFT est plus petit, on lui fout dedans
        {
            deqPair[sT] = leftTab[lTi];
            lTi++;
        }
        else // sinon on lui fout le droite
        {
            deqPair[sT] = rightTab[rTi];
            rTi++;
        }
        sT++; //on reecrit le tableau avec les bons elements tries
    }
    while (lTi < leftTab.size()) //et apres quoiquil faut bien mettre lautre pair
    {
        deqPair[sT] = leftTab[lTi];
        lTi++;
        sT++;
    }
    while (rTi < rightTab.size())
    {
        deqPair[sT] = rightTab[rTi];
        rTi++;
        sT++;
    }
}

void PmergeMe::sortMeV(std::vector<std::pair<int, int> > &vecPair, int begin, int end)
{
    if (begin < end)
    {
        int mid = begin + (end - begin) / 2;
        sortMeV(vecPair, begin, mid);
        sortMeV(vecPair, mid + 1, end);
        mergeMeV(vecPair, begin, mid, end);
    }
}

void PmergeMe::sortMeD(std::deque<std::pair<int, int> > &deqPair, int begin, int end)
{
    if (begin < end)
    {
        int mid = begin + (end - begin) / 2;
        sortMeD(deqPair, begin, mid);
        sortMeD(deqPair, mid + 1, end);
        mergeMeD(deqPair, begin, mid, end);
    }
}

void PmergeMe::finalStack()
{
    int target(0);
    unsigned long int endPos(0);
    unsigned long int final_posi(0);
    unsigned long int count(0);

    generatePosition();
    for (std::vector<int>::iterator it = tmpPositionV.begin(); it < tmpPositionV.end(); it++)
    {
        target = pendingStackV.at(*it - 1); //ma nouvelle target a inserer dans FINAL STACK, je pars de la fin pour jacob
        endPos = *it + count;
        final_posi = binarySearchV(finalTabV, target, 0, endPos); //la position que doit avoir mon nombre pour la FINAL STACK
        finalTabV.insert(finalTabV.begin() + final_posi, target);
        count++;
    }
    ////////////////////////meme chose pour DEQUE ///////////////////
    target = 0;
    endPos = 0;
    final_posi = 0;
    count = 0;
    for (std::deque<int>::iterator it = tmpPositionD.begin(); it < tmpPositionD.end(); it++)
    {
        target = pendingStackD.at(*it - 1);
        endPos = *it + count;
        final_posi = binarySearchD(finalTabD, target, 0, endPos);
        finalTabD.insert(finalTabD.begin() + final_posi, target);
        count++;
    }
}

void PmergeMe:: sortPair(void)
{
    std::vector<std::pair<int, int> >::iterator itV = vecPair.begin();
    while (itV < vecPair.end())
    {
        std::pair<int, int>& paire = *itV;
        mainStackV.push_back(paire.first);
        pendingStackV.push_back(paire.second);
        itV++;
    }
    /////On met le premier de pending au premier de mainstack
    std::vector<int>::iterator itVa = pendingStackV.begin();
    finalTabV.push_back(*itVa);
    for (std::vector<int>::iterator itV = mainStackV.begin(); itV < mainStackV.end(); itV++)
    {
        finalTabV.push_back(*itV);
    }
    //////////////////////////// meme chose pour DEQUE //////////////////////////
    std::deque<std::pair<int, int> >::iterator itD = deqPair.begin();
    while (itD < deqPair.end())
    {
        std::pair<int, int>& paire = *itD;
        mainStackD.push_back(paire.first);
        pendingStackD.push_back(paire.second);
        itD++;
    }
    /////On met le premier de pending au premier de mainstack
    std::deque<int>::iterator itDa = pendingStackD.begin();
    finalTabD.push_back(*itDa);
    for (std::deque<int>::iterator itD = mainStackD.begin(); itD < mainStackD.end(); itD++)
    {
        finalTabD.push_back(*itD);
    }
}

void PmergeMe::assemble(char **argv, int argc)
{
    for (int i(1); i < argc; i++)
    {
        std::string str = argv[i];
        gather(atoi(str.c_str()));
    }
    displayBefore();
    if (vector.size() == 1)
    {
        finalTabV.push_back(std::atoi(argv[1]));
        finalTabD.push_back(std::atoi(argv[1]));
        displayAfter();
        return ;
    }
    toPair();
    sortMeV(vecPair, 0, vecPair.size() - 1);
    sortMeD(deqPair, 0, deqPair.size() - 1);
    sortPair();
    finalStack();
    displayAfter();
}


//////////SORT PAIR
 // for (std::vector<int>::iterator it = pendingStack.begin(); it < pendingStack.end(); it++)
    // {
    //     std::cout << "Pending STACK -> " << *it << std::endl;
    // }
    // int i = 0;
    // for (std::vector<int>::iterator it = finalTabV.begin(); it < finalTab.end(); it++)
    // {
    //     std::cout << "Final STACK -> " << *it << std::endl;
    //     // std::cout << "i => " << i << std::endl;
    //     i++;
    // }

//////////////////DISPLAY
    //  std::vector<std::pair<int, int> >::iterator it = vecPair.begin();
    // while (it < vecPair.end())
    // {
    //     std::pair<int, int>& paire = *it;
    //     // std::pair<int, int>& nextPaire = *(it + 1);
    //     std::cout << "===================> (" << paire.first << " , " << paire.second << ")" << std::endl;
    //     it++;
    // }


    //IMPRESSION PENDING ET MAIN STACK
    // for (std::vector<int>::iterator it = finalTab.begin(); it < finalTab.end(); it++)
    // {
    //     std::cout << "Main STACK -> " << *it << std::endl;
    // }
    // for (std::vector<int>::iterator it = pendingStack.begin(); it < pendingStack.end(); it++)
    // {
    //     std::cout << "Pending STACK -> " << *it << std::endl;
    // }

     // std::vector<std::pair<int, int> >::iterator it = vecPair.begin();
    // while (it < vecPair.end())
    // {
    //     std::pair<int, int>& paire = *it;
    //     // std::pair<int, int>& nextPaire = *(it + 1);
    //     std::cout << "===================> (" << paire.first << " , " << paire.second << ")" << std::endl;
    //     it++;
    // }

//     void PmergeMe::sortPair2()
// {
//     // std::vector<std::pair<int, int> >::iterator it = vecPair.begin();
//     // while (it < vecPair.end())
//     // {
    //     std::pair<int, int>& paire = *it;
    //     // std::pair<int, int>& nextPaire = *(it + 1);
    //     std::cout << "===================> (" << paire.first << " , " << paire.second << ")" << std::endl;
    //     it++;
    // }

    // std::vector<std::pair<int, int> >::iterator iti = vecPair.begin();
    // while (iti < vecPair.end())
    // {
    //     if (*iti < (*(iti + 1)))
    //     {
    //         std::cout << "ouiouiuoui" << std::endl;
    //         std::swap(*iti, *(iti + 1));
    //     }
    //     iti+=2;
    // }

    // std::cout << std::endl;
    // std::vector<std::pair<int, int> >::iterator ita = vecPair.begin();
    // while (ita < vecPair.end())
    // {
    //     std::pair<int, int>& paire = *ita;
    //     // std::pair<int, int>& nextPaire = *(ita + 1);
    //     std::cout << "===================> (" << paire.first << " , " << paire.second << ")" << std::endl;
    //     ita++;
    // }


       // std::vector<std::pair<int, int> >::iterator it = vecPair.begin();
    // while (it < vecPair.end())
    // {
    //     std::pair<int, int>& paire = *it;
    //     // std::pair<int, int>& nextPaire = *(it + 1);
    //     std::cout << "PAIRE => (" << paire.first << " , " << paire.second << ")" << std::endl;
    //     it++;
    // }

        // std::cout << "Before: <deque> ";
    // for (std::deque<int>::iterator it = deque.begin(); it < deque.end(); it++)
    // {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;


//     void PmergeMe::getIntegerSequence(char **argv)
// {
//     int i(1);
//     char *ptr;
//     int value(0);

//     while (argv[i])
//     {
//         if (argv[i][0] == '\0')
//         {
//             std::cerr << "EXCEPTION JON 1" << std::endl;
//             exit(1);
//         }
//         value = std::strtol(argv[i], &ptr, 10);
//         if (*ptr != '\0' || value < 0)
//         {
//             std::cerr << "EXCEPTION JON 2" << std::endl;
//             exit(1);
//         }
//         vector.push_back(value);
//         i++;
//     }
// }

    // if (vector.size() % 2 != 0)
    // {
    //     target = vector.at(vector.size() - 1);
    //     pos = binarySearch(finalTab, target, 0, finalTab.size() - 1);
    //     finalTab.insert(finalTab.begin() + pos, target);
    // }



////////////////->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//before first while :
    // while (sT < deqPair.size())
    // {
    //     std::cout << ">>>>>>>>>>>>>>" << deqPair[sT].first << ", " << deqPair[sT].second << std::endl;
    //     sT++;
    // }
    // sT = begin;
//befor condition if () :  std::cout << "Est ce que " << leftTab[lTi].first << ", " << leftTab[lTi].second << " est + petit que " << rightTab[rTi].first << ", " << rightTab[rTi].second << " ?" << std::endl;
//in each condition if or else :
            // std::cout << "1) " << leftTab[lTi].first << std::endl;
            // std::cout << "2) " << rightTab[rTi].first << std::endl;
            // std::cout << "3) " << leftTab[lTi].first << std::endl;
            // std::cout << "4) " << rightTab[rTi].first << std::endl;
        //at the end of the function :
    // sT = begin;
    // while (sT < deqPair.size())
    // {
    //     std::cout << "//////////////" << deqPair[sT].first << ", " << deqPair[sT].second << std::endl;
    //     sT++;
    // }





//pour final stack fonction
// std::cout << "*it de tmpposi " << *it << std::endl;
// for(std::vector<int>::iterator ita = pendingStackV.begin(); ita < pendingStackV.end(); ita++)
// {
//     std::cout << *ita << std::endl;
// }
// for(std::vector<int>::iterator ito = finalTabV.begin(); ito < finalTabV.end(); ito++)
// {
//     std::cout << "Final ------- " << *ito << std::endl;
// }
