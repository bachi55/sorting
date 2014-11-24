#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <vector>
#include <sys/types.h>

template <typename T>
void insertionSort (std::vector <T> & array);

// template <typename T>
// void quicksort (std::vector <T> & array);

template <typename T>
bool less (const T & a, const T & b) { return a < b; };

#include "sorting-algorithms.tpp"

#endif