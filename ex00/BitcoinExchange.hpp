/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:28    by ekocak            #+#    #+#             */
/*   Updated: 2023/09/02 18:28    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP 

#include <ostream>
#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
#include <limits>
#include "Date.hpp"

#define SourceFile  "data.csv"

class BitcoinExchange
{
    private:
        std::map<Date, float>   _container;    
    public:
        BitcoinExchange();
        BitcoinExchange(std::map<Date, float>);
        BitcoinExchange(const BitcoinExchange&);
        BitcoinExchange& operator=(const BitcoinExchange&);
        ~BitcoinExchange();
        const std::map<Date, float>&  getContainer() const;
        void    setContainer(std::map<Date, float>&);
        void    populateMap();
        void    traverseInputFile(std::string);
        float   findValue(Date&) const;
        float   calculateValue(Date, float);
        static Date StartDate;
};

int testDateValidity(std::string &);
int testValueValidity(std::string &);
int testForPipe(std::string);
bool    myIsDigit(const std::string &);
bool    consecutiveDigits(const char *);
bool    consecutiveDigitsAndPoint(const char *);
bool    isEmpty(const char *);

#endif