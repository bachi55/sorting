#include "sorting-algorithms.h"

template <typename RandomAccessIterator>
void insertionSort (RandomAccessIterator begin, RandomAccessIterator end) {
  // check for an empty or single element array
  if (std::distance (begin, end) <= 1) return;
  
  for (auto i = begin + 1; i != end; ++i) {
    auto j = i;
    while ((j != begin) && less (*j, (*(j - 1)))) {
      std::swap ((*(j - 1)), *j);
      --j;
    }
  }
}

template <typename RandomAccessIterator>
void insertionSort2 (RandomAccessIterator begin, RandomAccessIterator end) {
  // check for an empty or single element array
  if (std::distance (begin, end) <= 1) return;
  
  for (auto i = begin + 1; i != end; ++i) {
    auto j = i;
    auto tmp = *i;
    while ((j != begin) && less (tmp, (*(j - 1)))) {
      // shift value from the left to the current index
      *j = *(j - 1);
      --j;
    }
    *j = tmp;
  }
}

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
void quicksort2 (RandomAccessIterator begin, RandomAccessIterator end) {
  // small inputs are faster with insertion sort
  if (std::distance (begin, end) <= 30) {
    insertionSort2 (begin, end);
    return;
  }
  
  // get a random generated pivot element
  auto pivot = *(begin + (generator() % std::distance (begin, end)));
  
  // repeat until the counter reaches each other
  auto i = begin, j = (end - 1);
  do {
    // find pair to change
    while (less ((*i), pivot)) ++i; // left --> right
    while (less (pivot, (*j))) --j; // right --> left
    
    if (i < j) {
      std::swap ((*i), (*j));
      ++i;
      --j;
    } else if (i == j) {
      ++i;
      --j;
      break;
    }
  } while (i <= j);
 
  if (begin < j)  quicksort2 (begin, j + 1);
  if (i < (end - 1)) quicksort2 (i, end);
}

template <typename RandomAccessIterator>
void quicksort6 (RandomAccessIterator begin, RandomAccessIterator end) {
  // small inputs are faster with insertion sort
  if (std::distance (begin, end) <= 30) {
    insertionSort2 (begin, end);
    return;
  }
  
  // get a random generated pivot element
  auto pivot = *(begin + (generator() % std::distance (begin, end)));
  
  // implements fat-partition
  auto i = begin, lt = begin, gt = (end - 1);
  while (i <= gt) {
    if (less (*i, pivot)) { // left --> right
      std::swap (*lt, *i);
      ++i;
      ++lt;
    } else if (less (pivot, (*i))) { // right --> left
      std::swap (*gt, *i);
      --gt;
    } else {
      ++i;
    }
  }    
 
  quicksort6 (begin, lt + 1);
  quicksort6 (gt, end);
}

template <typename T>
T getMedianOfThree (const T* mC) {
    if ((mC[0] >= mC[1]) && (mC[0] >= mC[2])) {
    if (mC[1] >= mC[2]) return mC[1];
    else 		return mC[2];
  } 
  else if ((mC[1] >= mC[0]) && (mC[1] >= mC[2])) {
    if (mC[0] >= mC[2]) return mC[0];
    else 		return mC[2];
  }
  else /*((mC[2] >= mC[0]) && (mC[2] >= mC[1]))*/ { 
    if (mC[1] >= mC[0]) return mC[1];
    else 		return mC[0];
  }
}


template <typename RandomAccessIterator>
void quicksort3 (RandomAccessIterator begin, RandomAccessIterator end) {
  if (std::distance (begin, end) <= 1) { return; }
  
  auto pivotIndex = begin;
  auto partitionIndex = partition (begin, end, pivotIndex);
  quicksort3 (begin, partitionIndex);
  quicksort3 (partitionIndex, end);
}

template <typename RandomAccessIterator>
RandomAccessIterator partition (RandomAccessIterator begin, RandomAccessIterator end, RandomAccessIterator pivotIndex) {
  auto pivot = *pivotIndex;
  std::swap (*pivotIndex, *(end - 1));
  // iterator pointing to end of the lower-than-pivot part
  auto lt = begin; 
  for (auto it = begin; it != (end - 1); ++it) {
    if (less (*it, pivot)) {
      std::swap (*it, *lt);
      ++lt;
    }
  }
  std::swap (*lt, *(end - 1));  // Move pivot to its final place
  return ((lt + 1) == (end) ? lt : lt + 1);
}

template <typename RandomAccessIterator>
void quicksort4 (RandomAccessIterator begin, RandomAccessIterator end) {
  // small inputs are faster with insertion sort
  if (std::distance (begin, end) <= 30) {
    insertionSort2 (begin, end);
    return;
  }
  
  auto pivotIndex = begin;
  auto partitionIndex = partition (begin, end, pivotIndex);
  quicksort4 (begin, partitionIndex);
  quicksort4 (partitionIndex, end);
}

template <typename RandomAccessIterator>
void quicksort5 (RandomAccessIterator begin, RandomAccessIterator end) {
  // small inputs are faster with insertion sort
  if (std::distance (begin, end) <= 30) {
    insertionSort2 (begin, end);
    return;
  }
  
  auto pivotIndex = begin + (generator() % std::distance (begin, end));
  auto partitionIndex = partition (begin, end, pivotIndex);
  quicksort5 (begin, partitionIndex);
  quicksort5 (partitionIndex, end);
}



template <typename RandomAccessIterator>
void mergesort (RandomAccessIterator begin, RandomAccessIterator end) {
  // retrive the iterators container type
  typedef typename std::iterator_traits <RandomAccessIterator>::value_type ValueType;
  
  std::vector <ValueType> res (begin, end);
  auto sortedVector = _mergesort (res);
  
//   if (std::distance (begin, end) != sortedVector.size())
//     throw std::runtime_error ("Error: Merged vector size exceeds input vector size.");
  
  // copy the sorted vector into the given range
  std::copy (sortedVector.begin(), sortedVector.end(), begin);
}

template <typename T>
std::vector <T> _mergesort (std::vector <T> vector) {
  // check for an empty or single element array
  // TODO: on SMALL INPUTS the insertionSort is faster ~ 80
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
  // TODO: give mergedVector as parameter
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

template <typename RandomAccessIterator>
void mergesort2 (RandomAccessIterator begin, RandomAccessIterator end) {
  // check for an empty or single element array
  if (std::distance (begin, end) <= 1)
    return;
  
  // get pointer to the middle element
  auto middle = std::next (begin, std::distance (begin, end) / 2);
  
  // recursive descend to the left
  mergesort2 (begin, middle);
  // recursive descend to the right
  mergesort2 (middle, end);
  
  merge2 (begin, middle, end);
}

template <typename RandomAccessIterator>
void merge2 (RandomAccessIterator begin, RandomAccessIterator middle, RandomAccessIterator end) {
  typedef typename std::iterator_traits <RandomAccessIterator>::value_type ValueType;
  std::vector <ValueType> tmp (begin, end);
  
  // iterators for tmp vector
  auto itLeft 		= tmp.begin()
     , tmpMiddle	= std::next (itLeft, std::distance (begin, middle))
     , itRight 		= tmpMiddle
     , tmpEnd		= tmp.end();
     
  // iterator for the output vector (actually the input = inplace)
  auto i = begin;
  
  // merge both vectors and sort them meanwhile
  while ((itLeft != tmpMiddle) && (itRight != tmpEnd)) {
    if (less (*itLeft, *itRight)) {
      *i = *itLeft;
      itLeft++;
      i++;
    } else {
      *i = *itRight;
      itRight++;
      i++;
    }
  }
  // empty left vector
  while (itLeft != tmpMiddle) {
    *i = *itLeft;
    *itLeft++;
    i++;
  }
  // empty right vector
  while (itRight != tmpEnd) {
    *i = *itRight;
    itRight++;
    i++;
  }
}

template <typename RandomAccessIterator>
void mergesort3 (RandomAccessIterator begin, RandomAccessIterator end) {
  // check for an empty or single element array
  if (std::distance (begin, end) <= 1)
    return;
  
  // get pointer to the middle element
  auto middle = std::next (begin, std::distance (begin, end) / 2);
  
  // recursive descend to the left
  mergesort2 (begin, middle);
  // recursive descend to the right
  mergesort2 (middle, end);
  
  std::inplace_merge (begin, middle, end);
}
