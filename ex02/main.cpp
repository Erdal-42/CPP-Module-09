/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:47    by ekocak            #+#    #+#             */
/*   Updated: 2023/09/25 11:47    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MyList.hpp"
#include <ctime>

int COMMENT = 0;

int compareContainers(MyVector &vec, MyList &list)
{
    MyVector::iterator  itV = vec.begin();
    MyList::iterator    itL = list.begin();
    while(itV != vec.end() && itL != list.end())
    {
        if (*itV != *itL)
            return (0);
        itV ++;
        itL ++;
    }
    return (vec.size() == list.size()); 
}

MyVector    testVector(int argc, char **argv)
{
    std::clock_t start = std::clock();
    PairsVector pv;
    pv.populatePairsVector(argc, argv);
    if (COMMENT)
    {    
        std::cout << std::endl << "VECTOR CONTAINER" << std::endl;
        std::cout << "Input Paired: \t\t\t\t\t";
        printContainerPV(pv.getContainerPV());
    }
    pv.sortIndividualPairs();
    if (COMMENT)
    {
        std::cout << "Individual Pairs Sorted: \t\t\t";
        printContainerPV(pv.getContainerPV());
    }
    pv.mergeSortPairsContainer(0, pv.getContainerPV().size()-1);
    if (COMMENT)
    {
        std::cout << "Pairs Vector Sorted: \t\t\t\t";
        printContainerPV(pv.getContainerPV());
    }
    pv.generateMainAndPending();
    if (COMMENT)
    {
        std::cout << "Main Vector Established: \t\t\t";
        std::cout << pv.getContainerMain() << std::endl;
        std::cout << "Pending Vector Established: \t\t\t";
        std::cout << pv.getContainerPend() << std::endl;
    }
    pv.insertPendingToMainContainer();
    if (COMMENT)
    {
        std::cout << "Pending Have Been Transferred To Main: \t\t";
        std::cout << pv.getContainerMain() << std::endl;
    }
    if (!(argc % 2))
    {
        MyVector &ref = pv.getContainerMain();
        unsigned temp = ft_atou(argv[argc-1]);
        ref.binaryInsert(temp, ref.size()-1);
        if (COMMENT)
        {
            std::cout << "Single Element Has Been Inserted Into Main: \t";
            std::cout << pv.getContainerMain() << std::endl;
        }
    }
    std::clock_t vectorTime = std::clock() - start;
    pv.getContainerPend().clear();
    std::cout << "Before:\t";
    int i;
    for (i = 1; i < argc && i < 36; i ++)
        std::cout << argv[i] << " ";
    if (argc > i)
        std::cout << ".."; 
    std::cout << std::endl;
    std::cout << "After:\t" << pv.getContainerMain() << std::endl;
    std::cout << "Time to process a range of " << argc - 1 
              << " elements with std::vector : \t" << vectorTime << " us (microseconds)" << std::endl;
    return (pv.getContainerMain());
}

MyList    &testList(int argc, char **argv)
{
    std::clock_t start = std::clock();
    PairsList   pl;
    pl.populatePairsList(argc, argv);
    if (COMMENT)
    {    
        std::cout << std::endl << "LIST CONTAINER" << std::endl;
        std::cout << "Input Paired: \t\t\t\t\t";
        printPairsList(pl.getContainerPL());
    }
    pl.sortIndividualPairs();
    if (COMMENT)
    {
        std::cout << "Individual Pairs Sorted: \t\t\t";
        printPairsList(pl.getContainerPL());
    }
    pl.mergeSortPairsContainer(0, pl.getContainerPL().size() - 1);
    if (COMMENT)
    {
        std::cout << "Pairs List Sorted: \t\t\t\t";
        printPairsList(pl.getContainerPL());
    }
    pl.generateMainAndPending();
    if (COMMENT)
    {
        std::cout << "Main List Established: \t\t\t\t";
        printList(pl.getContainerMain());
        std::cout << "Pending List Established: \t\t\t";
        printList(pl.getContainerPend());
    }
    pl.insertPendingToMainContainer();
    if (COMMENT)
    {
        std::cout << "Pending Have Been Transferred To Main: \t\t";
        printList(pl.getContainerMain());
    }
    if (!(argc % 2))
    {
        MyList &ref = pl.getContainerMain();
        unsigned temp = ft_atou(argv[argc-1]);
        ref.binaryInsert(temp, ref.size()-1);
        if (COMMENT)
        {
            std::cout << "Single Element Has Been Inserted Into Main: \t";
            printList(pl.getContainerMain());
        }
    }
    std::clock_t listTime = std::clock() - start;
    pl.getContainerPend().clear();
    if (COMMENT)
    {
        std::cout << "Before:\t";
        int i;
        for (i = 1; i < argc && i < 36; i ++)
            std::cout << argv[i] << " ";
        if (argc > i)
            std::cout << ".."; 
        std::cout << std::endl;
        std::cout << "After:\t";
        MyList  &ref = pl.getContainerMain();
        printList(ref);
    }
    std::cout << "Time to process a range of " << argc - 1 
              << " elements with std::list : \t" << listTime << " us (microseconds)" << std::endl; 
    return (pl.getContainerMain());
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        std::cout << ft_atou(argv[1]) << std::endl; 
    }
    else if (argc == 1)
        errorExit(1);
    else if (argc > 2)
    {
        testVector(argc, argv);
        testList(argc, argv);
    }
    return (0);
}