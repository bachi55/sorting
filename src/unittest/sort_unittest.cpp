#include <gtest/gtest.h>

#include "sorting-algorithms.h"

#include <cstdio>
#include <cstdlib>
#include <string>

// function to check, wether two vectors are equal
auto isEqual = [](const std::vector <int> & v1, const std::vector <int> & v2) { 
  if (v1.size() != v2.size()) return false;
  
  auto it1 = v1.begin();
  auto it2 = v2.begin();
  for (; it1 != v1.end(); ++it1, ++it2) 
    if ((*it1) != (*it2)) return false;
    
  return true;
}; 

// function to print a vector
auto printVector = [](const std::vector <int> & v, const std::string & prefix = "") {
  std::printf ("%s", prefix.c_str());
  for (auto it = v.begin(); it != v.end(); ++it) std::printf ("%i ", (*it));
  std::printf ("\n");
};

// function to feed a sorting algorithm with random algorithm
//
// returns false, if the sorting is wrong (compared to the std::sort implementation)
template <typename RandomAccessIterator> 
bool feedSortAlgoWithRandData (
  const std::function <void (RandomAccessIterator, RandomAccessIterator)> & sort) 
{
  // initialize the random generator with a fixed seed point
  std::srand (0); 
  
  // test for 100 arrays 
  for (uint i = 0; i < 100; i++) {
    // create an array of size 10000
    std::vector <int> randVector (std::rand() % 10000);
    
    // fill this array with random number between 0 and 99999
    for (auto & element : randVector) element = std::rand () % 100000;
    
    std::vector <int> vector (randVector);
    std::vector <int> referenceVector (randVector);
    
    // sort the arrays: 'vector' with my implementation and 'reference' with the std's one
    sort (vector.begin(), vector.end());
    std::sort (referenceVector.begin(), referenceVector.end());
    
    if (! isEqual (vector, referenceVector)) {
      printVector (randVector, "input vector: \t\t\t");
      printVector (referenceVector, "sorted vector (by std::): \t");
      printVector (vector, "sorted vector (by own impl.): \t");
      
      return false;
    }
  }
  
  return true;
}

// function to feed a sorting algorithm with border cases
//
// returns false, if the sorting is wrong (compared to the std::sort implementation)
template <typename RandomAccessIterator> 
bool feedSortAlgoWithBorderCases (
  const std::function <void (RandomAccessIterator, RandomAccessIterator)> & sort) 
{
  // border cases
  std::vector <int> emptyArray;
  std::vector <int> singleElement = {4};
  std::vector <int> sameElementsOdd = {1, 1, 1};
  std::vector <int> sameElementsEven = {1, 1, 1, 1};
  
  std::vector <int> vector = singleElement;
  sort (vector.begin(), vector.end());
  
  if (! isEqual (vector, singleElement)) {
    printVector (singleElement, "input vector: ");
    printVector (vector, "sorted vector: ");
    
    return false;
  }
  
  vector = emptyArray;
  sort (vector.begin(), vector.end());
  
  if (! isEqual (vector, emptyArray)) {
    printVector (emptyArray, "input vector: ");
    printVector (vector, "sorted vector: ");
    
    return false;
  }
  
  vector = sameElementsEven;
  sort (vector.begin(), vector.end());
  
  if (! isEqual (vector, sameElementsEven)) {
    printVector (sameElementsEven, "input vector: ");
    printVector (vector, "sorted vector: ");
    
    return false;
  }
  
  vector = sameElementsOdd;
  sort (vector.begin(), vector.end());
  
  if (! isEqual (vector, sameElementsOdd)) {
    printVector (sameElementsOdd, "input vector: ");
    printVector (vector, "sorted vector: ");
    
    return false;
  }
  
  return true;
}




TEST (sort, instertionSort) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (insertionSort <std::vector <int>::iterator>),
    true
  );
  
  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (insertionSort <std::vector <int>::iterator>),
    true
  );
}

TEST (sort, quicksort) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (quicksort <std::vector <int>::iterator>),
    true
  );
  
  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (quicksort <std::vector <int>::iterator>),
    true
  );
}

TEST (sort, mergesort) {
//   std::vector <int> vector = {9, 4, 2, 4, 1, 5};
//   printVector (vector);
//   mergesort (vector.begin(), vector.end());
//   printVector (vector);
}


int main (int argc, char* argv[]) {
  
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}