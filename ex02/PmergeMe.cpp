/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:47    by ekocak            #+#    #+#             */
/*   Updated: 2023/09/25 11:47    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void    errorExit(int n)
{
    if (n == 1)
        std::cout << "Error: Please enter sequence of unsigned integers for sorting.\n";
    else if(n == 2)
        std::cout << "Error: All numbers entered must be unsigned.\n";
    else if (n == 3)
        std::cout << "Error: Please enter digits only.\n";
    exit(EXIT_FAILURE); 
}

unsigned    ft_atou(char *str)
{
    int total;

    if (!str)
        errorExit(1);
    if (*str && *str == '-')
        errorExit(2);
    total = 0;
    while (*str)
    {
        if (*str < '0' || *str > '9')
            errorExit(3);
        total = total * 10 + (*str - '0');
        ++ str;
    }
    return (total);
}

unsigned    calculateJacobsthal(unsigned n)
{
    if (n == 0)
        return (0);
    else if (n == 1)
        return (1);
    else 
        return calculateJacobsthal(n - 1) + (2 * calculateJacobsthal(n-2));
}