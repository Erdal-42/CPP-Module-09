/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:47    by ekocak            #+#    #+#             */
/*   Updated: 2023/09/25 11:47    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

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


class MyException : public std::exception
{
public:
    const char* what() const throw();
};

unsigned    ft_atou(char *);
void        errorExit(int);
unsigned    calculateJacobsthal(unsigned);

#endif
