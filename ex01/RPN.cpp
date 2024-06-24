/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 00:06    by ekocak            #+#    #+#             */
/*   Updated: 2023/10/01 00:06    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "RPN.hpp"

RPN::RPN()
{}

RPN::~RPN()
{}
int RPN::conductCalculation(char op)
{
    int result;

    if (size() < 2)
    {
        std::cout << "Error: Invalid operation." << std::endl;
        exit(EXIT_FAILURE);
    }
    int num1 = top();
    pop();
    int num2 = top();
    pop();
 
    switch (op)
    {
        case '+':
            result = num1 + num2;
            break ;
        case '-':
            result = num2 - num1;
            break ;
        case '*':
            result = num1 * num2;
            break ;
        case '/':
            if (num1 == 0)
            {
                std::cout << "Error: Division by zero." << std::endl;
                exit(EXIT_FAILURE) ;
            }
            else 
                result = num2 / num1;
    }
    push(result);
    return (result); 
}

const char *InvalidOperationException::what() const throw()
{
    return "Error: Invalid operation.";
}

bool    isInteger(std::string token)
{
    unsigned i = 0;
    if (token[i] == '-')
    {
        if (token.length() == 1)
            return (false);
        i ++;
    }
    for(; i < token.length(); i ++)
    {
        if (token[i] < '0' || token[i] > '9')
            return (false);
    }
    return (true);
}

bool    isOperator(std::string token)
{
    if (token.length() != 1)
        return (false);
    if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')
        return (true);
    return (false);
}

void printStack(const std::stack<int>& s)
{
    std::stack<int> tempStack = s;

    while (!tempStack.empty())
    {
        tempStack.pop();
    }
    std::cout << std::endl;
}