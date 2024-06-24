/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:28    by ekocak            #+#    #+#             */
/*   Updated: 2023/09/02 18:28    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATE_HPP
# define DATE_HPP

#include <ostream>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

/**
 * @class Date
 * @brief Represents a date with year, month, and day components.
 *
 * This class provides functionalities to represent and manipulate dates.
 * It ensures date validity by considering leap years and the maximum
 * number of days in each month.
 */
class Date {
private:
  unsigned _year;
  unsigned _month;
  unsigned _day;

public:
  /**
   * @brief Default constructor.
   *
   * Initializes a Date object with default values (year, month, day set to 0).
   */
  Date();

  /**
   * @brief Constructor with specific year, month, and day.
   *
   * Constructs a Date object with the provided year, month, and day values.
   * @param theYear The year as an unsigned integer.
   * @param theMonth The month as an unsigned integer (1-12).
   * @param theDay The day as an unsigned integer (1-31, considering leap years).
   */
  Date(unsigned theYear, unsigned theMonth, unsigned theDay);

  /**
   * @brief Copy constructor.
   *
   * Creates a deep copy of another Date object.
   * @param other The Date object to be copied.
   */
  Date(const Date& other);

  /**
   * @brief Assignment operator.
   *
   * Assigns the values of another Date object to the current object.
   * @param other The Date object to be assigned from.
   * @return A reference to the modified Date object.
   */
  Date& operator=(const Date& other);

  /**
   * @brief Less-than operator overload.
   *
   * Compares two Date objects and returns true if the current object is less than the other object.
   * @param other The Date object to be compared with.
   * @return True if the current object is less than the other object, false otherwise.
   */
  bool operator<(const Date& other) const;

  /**
   * @brief Greater-than operator overload.
   *
   * Compares two Date objects and returns true if the current object is greater than the other object.
   * (Leverages the less-than operator for efficiency)
   * @param other The Date object to be compared with.
   * @return True if the current object is greater than the other object, false otherwise.
   */
  bool operator>(const Date& other) const { return (other < *this); }

  /**
   * @brief Equality operator overload.
   *
   * Compares two Date objects and returns true if they represent the same date.
   * @param other The Date object to be compared with.
   * @return True if the objects represent the same date, false otherwise.
   */
  bool operator==(const Date& other) const;

  /**
   * @brief Destructor.
   */
  ~Date();

  /**
   * @brief Get the year of the Date object.
   *
   * @return The year as an unsigned integer.
   */
  unsigned getYear() const;

  /**
   * @brief Get the month of the Date object.
   *
   * @return The month as an unsigned integer (1-12).
   */
  unsigned getMonth() const;

  /**
   * @brief Get the day of the Date object.
   *
   * @return The day as an unsigned integer (1-31, considering leap years).
   */
  unsigned getDay() const;

  /**
   * @brief Decrement the Date object to the previous day.
   *
   * This function decrements the current date to the previous day,
   * considering leap years and the maximum number of days in each month.
   */
  void decrement();

  /**
   * @brief Check if the current Date object represents a leap year.
   *
   * @return True if it's a leap year, false otherwise.
   */
    bool        isLeap() const;

  /**
   * @brief Check the validity of the date.
   *
   * @return True if it's a valid date, false otherwise.
   */
    bool        valid() const;
};

/**
 * @brief Overload the stream insertion operator for Date objects.
 *
 * This function overloads the << operator to allow Date objects 
 * to be directly inserted into output streams. It formats the 
 * Date object as "YYYY-MM-DD" and sends it to the provided 
 * output stream.
 *
 * @param os The output stream where the Date object will be inserted.
 * @param date The Date object to be inserted into the stream.
 * @return A reference to the output stream after insertion.
 */
std::ostream& operator<<(std::ostream& os, const Date& date);

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
Date    convertStrToDate(std::string strDate);

/**
 * @brief Check if a string contains only digits.
 *
 * This function checks if the given string consists entirely 
 * of numerical digits (0-9). It iterates through each character 
 * of the string and verifies that it falls within the ASCII 
 * range of numerical digits.
 *
 * @param str The string to be checked for digit characters.
 * @return True if the string contains only digits, false otherwise.
 */
bool    isDigi(std::string str);

#endif