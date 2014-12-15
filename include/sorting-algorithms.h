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

typedef std::vector <int>::iterator RandomAccessIteratorInt;

template <typename RandomAccessIterator>
void printRange (RandomAccessIterator begin, RandomAccessIterator end) {
  for (auto it = begin; it != end; ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}


// --------------------------------------------------------------------------------------
// COMPARING
// --------------------------------------------------------------------------------------

template <typename RandomAccessIterator>
using comparator = std::function <bool (RandomAccessIterator, RandomAccessIterator)>;

template <typename T>
bool less (const T & a, const T & b) { return a < b; };

template <typename T>
bool greater (const T & a, const T & b) { return a > b; };

// template <typename T>
// bool lessEqual (const T & a, const T & b) { return a <= b; };

template <typename RandomAccessIterator>
bool greaterEqual (RandomAccessIterator a, RandomAccessIterator b) { return *a >= *b; };

template <typename RandomAccessIterator>
bool lessEqual (RandomAccessIterator a, RandomAccessIterator b) { return *a <= *b; };

template <typename RandomAccessIterator>
bool lessIt (RandomAccessIterator a, RandomAccessIterator b) { return *a < *b; };

template <typename RandomAccessIterator>
bool greaterIt (RandomAccessIterator a, RandomAccessIterator b) { return *a > *b; };

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
void insertionSort_naive (RandomAccessIterator begin, RandomAccessIterator end);

template <typename T>
void insertionSort_naiveVec(std::vector <T> input) {
  insertionSort_naive (input.begin(), input.end());
}

// small improvement compared to 'naive': reduce the amount of swaps, random element as pivot
// time complexity: stil the same but with smaller constants
template <typename RandomAccessIterator>
void insertionSort (RandomAccessIterator begin, RandomAccessIterator end);

template <typename T>
void insertionSortVec(std::vector <T> input) {
  insertionSort (input.begin(), input.end());
}

// --------------------------------------------------------------------------------------
// QUICKSORT
// --------------------------------------------------------------------------------------

// naive implementation
// time complexity: worst case O(n^2), best case O(n log(n))
template <typename RandomAccessIterator>
void quicksort_naive (RandomAccessIterator begin, RandomAccessIterator end);

template <typename T>
void quicksort_naiveVec(std::vector <T> input) {
  quicksort_naive (input.begin(), input.end());
}

// improvements of the naive implementation
// * small inputs will be sorted with insertion-sort
// * the pivot-element is chosen randomly
// * partition is implemented as fat-partition
template <typename RandomAccessIterator>
void quicksort (RandomAccessIterator begin, RandomAccessIterator end);

template <typename T>
void quicksortVec(std::vector <T> input) {
  quicksort (input.begin(), input.end());
}

// --------------------------------------------------------------------------------------
// MERGESORT
// --------------------------------------------------------------------------------------

// naive implementation
// time complexity: Theta(n log(n))
// NOTE: only the wrapper to keep the interface for the sorting functions consistent
template <typename RandomAccessIterator>
void mergesort_naive (RandomAccessIterator begin, RandomAccessIterator end);

// actuall implementation of the improved mergesort
template <typename T>
std::vector <T> _mergesort_naive (std::vector <T> vector);

// function to implement the merge-step
// time complexity: Theta(n), where n is left.size + right.size
// memory complexity: Theta(n), where n is left.size + right.size
template <typename T>
std::vector <T> merge (std::vector <T> left, std::vector <T> right);

template <typename T>
void mergesort_naiveVec (std::vector <T> input) {
  mergesort_naive (input.begin(), input.end());
}

// improvements of the naive implementation
// * small inputs are sorted with insertion-sort
// * less memory allocations -> memory complexity O(2n)
// * merge2 is implemented in-place
template <typename RandomAccessIterator>
void mergesort (RandomAccessIterator begin, RandomAccessIterator end);

template <typename T>
void mergesortVec (std::vector <T> input) {
  mergesort (input.begin(), input.end());
}

// in-place merge
template <typename RandomAccessIterator>
void merge2 (RandomAccessIterator begin, RandomAccessIterator middle, RandomAccessIterator end);

// --------------------------------------------------------------------------------------
// HEAP-Sort
// --------------------------------------------------------------------------------------

// This function returns an iterator to the parent of an given element within a heap.
//
// NOTE: parent of the root is the root itself
template <typename RandomAccessIterator>
RandomAccessIterator parentIndex (RandomAccessIterator it, RandomAccessIterator begin) {
  // root's parent is root
  if (it == begin) return begin;
  return std::next (begin, (std::distance (begin, it) - 1) / 2);
}

// This function returns an interator to the left child of an given element within a heap.
// 
// NOTE: If there is now left child, the end of the range will be returned.
template <typename RandomAccessIterator>
RandomAccessIterator leftIndex (RandomAccessIterator it
			      , RandomAccessIterator begin
			      , RandomAccessIterator end)
{ 
  auto leftIt = std::next (begin, std::distance (begin, it) * 2 + 1);
  if (leftIt >= end) return end;
  else 		     return leftIt;
}

// This function returns an interator to the right child of an given element within a heap
//
// NOTE: If there is now right child, the end of the range will be returned.
template <typename RandomAccessIterator>
RandomAccessIterator rightIndex (RandomAccessIterator it
			       , RandomAccessIterator begin
			       , RandomAccessIterator end)
{ 
  auto rightIt = std::next (begin, std::distance (begin, it) * 2 + 2);
  if (rightIt >= end) return end;
  else 		      return rightIt;
}

template <typename RandomAccessIterator>
bool isHeap (RandomAccessIterator begin
	   , RandomAccessIterator end
	   , size_t offsetFromRoot = 0
	   , comparator <RandomAccessIterator> comp = lessIt) 
{  
  
  for (auto it = std::next (begin, offsetFromRoot); it < end; ++it) 
    // exchange argument order comp (a, b) -> comp (b, a)
    // it makes the use of an strict weak ordering possible
    // for example: <(a, b) becomes >(a, b) by exchange
    if (comp (it, parentIndex (it, begin))) return false;
  return true;
}

// This function repairs a heap if a new element has been added in the end
template <typename RandomAccessIterator>
void siftUp (RandomAccessIterator begin
	   , RandomAccessIterator end
	   , comparator <RandomAccessIterator> comp = lessIt)
{
  // nothing to repair in an empty or single element heap
  if (std::distance (begin, end) <= 1) return;
  
  // pre condition: excluding the last element in the range, it should be a heap
  if (! isHeap <RandomAccessIterator> (begin, std::prev (end), 0, comp))
    throw std::invalid_argument ("Error: Cannot repair heap, since not only the last element is broken.");
    
  auto newElementIt = std::prev (end);
  while (true) {
    if (newElementIt == begin) break;
    auto parentIt = parentIndex (newElementIt, begin);
    if (comp (parentIt, newElementIt)) break;
    std::swap (*parentIt, *newElementIt);
    newElementIt = parentIt;
  }
  
  // post condition: the heap should be repaired now
//   if (! isHeap <RandomAccessIterator> (begin, end, 0, comp))
//     throw std::invalid_argument ("Error: Heap is stil broken after 'siftUp'.");
}

// This function repairs a heap if a new element has been added in the beginning 
template <typename RandomAccessIterator>
void siftDown (RandomAccessIterator begin
	     , RandomAccessIterator end
	     , comparator <RandomAccessIterator> comp = lessIt)
{
  // nothing to repair in an empty or single element heap
  if (std::distance (begin, end) <= 1) return;
  
  // pre condition: left and right branch of root should be a heap
  if (! isHeap <RandomAccessIterator> (begin, end, 3, comp))
    throw std::invalid_argument ("Error: Cannot repair heap, since not only the root is broken.");
  
  auto newElementIt = begin;
  while (true) {
    auto leftIt = leftIndex (newElementIt, begin, end);
    // end of the heap could have been reached
    if (leftIt == end) break;
    
    auto rightIt = std::next (leftIt);
    // chose element to swap with the new element
    if (comp (rightIt, leftIt) && (rightIt != end)) leftIt = rightIt;
    // Is the heap property already repaired?
    if (comp (newElementIt, leftIt)) break;
    
    std::swap (*leftIt, *newElementIt);
    newElementIt = leftIt;
  }
  
  // post condition: the heap should be repaired now
//   if (! isHeap <RandomAccessIterator> (begin, end, 0, comp)) 
//     throw std::invalid_argument ("Error: Heap is stil broken after 'siftDown'.");  
}

template <typename RandomAccessIterator>
void buildHeap (RandomAccessIterator begin, RandomAccessIterator end
	      , comparator <RandomAccessIterator> comp = lessIt)
{
  // an empty or single element heap is already a max-heap
  if (std::distance (begin, end) <= 1) return;
  
  for (auto it = begin; it != std::next (end); ++it)
    siftUp <RandomAccessIterator> (begin, it, comp);
  
  if (! isHeap <RandomAccessIterator> (begin, end, 0, comp)) 
    throw std::invalid_argument ("Error: Failed to build up the heap."); 
}

template <typename RandomAccessIterator>
void heapsort (RandomAccessIterator begin, RandomAccessIterator end) {
  // check for an empty or single element array
  if (std::distance (begin, end) <= 1) return;
  
  buildHeap <RandomAccessIterator> (begin, end, greaterIt <RandomAccessIterator>);
  
  for (auto it = std::prev (end, 1); it != begin; --it) {
    // swap biggest value to the end of the range
    std::swap (*begin, *it);
    siftDown <RandomAccessIterator> (begin, it, greaterIt <RandomAccessIterator>);
  }
  
//   if (! isSorted (vector)) throw exeption;
}

// --------------------------------------------------------------------------------------
// INTROSORT
// --------------------------------------------------------------------------------------

// template <typename RandomAccessIterator>
// void introsort (RandomAccessIterator begin, RandomAccessIterator end) {
//   auto introsort_ = [](RandomAccessIterator begin, RandomAccessIterator end, size_t recursionDepth) {
//     while (std::distance (begin, end) > 30) {
//       if (recursionDepth == 0) { 
// 	heapsort (begin, end);
// 	return;
//       }
//       auto pivot = random();
//       // make partition
//       auto left = 0 ... pivot;
//       auto right = pivot ... $;
//       // make left always shorter
//       if (left.size() > right.size()) swap (left, right)
//       introsort_ (left, recursionDepth - 1);
//       array = right;
//     }
//   };
//   introsort_ (begin, end, 2 * log2 (std::distance (begin, end)));
//   insertionSort (begin, end);
// }
#include "sorting-algorithms.tpp"

#endif