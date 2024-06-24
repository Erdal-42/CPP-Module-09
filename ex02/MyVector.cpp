/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyVector.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekocak@student.42.org.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:47    by ekocak            #+#    #+#             */
/*   Updated: 2023/09/25 11:47    by ekocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MyVector.hpp"

MyVector::MyVector()
{}

MyVector::MyVector(const MyVector& other) : std::vector<unsigned>(other) 
{}


/**
 * Assignment operator for MyVector.
 *
 * This operator overloads the assignment operator for MyVector to perform
 * a deep copy of the elements from the provided MyVector `other`.
 * It ensures that self-assignment does not occur.
 *
 * @param other Another MyVector to copy data from.
 * @return A reference to the modified MyVector after assignment.
 */

MyVector &MyVector::operator=(const MyVector& other)
{
    if (this != &other)
    {
        std::vector<unsigned>::operator=(other);
    }
    return (*this);
}

MyVector::~MyVector()
{}

/**
 * Populate MyVector from an array of C-style strings.
 *
 * This function populates the MyVector with unsigned integers by converting
 * each element from the array of C-style strings `argv` to an unsigned integer
 * using the custom function `ft_atou`, and then adding it to the vector.
 *
 * @param argc The number of elements in the `argv` array.
 * @param argv An array of C-style strings containing elements to be added to MyVector.
 */

void    MyVector::populateMyVector(int argc, char **argv)
{
    int i = 1;
    int num;

    while (i < argc)
    {
        num = ft_atou(argv[i]);
        push_back(num);
        i ++;
    }
}

/**
 * Sort a portion of MyVector using the merge sort algorithm.
 *
 * This function recursively divides the MyVector range into smaller 
 * subranges, sorts them, and then merges the sorted subranges to 7
 * achieve the final sorted result.
 *
 * @param left The index of the left boundary of the range to be sorted.
 * @param right The index of the right boundary of the range to be sorted.
 */ 
void    MyVector::mergeSortMyVector(unsigned left, unsigned right) 
{ 
    if (left < right) 
    {
        unsigned middle = (left + right) / 2; // this middle = left + right / 2 is why we are testing left < right

        mergeSortMyVector(left, middle);
        mergeSortMyVector(middle + 1, right); // this +1 is why we are testing left < right

        mergeMyVector(left, middle, right);
    }
}


/**
 * Merge two subvectors of MyVector.
 *
 * This function merges two subvectors of MyVector. The subvectors are defined
 * by the indices `left`, `middle`, and `right`. It combines the two subvectors
 * in a sorted order, assuming they are already individually sorted. The result 
 * is loaded onto the object this function implements on. 
 *
 * @param left The index of the first element in the left subvector.
 * @param middle The index of the last element in the left subvector.
 * @param right The index of the last element in the right subvector.
 */
void    MyVector::mergeMyVector(unsigned left, unsigned middle, unsigned right) 
{
    unsigned n1 = middle - left + 1;        
    unsigned n2 = right - middle;          

    MyVector leftHalf;
    MyVector rightHalf;
    
    for (unsigned i = 0; i < n1; i ++)
        leftHalf.push_back((*this)[left + i]);
    for (unsigned i = 0; i < n2; i ++)
        rightHalf.push_back((*this)[middle + 1 + i]);

    unsigned i = 0, j = 0, k = left;
    while (i < n1 && j < n2) 
    {
        if (leftHalf[i] <= rightHalf[j]) 
        {
            (*this)[k] = leftHalf[i];
            i ++;
        } 
        else 
        {
            (*this)[k] = rightHalf[j];
            j ++;
        }
        k ++;
    }
    while (i < n1) {
        (*this)[k] = leftHalf[i];
        i ++;
        k ++;
    }
    while (j < n2) {
        (*this)[k] = rightHalf[j];
        j ++;
        k ++;
    }
}        

/**
 * Perform a binary search on the sorted MyVector.
 *
 * This function performs a binary search on the sorted MyVector to find the 
 * position where the specified value should be inserted to maintain the 
 * sorted order. The binary search algorithm helps find the lower bound of the 
 * value.
 *
 * @param value The value to be searched for.
 * @return The index where the specified value should be inserted while 
 * maintaining the sorted order.
 */
unsigned    MyVector::binarySearch(const unsigned value, int right) 
{
    int left = 0;
    
    while (left <= right) 
    {
        int middle = (left + right) / 2;
        if ((*this)[middle] < value) 
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }
    return left;
}

/**
 * Perform a binary insertion of an unsigned value into MyVector.
 *
 * This function first finds the insertion point for the given unsigned 
 * value using a binary search, and then inserts the value at the 
 * appropriate iterator position in the vector to maintain sorted order.
 *
 * @param value The unsigned value to be inserted into MyVector.
 */
void    MyVector::binaryInsert(unsigned& value, int right)
{
    int insertionPoint = binarySearch(value, right);
    insert(begin() + insertionPoint, value);
}

PairsVector::PairsVector()
{}

PairsVector::PairsVector(const PairsVector& other)
{
    _containerPV = other._containerPV;
}

std::vector<std::pair<unsigned, unsigned> >  PairsVector::getContainerPV() const
{
    return _containerPV;
}

PairsVector::~PairsVector()
{}

MyVector    &PairsVector::getContainerMain()
{
    return _containerMain;
}

MyVector    &PairsVector::getContainerPend()
{
    return _containerPend;
}

/**
 *
 * This function populates the PairsVector `_containerPV` with pairs of unsigned integers
 * by converting pairs of elements from the array of C-style strings `argv` to unsigned integers
* * using the custom function `ft_atou`, and then adding each pair to the vector.
 *
 * @param argc The number of elements in the `argv` array.
 * @param argv An array of C-style strings containing pairs of elements to be added to PairsVector.
 */
void    PairsVector::populatePairsVector(int argc, char **argv)
{
    int i = 1;
    int num1, num2;

    while ((i + 1) < argc)
    {
        num1 = ft_atou(argv[i]);
        num2 = ft_atou(argv[i+1]);
        _containerPV.push_back(std::make_pair(num1, num2));
        i += 2;
    }
}

/**
 * Sort individual pairs in the PairsVector container.
 *
 * This function iterates through the pairs in the PairsVector 
 * container and ensures that the first element of each pair is 
 * less than or equal to the second element. If the first element 
 * is greater than the second element, it swaps them to maintain 
 * the order.
 */
void    PairsVector::sortIndividualPairs()
{
    unsigned i;
    unsigned temp;

    i = 0;
    unsigned size = _containerPV.size();
    while (i < size)
    {
        if (_containerPV[i].first > _containerPV[i].second) 
        {
            temp = _containerPV[i].first;
            _containerPV[i].first = _containerPV[i].second;
            _containerPV[i].second = temp;
        }
        i ++;
    }
}

/**
 * Sort the PairsVector using the merge sort algorithm.
 *
 * This function sorts the PairsVector using the merge sort algorithm.
 * It divides the vector into two halves, recursively sorts each half, 
 * and then merges the two sorted halves into one.
 *
 * @param left The index of the left boundary of the range to be sorted.
 * @param right The index of the right boundary of the range to be sorted.
 */
void    PairsVector::mergeSortPairsContainer(unsigned left, unsigned right)
{
    if (left < right)
    {
        unsigned    middle = left + (right - left) / 2;
        mergeSortPairsContainer(left, middle);
        mergeSortPairsContainer(middle + 1, right);
        mergePairsContainer(left, middle, right);
    }
}

/**
 * Merge two subarrays of PairsVector::_containerPV.
 *
 * This function merges two subarrays of PairsVector::_containerPV. 
 * The first subarray is PairsVector::_containerPV[left..middle], 
 * and the second subarray is PairsVector::_containerPV[middle+1..right].
 *
 * @param left The index of the first element of the first subarray.
 * @param middle The index of the last element of the first subarray.
 * @param right The index of the last element of the second subarray.
 */
void    PairsVector::mergePairsContainer(unsigned left, unsigned middle, unsigned right)
{
    unsigned n1 = middle - left + 1;
    unsigned n2 = right - middle;

    std::vector<std::pair<unsigned, unsigned> > leftHalf(n1);
    std::vector<std::pair<unsigned, unsigned> > rightHalf(n2);

    for (unsigned i = 0; i < n1; i ++)
        leftHalf[i] = _containerPV[left + i];
    for (unsigned i = 0; i < n2; i++)
        rightHalf[i] = _containerPV[middle + 1 + i];

    unsigned i = 0, j = 0, k = left;
    while (i < n1 && j < n2) 
    {
        if (leftHalf[i].second <= rightHalf[j].second) 
        {
            _containerPV[k] = leftHalf[i];
            i++;
        } 
        else 
        {
            _containerPV[k] = rightHalf[j];
            j++;
        }
        k++;
    } 
    while (i < n1) {
        _containerPV[k] = leftHalf[i];
        i++;
        k++;
    }
    while (j < n2) {
        _containerPV[k] = rightHalf[j];
        j++;
        k++;
    }
}

/**
 * Generate main and pending MyVectors from the PairsVector container.
 *
 * This function generates two MyVector containers, `main` and 
 * `pending`, by extracting elements from the PairsVector `_containerPV`. 
 * The first elements of each pair are pushed into the `pending` 
 * MyVector, and the second elements are pushed into the `main` MyVector.
 * The resulting MyVectors are then assigned to the respective class 
 * members, `_containerMain` and `_containerPend`.
 */
void    PairsVector::generateMainAndPending()
{
    MyVector    main;
    MyVector    pending;
    unsigned    i;
    unsigned    size;

    i = 0;
    size = _containerPV.size();
    while (i < size)
    {
        pending.push_back(_containerPV[i].first);    
        main.push_back(_containerPV[i].second);
        i ++;
    }
    _containerMain = main;
    _containerPend = pending;
}


void    PairsVector::insertPendingToMainContainer()
{
    unsigned    insert_index;       
    unsigned    jacobsthal_index;   
    unsigned    insertion_range_in_main;
    unsigned    prev_jacobsthal_index = 0;  
    int n = 3;
    
    jacobsthal_index = calculateJacobsthal(n) - 1;
    insertion_range_in_main = jacobsthal_index;
    _containerMain.insert(_containerMain.begin(), _containerPend[0]);
    while (_containerMain.size() < (2 * _containerPend.size()))
    {
        if (jacobsthal_index < _containerPend.size())
            insert_index = jacobsthal_index;
        else
            insert_index = _containerPend.size() - 1;
        while (insert_index != prev_jacobsthal_index)
        {                                             
            _containerMain.binaryInsert(_containerPend[insert_index], insertion_range_in_main ++);
            insert_index --;
        }
        prev_jacobsthal_index = jacobsthal_index;
        n ++;
        jacobsthal_index = calculateJacobsthal(n) - 1;
        insertion_range_in_main += jacobsthal_index - prev_jacobsthal_index;
        if (insertion_range_in_main > _containerMain.size() - 1)
            insertion_range_in_main = _containerMain.size() - 1;
    }
}

unsigned    PairsVector::binarySearch(const unsigned value, int right) 
{
    int left = 0;
    if ((unsigned)right > _containerMain.size() - 1)
        right = _containerMain.size() - 1;

    while (left <= right) 
    {
        int middle = (left + right) / 2;
        if (_containerMain[middle] < value) 
            left = middle + 1;
        else
            right = middle - 1;
    }
    return left;
}

std::ostream &operator<<(std::ostream &os, const MyVector& vec) 
{
    const std::vector<unsigned>& containerRef = vec;
    std::vector<unsigned>::const_iterator iter = containerRef.begin();
    if (iter != containerRef.end()) {
        os << *iter;
        ++ iter;
    }
    unsigned i = 1;
    for (; iter != containerRef.end() && i < 36; ++ iter) {
        os << " " << *iter;
        ++ i;
    }
    if (i < containerRef.size())
        std::cout << "..";
    return os;
}

void printContainerPV(const std::vector<std::pair<unsigned, unsigned> >& containerPV) 
{
    int i = 0;

    for (std::vector<std::pair<unsigned, unsigned> >::const_iterator it = containerPV.begin(); it != containerPV.end() && i < 36; ++it) 
    {
        const std::pair<unsigned, unsigned>& pair = *it;
        std::cout << "[" << pair.first << "," << pair.second << "] ";
        i ++;
    }
    std::cout << std::endl;
}