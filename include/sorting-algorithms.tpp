#include "sorting-algorithms.h"

template <typename T>
void insertionSort (std::vector <T> & array) {
  for (auto i = array.begin() + 1; i != array.end(); ++i) {
    auto j = i;
    while ((j != array.begin()) && less <T> ((*j), (*(j - 1)))) {
      std::swap <T> ((*(j - 1)), (*j));
      --j;
    }
  }
}

// template <typename T>
// void quicksort (std::vector <T> & array) {
//   // needs compare function
//   auto pivotIndex = partition (array, 0);
//   quicksort <T> (array[0 .. pivotIndex]);
//   quicksort <T> (array[pivotIndex + 1 .. end]);
// }

// partition (array, pivotIndex) {
//   swap (array[pivotIndex], (*array.end()));
//   auto pivot = (*array.end());
//   
//   uint s = 0;
//   
//   for (...) {
//     if (array[i] < pivot) {
//       swap (array[s], array[i])
//       s++;
//     }
//   }
//   swap (array[s], (*array.end()))
// }

// template <>
// void insertionSort (std::vector <int> & array);