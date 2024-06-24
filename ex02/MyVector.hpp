/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyVector.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:47    by ekocak            #+#    #+#             */
/*   Updated: 2023/09/25 11:47    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYVECTOR_HPP
# define MYVECTOR_HPP

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
#include "PmergeMe.hpp"

class MyVector : public std::vector<unsigned>
{
    public:
        MyVector();
        MyVector(const MyVector&);
        MyVector& operator=(const MyVector &);
        ~MyVector();
        void    populateMyVector(int, char **);
        void    mergeMyVector(unsigned, unsigned, unsigned); 
        void    mergeSortMyVector(unsigned, unsigned);
        void    binaryInsert(unsigned &value, int);
        unsigned    binarySearch(const unsigned, int);
};

std::ostream& operator<<(std::ostream&, const MyVector&);

class PairsVector
{
    private:
        std::vector<std::pair<unsigned, unsigned> > _containerPV;
        MyVector    _containerMain;
        MyVector    _containerPend;
        void        mergePairsContainer(unsigned, unsigned, unsigned);
        unsigned    binarySearch(const unsigned, int);

    public:
        PairsVector();
        PairsVector(const PairsVector&);
        ~PairsVector();
        std::vector<std::pair<unsigned, unsigned> >  getContainerPV() const;
        MyVector    &getContainerMain();
        MyVector    &getContainerPend();
        void        populatePairsVector(int, char **);
        void        sortIndividualPairs();
        void        mergeSortPairsContainer(unsigned, unsigned);
        void        generateMainAndPending();
        void        insertPendingToMainContainer();
        void        insertMain(unsigned &);
};
std::ostream &operator<<(std::ostream &, const PairsVector&);
void printContainerPV(const std::vector<std::pair<unsigned, unsigned> >& containerPV);

#endif