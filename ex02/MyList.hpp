/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyList.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:47    by ekocak            #+#    #+#             */
/*   Updated: 2023/09/25 11:47    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYLIST_HPP
# define MYLIST_HPP

#include "MyVector.hpp"
#include <vector>
#include <list>
#include <exception>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ostream>
#include <string>
#include <sys/time.h>

class MyList : public std::list<unsigned>
{
    public:
        MyList();
        MyList(const MyList&);
        MyList& operator=(const MyList &);
        ~MyList();
        void populateMyList(int, char **);
        std::list<unsigned> merge(const MyList &, const MyList &);
        void        mergeSortMyList();
        MyList      mergeMyList(const MyList &, const MyList &);
        void        binaryInsert(unsigned &, int);
        unsigned    binarySearch(const unsigned, int right);
        MyList      insertSortL(unsigned num); 
};

class PairsList
{
    private:
        std::list<std::pair<unsigned, unsigned> > _containerPL; 
        MyList      _containerMain;
        MyList      _containerPend;
        unsigned    binarySearch(const unsigned);
        unsigned    size;

    public:
        PairsList();
        ~PairsList();
        PairsList(const PairsList &);
        std::list<std::pair<unsigned, unsigned> >  &getContainerPL();
        MyList      &getContainerMain();
        MyList      &getContainerPend();
        void        populatePairsList(int, char **);
        void        sortIndividualPairs();
        void        mergeSortPairsContainer(unsigned, unsigned);
        void        mergePairsContainer(unsigned, unsigned, unsigned);
        void        generateMainAndPending();
        void        insertPendingToMainContainer();
        void        insertMain(unsigned &);
        unsigned    getSize();
};

void printList(MyList &);
void printPairsList(std::list<std::pair<unsigned, unsigned> >&);

#endif