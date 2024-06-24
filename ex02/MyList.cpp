/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyList.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:47    by ekocak            #+#    #+#             */
/*   Updated: 2023/09/25 11:47    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "MyList.hpp"

MyList::MyList()
{}

MyList::MyList(const MyList &other) : std::list<unsigned>(other) 
{}

MyList &MyList::operator=(const MyList& other)
{
    if (this != &other)
    {
        std::list<unsigned>::operator=(other);
    }
    return (*this);
}

MyList::~MyList()
{}

void    MyList::populateMyList(int argc, char **argv)
{
    int i = 1;
    int num;

    while (i < argc)
    {
        num = ft_atou(argv[i]);
        push_back(num);
        i ++;
    }
}

void MyList::mergeSortMyList()
{
    if (size() <= 1)
        return;

    MyList left, right;
    int middle = size() / 2;
    int index = 0;

    for (MyList::iterator it = begin(); it != end(); ++it)
    {
        if (index < middle)
            left.push_back(*it);
        else
            right.push_back(*it);
        index++;
    }

    left.mergeSortMyList();
    right.mergeSortMyList();

    MyList::iterator it = begin();
    MyList::iterator leftIter = left.begin();
    MyList::iterator rightIter = right.begin();

    while (leftIter != left.end() && rightIter != right.end())
    {
        if (*leftIter < *rightIter)
        {
            *it = *leftIter;
            ++leftIter;
        }
        else
        {
            *it = *rightIter;
            ++rightIter;
        }
        ++it;
    }
    while (leftIter != left.end())
    {
        *it = *leftIter;
        ++leftIter;
        ++it;
    }
    while (rightIter != right.end())
    {
        *it = *rightIter;
        ++rightIter;
        ++it;
    }
}

MyList MyList::mergeMyList(const MyList &left, const MyList &right)
{
    MyList result;
    MyList::const_iterator leftIter = left.begin();
    MyList::const_iterator rightIter = right.begin();
    while (leftIter != left.end() && rightIter != right.end())
    {
        if (*leftIter < *rightIter)
        {
            result.push_back(*leftIter);
            ++ leftIter;
        }
        else
        {
            result.push_back(*rightIter);
            ++ rightIter;
        }
    }
    while (leftIter != left.end())
    {
        result.push_back(*leftIter);
        ++ leftIter;
    }
    while (rightIter != right.end())
    {
        result.push_back(*rightIter);
        ++ rightIter;
    }
    return result;  
}

unsigned    MyList::binarySearch(const unsigned value, int right) 
{
    int left = 0;
    MyList::iterator   iter;

    while (left <= right) 
    {
        int middle = (left + right) / 2;
        iter = begin();
        for (int i = 0; i < middle; ++i)
        {
            ++iter;
        }
        if (*iter < value) 
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }
    return left;
}

void    MyList::binaryInsert(unsigned& value, int right)
{
    int insertionPoint = binarySearch(value, right);
    MyList::iterator iter = begin();
    for (int i=0; i < insertionPoint; i ++)
        iter ++;
    insert(iter, value);
}

PairsList::PairsList() : size(0)
{}

PairsList::~PairsList()
{}

PairsList::PairsList(const PairsList &other)
{
    _containerPL = other._containerPL;
}

std::list<std::pair<unsigned, unsigned> >  &PairsList::getContainerPL()
{
    return _containerPL;
}

MyList    &PairsList::getContainerMain()
{
    return _containerMain;
}

MyList    &PairsList::getContainerPend()
{
    return _containerPend;
}

unsigned    PairsList::getSize()
{
    return (size);
}

void    PairsList::populatePairsList(int argc, char **argv)
{
    int i = 1;
    int num1, num2;

    while ((i + 1) < argc)
    {
        num1 = ft_atou(argv[i]);
        num2 = ft_atou(argv[i+1]);

        _containerPL.push_back(std::make_pair(num1, num2));
        size ++;
        i += 2;
    }
    if (!(argc % 2)) 
        ft_atou(argv[i]);
}

void    PairsList::sortIndividualPairs()
{
    unsigned    temp;
    std::list<std::pair<unsigned, unsigned> > &containerRef = getContainerPL();
    std::list<std::pair<unsigned, unsigned> >::iterator   iter = containerRef.begin();  
    for ( ; iter != containerRef.end(); iter ++)
    {
        if (iter->first > iter->second) 
        {
            temp = iter->first;
            iter->first = iter->second;
            iter->second = temp;
        }
    }
}

void    PairsList::mergeSortPairsContainer(unsigned left, unsigned right)
{
    if (left < right)
    {
        unsigned    middle = left + (right - left) / 2;
        mergeSortPairsContainer(left, middle);
        mergeSortPairsContainer(middle + 1, right);
        mergePairsContainer(left, middle, right);
    }
}

void PairsList::mergePairsContainer(unsigned left, unsigned middle, unsigned right)
{
    unsigned n1 = middle - left + 1;
    unsigned n2 = right - middle;

    std::list<std::pair<unsigned, unsigned> > leftHalf;
    std::list<std::pair<unsigned, unsigned> > rightHalf;
    std::list<std::pair<unsigned, unsigned> >::iterator iter = _containerPL.begin();
    std::advance(iter, left);
    for (unsigned i = 0; i < n1; i++)
    {
        leftHalf.push_back(*iter);
        ++iter;
    }

    iter = _containerPL.begin();
    std::advance(iter, middle + 1);
    for (unsigned i = 0; i < n2; i++)
    {
        rightHalf.push_back(*iter);
        ++iter;
    }

    iter = _containerPL.begin();
    std::advance(iter, left);
    std::list<std::pair<unsigned, unsigned> >::iterator leftIter = leftHalf.begin();
    std::list<std::pair<unsigned, unsigned> >::iterator rightIter = rightHalf.begin();

    while (leftIter != leftHalf.end() && rightIter != rightHalf.end())
    {
        if (leftIter->second <= rightIter->second)
        {
            *iter = *leftIter;
            ++leftIter;
        }
        else
        {
            *iter = *rightIter;
            ++rightIter;
        }
        ++iter;
    }
    while (leftIter != leftHalf.end())
    {
        *iter = *leftIter;
        ++leftIter;
        ++iter;
    }
    while (rightIter != rightHalf.end())
    {
        *iter = *rightIter;
        ++rightIter;
        ++iter;
    }
}

void    PairsList::generateMainAndPending()
{
    MyList      main;
    MyList      pending;

    std::list<std::pair<unsigned, unsigned> >::iterator    iter;
    for (iter = _containerPL.begin(); iter != _containerPL.end(); iter ++)
    {
        pending.push_back(iter->first);    
        main.push_back(iter->second);
    }
    _containerMain = main;
    _containerPend = pending;
}

void    PairsList::insertPendingToMainContainer()
{
    unsigned    insert_index;
    unsigned    jacobsthal_index;
    unsigned    insertion_range_in_main;
    unsigned    prev_jacobsthal_index = 0; 
    int n = 3;                      

    jacobsthal_index = calculateJacobsthal(n) - 1;
    insertion_range_in_main = jacobsthal_index;
    _containerMain.push_front(*(_containerPend.begin()));
    while (_containerMain.size() < (2 * _containerPend.size()))
    {
        if (jacobsthal_index < _containerPend.size())
            insert_index = jacobsthal_index;
        else
            insert_index = _containerPend.size() - 1;
        MyList::iterator iter = _containerPend.begin();
        for (unsigned i=0; i < insert_index; i ++)
            iter ++;   
        while (insert_index != prev_jacobsthal_index)
        {                                               
            _containerMain.binaryInsert(*iter, insertion_range_in_main ++);
            insert_index --;
            iter --;
        }
        prev_jacobsthal_index = jacobsthal_index;
        n ++;
        jacobsthal_index = calculateJacobsthal(n) - 1;
        insertion_range_in_main += jacobsthal_index - prev_jacobsthal_index;
        if (insertion_range_in_main > _containerMain.size() - 1)
            insertion_range_in_main = _containerMain.size() - 1;
    }
}

void printPairsList(std::list<std::pair<unsigned, unsigned> >& _container)
{
    int i = 0;
    std::list<std::pair<unsigned, unsigned> >::iterator iter;
    for (iter = _container.begin(); iter != _container.end() && i < 36; ++ iter)
    {
        std::cout << "[" << iter->first << "," << iter->second << "]";
        i ++;
    }
    std::cout << std::endl;
}

void printList(MyList &_container)
{
    MyList::iterator iter;
    unsigned i = 0;
    for (iter = _container.begin(); iter != _container.end() && i < 36; ++ iter, i ++)
    {
        std::cout << *iter << " ";
    }
    if (i < _container.size())
            std::cout << "..";
    std::cout << std::endl;
}

