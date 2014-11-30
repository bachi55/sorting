#include "sorting-algorithms.h"

typedef std::vector <int>::iterator RandomAccessIteratorInt;

void insertionSortInt (RandomAccessIteratorInt begin, RandomAccessIteratorInt end) {
  std::vector <int> tmp (begin, end);
  insertionSort (tmp.begin(), tmp.end());
}

void quicksortInt (RandomAccessIteratorInt begin, RandomAccessIteratorInt end) {
  std::vector <int> tmp (begin, end);
  quicksort (tmp.begin(), tmp.end());
}

void mergesortInt (RandomAccessIteratorInt begin, RandomAccessIteratorInt end) {
  std::vector <int> tmp (begin, end);
  mergesort (tmp.begin(), tmp.end());
}