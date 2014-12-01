#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <iterator>
#include <vector>
#include <sys/types.h>

// function to implement the insertion sort algorithm
//
// time complexity: worst case O(n^2), best case O(n)
template <typename RandomAccessIterator>
void insertionSort (RandomAccessIterator begin, RandomAccessIterator end);

// function to implement the quicksort algorithm
//
// time complexity: worst case O(n^2), best case O(n log(n))
// NOTE: the time complexity depends on the choice of the pivot element
template <typename RandomAccessIterator>
void quicksort (RandomAccessIterator begin, RandomAccessIterator end);

// Wrapper to keep the interface for the sorting functions consistent
template <typename RandomAccessIterator>
void mergesort (RandomAccessIterator begin, RandomAccessIterator end);

// function to implement mergesort algorithm
//
// time complexity: Theta(n log(n))
template <typename T>
std::vector <T> _mergesort (std::vector <T> vector);

// function to implement the merge-step
//
// time complexity: Theta(n), where n is left.size + right.size
template <typename T>
std::vector <T> merge (std::vector <T> left, std::vector <T> right);


template <typename T>
bool less (const T & a, const T & b) { return a < b; };

#include "sorting-algorithms.tpp"

// TODO: Why does spezialization not work?
typedef std::vector <int>::iterator RandomAccessIteratorInt;

void insertionSortInt (RandomAccessIteratorInt begin, RandomAccessIteratorInt end);
void quicksortInt (RandomAccessIteratorInt begin, RandomAccessIteratorInt end);
void mergesortInt (RandomAccessIteratorInt begin, RandomAccessIteratorInt end);

#endif