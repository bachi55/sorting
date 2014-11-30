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
  // retrive the iterators container type
  typedef typename std::iterator_traits <RandomAccessIterator>::value_type ValueType;
  
  // TODO: Does this makes a copy of the data?
  std::vector <ValueType> tmp (begin, end);
  auto sortedVector = _mergesort (tmp);
  
  if (std::distance (begin, end) != sortedVector.size())
    throw std::runtime_error ("Error: Merged vector size exceeds input vector size.");
  
  // copy the sorted vector into the given range
  std::copy (sortedVector.begin(), sortedVector.end(), begin);
  // TODO: Would it be better to std::move the data, since it could happen that complex objects are sorted?
  // std::move (sortedVector.begin(), sortedVector.end(), begin);
}

template <typename T>
std::vector <T> _mergesort (std::vector <T> vector) {
  // check for an empty or single element array
  if (vector.size() <= 1) return vector;
  
  // get pointer to the middle element
  auto middle = std::next (
    vector.begin(), std::distance (vector.begin(), vector.end()) / 2
  );
  
  typedef typename std::vector <T> VectorType;
  auto left  = _mergesort (VectorType (vector.begin(), middle));
  auto right = _mergesort (VectorType (middle, vector.end()));
  
  return merge (left, right);
}

template <typename T>
std::vector <T> merge (std::vector <T> left, std::vector <T> right) {
  // create new vector to store the merged data
  std::vector <int> mergedVector (left.size() + right.size());
  
  auto itMergedVector 	= mergedVector.begin()
     , itLeft 		= left.begin()
     , itRight	 	= right.begin();
  
  // merge both vectors and sort them meanwhile
  while ((itLeft != left.end()) && (itRight != right.end())) {
    if (less (*itLeft, *itRight)) {
      *itMergedVector = *itLeft;
      itLeft++;
      itMergedVector++;
    } else {
      *itMergedVector = *itRight;
      itRight++;
      itMergedVector++;
    }
  }
  // empty left vector
  while (itLeft != left.end()) {
    *itMergedVector = *itLeft;
    *itLeft++;
    itMergedVector++;
  }
  // empty right vector
  while (itRight != right.end()) {
    *itMergedVector = *itRight;
    itRight++;
    itMergedVector++;
  }
  
  return mergedVector;
}