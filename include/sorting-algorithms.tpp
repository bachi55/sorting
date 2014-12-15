#include "sorting-algorithms.h"

template <typename RandomAccessIterator>
void insertionSort (RandomAccessIterator begin, RandomAccessIterator end) {
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
void insertionSort_naive (RandomAccessIterator begin, RandomAccessIterator end) {
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
void quicksort (RandomAccessIterator begin, RandomAccessIterator end) {
  // small inputs are faster with insertion sort
  if (std::distance (begin, end) <= 30) {
    insertionSort (begin, end);
    return;
  }
  
  // get a random generated pivot element
  auto pivot = *(begin + (generator() % std::distance (begin, end)));
  
  // perform fat-partition
  auto i = begin	// current element
    , lt = begin	// points to the end of the lower-than part
    , gt = (end - 1);	// points to the begin of the greater-than part
    
  while (i <= gt) {
    if (less (*i, pivot)) { // left --> right: move *i to the lower-than part
      std::swap (*lt, *i);
      ++i;
      ++lt;
    } else if (less (pivot, (*i))) { // right --> left: move *i to the greater-than part
      std::swap (*gt, *i);
      --gt;
    } else { // *i remains in the equal part
      ++i;
    }
  }    
 
  quicksort (begin, lt + 1);
  quicksort (gt, end);
}

template <typename RandomAccessIterator>
void quicksort_naive (RandomAccessIterator begin, RandomAccessIterator end) {
  // check for an empty or single element array
  if (std::distance (begin, end) <= 1) return;
  
  // get pivot element
  auto pivot = *begin;
  
  // perform partition
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
 
  if (begin < j)  quicksort_naive (begin, j + 1);
  if (i < (end - 1)) quicksort_naive (i, end);
}

template <typename RandomAccessIterator>
void mergesort_naive (RandomAccessIterator begin, RandomAccessIterator end) {
  // retrive the iterators container type
  typedef typename std::iterator_traits <RandomAccessIterator>::value_type ValueType;
  
  std::vector <ValueType> res (begin, end);
  auto sortedVector = _mergesort_naive (res);
  
  // copy the sorted vector into the given range
  std::copy (sortedVector.begin(), sortedVector.end(), begin);
}

template <typename T>
std::vector <T> _mergesort_naive (std::vector <T> vector) {
  // check for an empty or single element array
  if (vector.size() <= 1) return vector;
  
  // get pointer to the middle element
  auto middle = std::next (
    vector.begin(), std::distance (vector.begin(), vector.end()) / 2
  );
  
  typedef typename std::vector <T> VectorType;
  auto left  = _mergesort_naive (VectorType (vector.begin(), middle));
  auto right = _mergesort_naive (VectorType (middle, vector.end()));
  
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

template <typename RandomAccessIterator>
void mergesort (RandomAccessIterator begin, RandomAccessIterator end) {
  // check for an empty or single element array
  if (std::distance (begin, end) <= 1)
    return;
  
  // get pointer to the middle element
  auto middle = std::next (begin, std::distance (begin, end) / 2);
  
  // recursive descend to the left
  mergesort (begin, middle);
  // recursive descend to the right
  mergesort (middle, end);
  
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