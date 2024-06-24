/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:28    by ekocak            #+#    #+#             */
/*   Updated: 2023/09/02 18:28    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

Date BitcoinExchange::StartDate = Date(0,0,0);

BitcoinExchange::BitcoinExchange() 
{}

BitcoinExchange::BitcoinExchange(std::map<Date, float> theContainer) : _container(theContainer)
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    _container = other._container;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        _container.clear();
        std::map<Date, float>::const_iterator it = other._container.begin();
        while (it != other._container.end())
        {
            _container.insert(std::make_pair(it->first, it->second));
            it ++;
        }
    }
    return (*this);
}

BitcoinExchange::~BitcoinExchange()
{} 

const std::map<Date, float>&   BitcoinExchange::getContainer() const
{
    return _container;
}
        
void    BitcoinExchange::setContainer(std::map<Date, float>& theContainer)
{
    _container = theContainer;
}

/**
 * @brief Populate the Bitcoin data container from a source file.
 *
 * The source file is expected to be in CSV format, with each line 
 * containing date and value information separated by commas. It 
 * first reads and discards the header line of the CSV file since 
 * it is assumed to contain column headers and not data. Afterward, 
 * it iterates through each data line, extracting the date and value 
 * components, and inserts them into the container.
 * Additionally, it keeps track of the earliest date encountered 
 * during this process and updates the 'StartDate' static member 
 * variable accordingly.
 *
 * The function first attempts to open the source file and checks if 
 * it can be opened successfully. If the file cannot be opened, it 
 * prints an error message and returns without modifying the container.
 *
 * Finally, the data file is closed, and the function returns, leaving 
 * the container populated with Bitcoin data.
 *
 * @note This function assumes that the CSV file format is valid and 
 * adheres to the expected structure. If the file does not exist or 
 * cannot be opened, it logs an error message and returns without 
 * modifying the container.
 *
 * @see Date
 * @see convertStrToDate
 *
 * @param None.
 * @return None.
 */
void BitcoinExchange::populateMap()
{
    std::ifstream inputFile(SourceFile);
    if (!inputFile.is_open()) {
        std::cout << "Error opening the source file: " << SourceFile << std::endl;
        return ;
    }
    std::string line;
    Date& sDate = StartDate;
    std::getline(inputFile, line);
    while (std::getline(inputFile, line))
    { 
        std::stringstream lineStream(line);
        std::string str_date;
        std::getline(lineStream, str_date, ',');
        Date date = convertStrToDate(str_date);
        std::string str_value;
        std::getline(lineStream, str_value, ',');
        const float value = std::atof(str_value.c_str());
        _container.insert(std::make_pair(date, value));
        if (StartDate == Date(0,0,0))
            StartDate = date;
        if (date < sDate)
            sDate = date;
    }
    inputFile.close();
    StartDate = sDate;
}

/**
 * @brief Traverse and process data from an input file.
 *
 * This function reads and processes data from the referance
 * of a specified input file line by line. Each line is 
 * expected to contain date and value information separated 
 * by '|'. The function validates the input data, calculates 
 * a derived value based on the date and provided value, and 
 * prints the results. Errors are reported for invalid dates, 
 * non-positive values or values exceeding the maximum limit.
 *
 * If the date and value are valid, it calculates and prints 
 * the result using the 'calculateValue' function. Finally, 
 * the input file is closed.
 *
 * @param param The name of the input file to be processed.
 *
 * @details
 * The function opens the input file specified by 'param' and 
 * checks if it's successfully opened. If the file cannot be 
 * opened, it prints an error message and exits with a failure 
 * code.
 *
 * For each line in the input file, it extracts the date and 
 * value portions. It then validates the date, checks for 
 * non-positive values, and verifies that the value doesn't 
 * exceed the maximum limit. If any of these conditions are 
 * not met, corresponding error messages are printed.
 *
 * @see calculateValue
 *
 * @param param The name of the input file to be processed.
 */
void BitcoinExchange::traverseInputFile(std::string param)
{
    std::ifstream inputFile(param);     
    if (!inputFile.is_open())     
    {
        std::cout << "Error: could not open file: " << param << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string line;
    std::getline(inputFile, line);          
    std::string str_date;                     
    std::string str_value;
    while (std::getline(inputFile, line))     
    {
        std::stringstream lineStream(line);    
        std::getline(lineStream, str_date, '|');
        Date date = convertStrToDate(str_date);
        std::getline(lineStream, str_value, '|');
        if (!testDateValidity(str_date))         
            continue ;
        else if (!testForPipe(line))
            continue;
        else if (!testValueValidity(str_value))
            continue ; 
        else     
        {
            float fValue = std::atof(str_value.c_str());     
            std::cout << date << " => " << fValue << " = " << calculateValue(date, fValue) << std::endl;
        }
    }
    inputFile.close();  
}
/*
 * @brief Find the Bitcoin value for a given date.
 *
 * This function searches for the Bitcoin value associated 
 * at a specific date in the internal data container. It 
 * takes a 'Date' object as input and tries to find a 
 * matching date in the container. If the date is found, the 
 * corresponding Bitcoin value is returned. If the date is 
 * not found in the container, it enters a loop to decrement 
 * the date until it finds a matching value or reaches the 
 * predefined 'StartDate'. If the date is not found at all, 
 * it prints an error message indicating that there is no 
 * data available for the specified date.
 *
 * @param date The 'Date' for which to find the Bitcoin value.
 * @return The Bitcoin value for the specified date, or 0 if 
 * the date is not found.
 */
float   BitcoinExchange::findValue(Date& date) const
{
    std::map<Date, float>::const_iterator it;
    while (1)
    {
        it = _container.find(date);
        if (it != _container.end()) 
            return (it->second);
        date.decrement();
    }
    return (0);
}            

/**
 * @brief Calculate the total value of a Bitcoin investment.
 *
 * This function calculates the total value of a Bitcoin 
 * investment made on a specified 'inputDate' based on the 
 * provided 'inputAmount'. It uses the 'findValue' function to
 * retrieve the Bitcoin value for the 'inputDate' and then 
 * multiplies it by the 'inputAmount' to determine the total 
 * value of the investment.
 *
 * @param inputDate The date of the Bitcoin investment.
 * @param inputAmount The amount of Bitcoin invested.
 * @return The total value of the Bitcoin investment.
 */
float   BitcoinExchange::calculateValue(Date inputDate, float inputAmount) 
{
    return  (findValue(inputDate) * inputAmount);
}

/**
 * @brief Test the validity of a Date object.
 *
 * This function checks the validity of a given 'Date' 
 * object. If the date is not valid, it prints an error 
 * message indicating that  * the input date is invalid 
 * and returns 0. If the date is valid but falls before 
 * the predefined 'StartDate', it prints an error message 
 * indicating that the input date  * is too early and 
 * also returns 0. If the date is both valid and falls on 
 * or after the 'StartDate', it returns 1 to indicate a 
 * valid date.
 *
 * @param date The 'Date' object to be tested for validity.
 * @return 1 if the date is valid and not too early, 0 otherwise.
 */
int    testDateValidity(std::string& str_date)
{
    Date date = convertStrToDate(str_date);

    if ((date == Date(0, 0, 0)) || !date.valid())
    {
        std::cout << "Error: bad input => " << str_date << std::endl;
        return (0);
    }
    else if (date < BitcoinExchange::StartDate)
    {
        std::cout << "Error: too early input => " << date << std::endl;
        return (0);
    }
    return (1);
}

int testForPipe(std::string text)
{
    char letterToFind = '|';

    // Using find() to search for the first occurrence of the letter
    size_t found = text.find(letterToFind);

    if (found != std::string::npos) {
        return (1);
    }
    std::cout << "Error: illegal line." << std::endl;
    return (0);
}

/**
 * @brief Test the validity of a float value.
 *
 * This function tests the validity of a given float value. 
 * It checks whether the value is positive and within the 
 * range of a signed integer. If the value is negative, it
 * prints an error message indicating that it's not a
 * positive number and returns 0. If the value exceeds the 
 * maximum limit of a signed integer, it prints an error 
 * message indicating that it's too large, and also returns 
 * 0. If the value is valid (positive and within the allowed 
 * range), it returns 1.
 *
 * @param fValue The float value to be tested.
 * @return 0 if the value is not valid, 1 if the value is valid.
 */
int    testValueValidity(std::string& str_value)
{
    const char *cstr;

    cstr = str_value.c_str();
//    printf("!myIsDigit(str_value): %d\t", !myIsDigit(str_value));
//    printf("!consecutiveDigitsAndPoint(cstr): %d\t", !consecutiveDigitsAndPoint(cstr));
//    std::cout << "!consecutiveDigitsAndPoint(cstr): " << !consecutiveDigitsAndPoint(cstr) << "\t";
//    std::cout << "!consecutiveDigits(cstr): " << !consecutiveDigits(cstr) << "\t" << std::endl;
    
    float fValue = std::atof(cstr);
    if (fValue < 0)
    {
        std::cout << "Error: not a positive number => " << str_value << std::endl;
        return (0);
    }
    else if ((!myIsDigit(str_value)) && !consecutiveDigitsAndPoint(cstr) && !consecutiveDigits(cstr))
    {
        std::cout << "Error: bad input => " << str_value << std::endl;
        return (0);
    }
    else if (str_value.length() == 0)
    {
        std::cout << "Error: missing bitcoin amount." << std::endl;
        return (0);
    }
    else if (fValue > 1000)
    {
        std::cout << "Error: too large number." << std::endl;
        return (0);
    }

    return (1);
}

bool    myIsDigit(const std::string &str)
{
    unsigned i;
    int flag_dot = 0;

    for (i = 0; i < str.length()-1; i ++)
    {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.' && str[i] != ' ')
            return (false);
        if (str[i] == '.')
        {
            if (flag_dot == 1)
                return (false);
            else
                flag_dot = 1;
        }
    }
    return (true);
}

/**
 * Check if a string contains consecutive digits separated by 
 * spaces.
 *
 * This function examines the input string `str` and determines 
 * if it contains consecutive digits (0-9)
 * separated by spaces. It returns true if such consecutive 
 * digits are found; otherwise, it returns false.
 * A valid consecutive digits sequence must begin with a digit 
 * and be separated by spaces.
 *
 * @param str A pointer to a C-style string to be checked.
 * @return True if the string contains consecutive digits 
 * separated by spaces, false otherwise.
 *         Also returns false if the input string contains 
 * characters other than digits, spaces, or tabs.
 */
bool consecutiveDigits(const char *str)
{
    int digit_flag = 0; // Flag raised when a digit is encountered after a space or other characters.
    int space_flag = 0; // Flag raised when a space is encountered after a digit.
    int i = 0;

    while (str[i] != '\0')
    {
        if (!isdigit(str[i]) && str[i] != ' ' && str[i] != '\t')
        {
            // If a character other than a digit, space, or tab is encountered, return false.
            return false;
        }
        else if (isdigit(str[i]) && !digit_flag)
        {
            // If a digit is encountered after spaces or other characters, set the digit flag.
            digit_flag = 1;
        }
        else if ((str[i] == ' ') && digit_flag && !space_flag)
        {
            // If a space is encountered after a digit and not already separated, set the space flag.
            space_flag = 1;
        }
        else if (space_flag && isdigit(str[i]))
        {
            // If a space is followed by a digit (without another space in between), return false.
            return false;
        }
        ++i;
    }
    
    // Return true if a valid sequence of consecutive digits is found; otherwise, return false.
    return digit_flag;
}

/**
 * Check if a string contains consecutive digits and, at most, 
 * one decimal point, separated by spaces.
 *
 * This function examines the input string `str` and determines 
 * if it contains consecutive digits (0-9) and, at most, one 
 * decimal point (.) separated by spaces. It returns true if 
 * such a sequence is found; otherwise, it returns false.
 * A valid sequence may start with a digit and should consist 
 * of digits, at most one decimal point, and spaces.
 *
 * @param str A pointer to a C-style string to be checked.
 * @return True if the string contains consecutive digits and, 
 * at most, one decimal point separated by spaces, false 
 * otherwise.
 * Also returns false if the input string contains characters 
 * other than digits, spaces, or a single decimal point.
 */
bool    consecutiveDigitsAndPoint(const char *str)
{
    int i;
    int point_flag;
    int digit_flag;

    if (!str || isEmpty(str))
        return (0);
    i = 0;
    point_flag = 0;
    digit_flag = 0;
    while (str[i] && str[i+1])
    {
        if (!isdigit(str[i]) && str[i] != ' ' && str[i] != '.')
            return (0);
        else if (!isdigit(str[i+1]) && str[i+1] != ' ' && str[i+1] != '.')
            return (0);
        else if ((!isdigit(str[i]) && str[i] != '.') && (isdigit(str[i+1]) || str[i+1] == '.'))
            return (0);
        if (str[i] == '.' || str[i+1] == '.')
        {
            if (point_flag)
                return (0);
            if (str[i] == '.')
                point_flag = 1;
        }
        if (str[i] == '.' && str[i+1] == '.')
            return (0);
        if (!digit_flag && (isdigit(str[i]) || isdigit(str[i+1])))
            digit_flag = 1;
        ++ i;
    }
    return (digit_flag);
}

/**
 * Check if a C-style string consists of only whitespace 
 * characters.
 *
 * This function examines the input string `str` and 
 * determines if it contains only whitespace characters,
 * such as spaces (' '). It returns true if the string 
 * consists solely of whitespace characters; otherwise, 
 * it returns false.
 *
 * @param str A pointer to a C-style string to be checked.
 * @return True if the string consists only of whitespace 
 * characters, false otherwise.
 */
bool    isEmpty(const char *str)
{
    while (*str)
    {
        if (*str != ' ')
            return (false);
        ++ str;
    }
    return (true);
}