In this module I had to demonstrate templated containers, iterators and algorithms in C++98 OOP. It is mandatory to use the standard containers to perform each exercise in this module. Once a container is used, it cannot used for the rest of the module.

I had to structure my files as header files and source files.  

# TASKS

---

**Ex00:**

You have to create a program which outputs the value of a certain amount of bitcoin on a certain date.
This program must use a database in csv format which will represent bitcoin price over time. This database is provided with this subject.
The program will take as input a second database, storing the different prices/dates to evaluate.
The program must respect these rules:
```
• The program name is btc.
• The program must take a file as argument.
• Each line in this file must use the following format: "date | value".
• A valid date will always be in the following format: Year-Month-Day.
• A valid value must be either a float or a positive integer, between 0 and 1000.
```

The program will use the value in the input file. The program should display on the standard output the result of the value multiplied by the exchange rate according to the date indicated in the database. 
If the date used in the input does not exist in the DB then you must use the closest date contained in the DB. Be careful to use the lower date and not the upper one.

---

**Ex01:**

You must create a program with these constraints:
```
• The program name is RPN.
• The program must take an inverted Polish mathematical expression as an argument.
• The numbers used in this operation and passed as arguments will always be less than 10. The calculation itself but also the result do not take into account this rule.
• The program must process this expression and output the correct result on the standard output.
• If an error occurs during the execution of the program an error message should be displayed on the standard output.
• The program must be able to handle operations with these tokens: "+ - / *".
• You must use at least one container in the code to validate this exercise.
```

---

**Ex02:**

You must create a program with these constraints:
```
• The name of the program is PmergeMe.
• The program must be able to use a positive integer sequence as argument.
• The program must use the merge-insert sort algorithm to sort the positive integer sequence.
• You need to use the Ford-Johnson algorithm.
• You must use at least two different containers in the code to validate this exercise. The program must be able to handle at least 3000 different integers.
• On the first line you must display an explicit text followed by the unsorted positive integer sequence.
• On the second line you must display an explicit text followed by the sorted positive integer sequence.
• On the third line you must display an explicit text indicating the time used by the algorithm by specifying the first container used to sort the positive integer sequence.
• On the last line you must display an explicit text indicating the time used by the algorithm by specifying the second container used to sort the positive integer sequence.
```
---
