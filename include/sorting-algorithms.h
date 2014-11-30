#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <iterator>
#include <vector>
#include <sys/types.h>

// O(n^2), Omage(n)
template <typename RandomAccessIterator>
void insertionSort (RandomAccessIterator begin, RandomAccessIterator end);


template <typename RandomAccessIterator>
void quicksort (RandomAccessIterator begin, RandomAccessIterator end);

// Theta(n log(n))
// Wrapper to keep the interface for the sorting functions consistent
template <typename RandomAccessIterator>
void mergesort (RandomAccessIterator begin, RandomAccessIterator end);

// Function to implement mergesort
template <typename T>
std::vector <T> _mergesort (std::vector <T> vector);

// Function to implement the merge-step
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