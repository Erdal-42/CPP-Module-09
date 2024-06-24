/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:28    by ekocak            #+#    #+#             */
/*   Updated: 2023/09/02 18:28    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"   

void testDate()
{
    std::cout << "=======TEST FOR DATE DECREMENT()=======" << std::endl; 
    Date date1(2000, 3, 1);
    date1.decrement();
    std::cout << date1 << std::endl;

    Date date2(2004, 3, 1);
    date2.decrement();
    std::cout << date2 << std::endl;

    Date date3(2001, 12, 1);
    date3.decrement();
    std::cout << date3 << std::endl;

    Date date4(2001, 11, 1);
    date4.decrement();
    std::cout << date4 << std::endl;

    Date date5(2001, 10, 1);
    date5.decrement();
    std::cout << date5 << std::endl;
    
    Date date6(2001, 9, 1);
    date6.decrement();
    std::cout << date6 << std::endl;

    Date date7(2001, 8, 1);
    date7.decrement();
    std::cout << date7 << std::endl;

    Date date8(2001, 7, 1);
    date8.decrement();
    std::cout << date8 << std::endl;

    Date date9(2001, 6, 1);
    date9.decrement();
    std::cout << date9 << std::endl;

    Date date10(2001, 5, 1);
    date10.decrement();
    std::cout << date10 << std::endl;

    Date date11(2001, 4, 1);
    date11.decrement();
    std::cout << date11 << std::endl;

    Date date12(2001, 3, 1);
    date12.decrement();
    std::cout << date12 << std::endl;

    Date date13(2001, 2, 1);
    date13.decrement();
    std::cout << date13 << std::endl;

    Date date14(2001, 1, 1);
    date14.decrement();
    std::cout << date14 << std::endl;

    std::cout << "=======TEST FOR DATE VALIDITY=======" << std::endl;
    Date date15(0, 5, 5);
    std::cout << date15 << " Validity: " << date15.valid() << std::endl; 

    Date date16(2010, 0, 5);
    std::cout << date16 << " Validity: " << date16.valid() << std::endl;

    Date date17(2010, 5, 0);
    std::cout << date17 << " Validity: " << date17.valid() << std::endl;

    Date date18(2010, 5, 13);
    std::cout << date18 << " Validity: " << date18.valid() << std::endl;

    Date date19(2010, 5, 32);
    std::cout << date19 << " Validity: " << date19.valid() << std::endl;

    Date date20(2011, 2, 29);
    std::cout << date20 << " Validity: " << date20.valid() << std::endl;

    Date date21(2012, 2, 29);
    std::cout << date21 << " Validity: " << date21.valid() << std::endl;
}

int main(int argc, char **argv)
{
//    testDate();
    if (argc < 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return (1);
    }
    std::ifstream inputFile(argv[1]);   
    if (!inputFile.is_open()) 
    {
        std::cout << "Error: could not open file." << argv[1] << std::endl;
        return (2);
    }
    inputFile.close();
    std::cout << "=======TEST FOR BITCOIN EXCHANGE=======" << std::endl;
    BitcoinExchange *btc = new BitcoinExchange();
    btc->populateMap();
    btc->traverseInputFile(argv[1]);

    delete (btc);
    return (0);
}
