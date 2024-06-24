/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 00:06    by ekocak            #+#    #+#             */
/*   Updated: 2023/10/01 00:06    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
    int result;
    int flag = 0;
    RPN stack;
    std::queue<int> myQueue;
    
    if (argc != 2 || argv[1] == nullptr)
    {
        std::cout << "Error: Missing argument." << std::endl;
        return (-1);
    }
    else if (argv[1][0] == '\0')
    {
        std::cout << "Error: Empty argument." << std::endl;
        return (-1);
    }

    std::istringstream lineStream1(argv[1]);
    std::string  token;                    
    while (lineStream1 >> token)            
    {
        if (!isInteger(token) && !isOperator(token))
        {
            std::cout << "Error: Unrecognised input." << std::endl;
            return (-2);
        }
        std::istringstream lineStream2(token);
        if (isInteger(token))         
        {
            int num;
            lineStream2 >> num; 
            if (num < -9 || num > 9)
            {
                std::cout << "Error: Operands must be single digit" << std::endl;
                return (-2);            
            }
            stack.push(num);
            myQueue.push(num);
        }
        else if (isOperator(token))
        {   
            try
            {
                if (stack.size() < 2)
                {
                    std::cout << "Error: Not enough operands for operator." << std::endl;
                    return (-3);
                }
                result = stack.conductCalculation(token[0]);
                flag = 1;
                while (!myQueue.empty())
                {
                    myQueue.pop();
                }
            }
            catch (InvalidOperationException &e)
            {
                std::cout << "Error: Invalid operation." << std::endl;
                return (-3);
            }
        }
    }
    if (flag)
        std::cout << result << " ";
    while (!myQueue.empty())
    {
        std::cout << myQueue.front() << " ";
        myQueue.pop();
    }
    std::cout << std::endl;
    return (0);
}