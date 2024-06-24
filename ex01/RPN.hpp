/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 00:06    by ekocak            #+#    #+#             */
/*   Updated: 2023/10/01 00:06    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>


class RPN : public std::stack<int>
{
    public:
        RPN();
        ~RPN();
        int conductCalculation(char);
};

class InvalidOperationException : public std::exception
{
    public:
        const char *what() const throw();
};

bool    isInteger(std::string);
bool    isOperator(std::string);
void    printStack(const std::stack<int> &);
#endif
