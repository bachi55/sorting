#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <iterator>
#include <random>
#include <string>
#include <sys/types.h>
#include <vector>

std::string seedStr = "meleg";
std::seed_seq seed (seedStr.begin(), seedStr.end());
std::mt19937 generator (seed);
// std::minstd_rand0 generator (seed);

typedef std::vector <int>::iterator RandomAccessIteratorInt;


// --------------------------------------------------------------------------------------
// QSORT
// --------------------------------------------------------------------------------------

template <typename T>
void qsortVec(std::vector <T> input) {
  std::sort (input.begin(), input.end());
}

// --------------------------------------------------------------------------------------
// INSERTION SORT
// --------------------------------------------------------------------------------------

// naive implementation
// time complexity: worst case O(n^2), best case O(n)
template <typename RandomAccessIterator>
void insertionSort (RandomAccessIterator begin, RandomAccessIterator end);

template <typename T>
void insertionSortVec(std::vector <T> input) {
  insertionSort (input.begin(), input.end());
}

// small improvement: reduce the amount of swaps, random element as pivot
// time complexity: stil the same but with smaller constants
template <typename RandomAccessIterator>
void insertionSort2 (RandomAccessIterator begin, RandomAccessIterator end);

template <typename T>
void insertionSort2Vec(std::vector <T> input) {
  insertionSort2 (input.begin(), input.end());
}

// --------------------------------------------------------------------------------------
// QUICKSORT
// --------------------------------------------------------------------------------------

// naive implementation
// time complexity: worst case O(n^2), best case O(n log(n))
template <typename RandomAccessIterator>
void quicksort (RandomAccessIterator begin, RandomAccessIterator end);

template <typename T>
void quicksortVec(std::vector <T> input) {
  quicksort (input.begin(), input.end());
}

// small improvement: use insertion sort for small input ~ 80
template <typename RandomAccessIterator>
void quicksort2 (RandomAccessIterator begin, RandomAccessIterator end);

template <typename T>
void quicksort2Vec(std::vector <T> input) {
  quicksort2 (input.begin(), input.end());
}

template <typename T>
T getMedianOfThree (const T* mC);

template <typename RandomAccessIterator>
void quicksort3 (RandomAccessIterator begin, RandomAccessIterator end);

template <typename T>
void quicksort3Vec(std::vector <T> input) {
  quicksort3 (input.begin(), input.end());
}

template <typename RandomAccessIterator>
RandomAccessIterator partition (RandomAccessIterator begin, RandomAccessIterator end, RandomAccessIterator pivotIndex);

template <typename RandomAccessIterator>
void quicksort4 (RandomAccessIterator begin, RandomAccessIterator end);

template <typename T>
void quicksort4Vec(std::vector <T> input) {
  quicksort4 (input.begin(), input.end());
}

template <typename RandomAccessIterator>
void quicksort5 (RandomAccessIterator begin, RandomAccessIterator end);

template <typename T>
void quicksort5Vec(std::vector <T> input) {
  quicksort5 (input.begin(), input.end());
}

template <typename RandomAccessIterator>
void quicksort6 (RandomAccessIterator begin, RandomAccessIterator end);

template <typename T>
void quicksort6Vec(std::vector <T> input) {
  quicksort6 (input.begin(), input.end());
}

// --------------------------------------------------------------------------------------
// MERGESORT
// --------------------------------------------------------------------------------------

// naive implementation
// time complexity: Theta(n log(n))
// NOTE: only the wrapper to keep the interface for the sorting functions consistent
template <typename RandomAccessIterator>
void mergesort (RandomAccessIterator begin, RandomAccessIterator end);

// actuall implementation of the improved mergesort
template <typename T>
std::vector <T> _mergesort (std::vector <T> vector);

// function to implement the merge-step
//
// time complexity: Theta(n), where n is left.size + right.size
template <typename T>
std::vector <T> merge (std::vector <T> left, std::vector <T> right);

template <typename RandomAccessIterator>
void mergesort2 (RandomAccessIterator begin, RandomAccessIterator end);

template <typename RandomAccessIterator>
void merge2 (RandomAccessIterator begin, RandomAccessIterator middle, RandomAccessIterator end);

template <typename RandomAccessIterator>
void mergesort3 (RandomAccessIterator begin, RandomAccessIterator end);

// --------------------------------------------------------------------------------------
// COMPARING
// --------------------------------------------------------------------------------------

template <typename T>
bool less (const T & a, const T & b) { return a < b; };

#include "sorting-algorithms.tpp"

#endif