#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <vector>
#include <sys/types.h>

// O(n^2), Omage(n)
template <typename RandomAccessIterator>
void insertionSort (RandomAccessIterator begin, RandomAccessIterator end);


template <typename RandomAccessIterator>
void quicksort (RandomAccessIterator begin, RandomAccessIterator end);

// Theta(n log(n))
template <typename RandomAccessIterator>
void mergesort (RandomAccessIterator begin, RandomAccessIterator end);

template <typename RandomAccessIterator>
void merge (RandomAccessIterator left_begin, RandomAccessIterator left_end
	  , RandomAccessIterator right_begin, RandomAccessIterator right_end);



template <typename T>
bool less (const T & a, const T & b) { return a < b; };

#include "sorting-algorithms.tpp"

#endif