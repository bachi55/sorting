#include "sorting-algorithms.h"

template <typename RandomAccessIterator>
void insertionSort (RandomAccessIterator begin, RandomAccessIterator end) {
  // check for an empty or single element array
  if (std::distance (begin, end) <= 1) return;
  
  for (auto i = begin + 1; i != end; ++i) {
    auto j = i;
    while ((j != begin) && less ((*j), (*(j - 1)))) {
      std::swap ((*(j - 1)), (*j));
      --j;
    }
  }
}

// template <typename T>
// void insertionSort2 (std::vector <T> & array) {
//   for (auto i = array.begin() + 1; i != array.end(); ++i) {
//     auto j = i;
//     auto tmp = array[i];
//     while ((j != array.begin()) && less <T> (tmp, (*(j - 1)))) {
//       array[j-1] = array[j];
//       --j;
//     }
//     array[j] = tmp;
//   }
// }

template <typename RandomAccessIterator>
void quicksort (RandomAccessIterator begin, RandomAccessIterator end) {
  // check for an empty or single element array
  if (std::distance (begin, end) <= 1) return;
  
  // get pivot element
  auto pivot = *begin;
  
  auto i = begin, j = (end - 1);
  // repeat until the counter reaches each other
  do {
    // find pair to change
    while (less ((*i), pivot)) ++i; // left --> right
    while (less (pivot, (*j))) --j; // right --> left
    
    if (i < j) {
      std::swap ((*i), (*j));
      ++i;
      --j;
    }
    // 
    else if (i == j) {
      ++i;
      --j;
      break;
    }
  } while (i <= j);
 
  if (begin < j)  quicksort (begin, j + 1);
  if (i < (end - 1)) quicksort (i, end);
}

template <typename RandomAccessIterator>
void mergesort (RandomAccessIterator begin, RandomAccessIterator end) {
  // check for an empty or single element array
  if (std::distance (begin, end) <= 1) return;
  
  for (auto it = begin; it != end; ++it) { std::printf ("%i ", *it); } std::printf ("\n");
  
  auto middle = std::distance (begin, end) / 2;
  
  // set iterator for the ranges of the left and right vector parts
  // NOTE: end always points one element after the last element (like in std::)
  auto left_begin = begin;
  auto left_end = (left_begin + middle) + 1;
  auto right_begin = left_end;
  auto right_end = end;
  
  mergesort (left_begin, left_end);
  mergesort (right_begin, right_end);
  
  merge (left_begin, left_end, right_begin, right_end);
  
  return;
}

template <typename RandomAccessIterator>
void merge (RandomAccessIterator left_begin, RandomAccessIterator left_end
	  , RandomAccessIterator right_begin, RandomAccessIterator right_end) 
{
  return;
}

// template <typename RandomAccessIterator>
// void mergesort (RandomAccessIterator begin, RandomAccessIterator end) {
//   // check for empty array
//   if (begin == end) return;
//   
//   auto merge = [](RandomAccessIterator left, RandomAccessIterator right) {
//     auto res = 
//     auto i = 0;
//     auto j = 0;
//     while (){
//       if (less (left[i], right[j]))
//     }
//   };
//   
//   auto middle = std::distance (end, begin) / 2;
//   auto leftArray = mergesort (begin, middle);
//   auto rightArray = mergesort (middle, end);
//   auto merge = (leftArray, rightArray);
// }