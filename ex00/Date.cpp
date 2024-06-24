/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:28    by ekocak            #+#    #+#             */
/*   Updated: 2023/09/02 18:28    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Date.hpp"


Date::Date() : _year(0), _month(0), _day(0)
{}

Date::Date(unsigned theYear, unsigned theMonth, unsigned theDay) 
                : _year(theYear), _month(theMonth), _day(theDay)
{}

Date::Date(const Date &other)
{
    *this = other;    
}

Date& Date::operator=(const Date &other)
{
    if (this != &other)
    {
        _year = other._year;
        _month = other._month;
        _day = other._day;
    }
    return (*this);
}

bool    Date::operator<(const Date& other) const
{
    if (_year > other._year)
        return (false);
    else if (_year == other._year && _month > other._month)
        return (false);
    else if (_year == other._year && _month == other._month && _day >= other._day)
        return (false);
    return (true);
}

bool Date::operator>(const Date& other) const
{
    return (other < *this);
}

bool    Date::operator==(const Date& other) const
{
    return (_year == other._year && _month == other._month && _day == other._day);
}

Date::~Date()
{}

unsigned Date::getYear() const
{
    return (_year); 
}

unsigned Date::getMonth() const
{
    return (_month);
}

unsigned Date::getDay() const
{
    return (_day);
}

/**
 * @brief Decrement the Date object to the previous day.
 *
 * This function decrements the current date represented 
 * by the 'Date' object to the previous day. It takes into 
 * account various factors such as the current day of the
 * month, whether it's a leap year, and the maximum number 
 * of days in each month. If the current day is greater than 
 * 1, it simply decrements the day. If the current day is 1 
 * and the month is March in a leap year, it sets the day to 
 * 29 (since February in leap years has 29 days). If the 
 * current day is 1 and the month is January, it rolls back 
 * to December of the previous year and sets the day to 31. 
 * For other cases, it decrements the month and sets the day 
 * based on whether the month has 31 or 30 days.
 */
void Date::decrement()
{
    if (_day > 1)
        _day --;
    else if (_month == 3 && isLeap())
    {
        _month = 2; 
        _day = 29;
    }
    else if (_month == 3 && !isLeap())
    {
        _month = 2; 
        _day = 28;
    }
    else if (_month == 1)
    {
        _year --;
        _month = 12;
        _day = 31;
    }
    else
    {
        _month --;
        if (_month < 8 && _month%2 == 1)
            _day = 31;
        else if (_month < 8 && _month%2 == 0)
            _day = 30;
        else if (_month%2 == 1)
            _day = 30;
        else
            _day = 31;
    }
}

bool    Date::isLeap() const
{
    if ((_year % 4 == 0 && _year % 100 != 0) || (_year % 400 == 0)) {
        return (true);
    }
    return (false);
}

/**
 * @brief Check the validity of a Date object.
 *
 * This function validates a Date object to ensure that 
 * it represents a valid date. It checks if the stored 
 * values for year, month, and day fall within acceptable 
 * ranges for a valid date. Specifically, it verifies:
 * - The month is between 1 and 12 (inclusive).
 * - The year is a positive integer.
 * - The day is between 1 and 31 (inclusive), considering 
 * - the specific month and leap year rules.
 *
 * For February (month 2), it takes into account whether 
 * it's a leap year or not. February can have 28 or 29 days 
 * depending on leap year status. For other months, it checks 
 * if the day is not greater than 30 for even months and not 
 * greater than 31 for odd months until July. August onwards
 * the rule reverses.
 *
 * If any of these conditions are not met, the function 
 * returns false, indicating an invalid date. Otherwise, 
 * it returns true, signifying that the Date object represents 
 * a valid date.
 *
 * @return True if the Date object is valid, false otherwise.
 */
bool    Date::valid() const
{
    //isdigit no negative, no positive only digit.
/*    if (!isDigit(_day) || !isDigit(_month) || !isDigit(_year))
        return (false);   */
    if (_month < 1 || _month > 12 || _year < 1 || _day < 1 || _day > 31)
        return (false);
    else if (_month == 2 && ((!isLeap() && _day > 28) || (isLeap() && _day > 29)))
        return (false);
    else if (_month < 8 && _month%2 == 0 && _day > 30)
        return (false);
    else if (_month%2 == 1 && _day > 30)
        return (false);
    return (true);
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.getYear() << "-" << std::setw(2) << std::setfill('0') 
                         << date.getMonth() << "-" 
                         << std::setw(2) << std::setfill('0') << date.getDay();
    return os;
}

/**
 * @brief Convert a string to a Date object.
 *
 * This function takes a string in the format "YYYY-MM-DD" 
 * and converts it into a corresponding 'Date' object. It 
 * parses the input string to extract the year, month, and 
 * day components using stringstream tokenizer and string 
 * manipulation. 
 * Then, it converts these components into unsigned integers 
 * and constructs a 'Date' object with them.
 *
 * @param strDate The string containing the date in 
 * "YYYY-MM-DD" format.
 * @return A dynamically allocated 'Date' object representing 
 * the parsed date.
 * @warning The caller is responsible for freeing the memory 
 * allocated for the 'Date' object.
 */
Date    convertStrToDate(std::string strDate)
{
    std::string strYear;
    std::string strMonth;
    std::string strDay;
    std::stringstream lineStream(strDate);
    std::getline(lineStream, strYear, '-');
    std::getline(lineStream, strMonth, '-');
    std::getline(lineStream, strDay, '-');  

    std::istringstream iss1(strYear);
    unsigned year;
    iss1 >> year;

    std::istringstream iss2(strMonth);
    unsigned month;
    iss2 >> month;

    std::istringstream iss3(strDay);
    unsigned day;
    iss3 >> day;
    if (!isDigi(strYear) || !isDigi(strMonth) || !isDigi(strDay))
        return (Date(0, 0, 0));
    return Date(year, month, day);
}

bool    isDigi(std::string str)
{
    if (str.empty())
        return (false);
    unsigned i;
    for (i = 0; i < str.length()-1; i ++)
    {
        if (str[i] < '0' || str[i] > '9')
            return (false);        
    }
    return (true);
}