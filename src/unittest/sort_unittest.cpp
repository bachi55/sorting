#include <gtest/gtest.h>

#include "sorting-algorithms.h"

#include <cstdio>

TEST (sort, instertionSort) {
  std::vector <int> array = {4, 3, 7, 1, 8, 2};
  insertionSort <int> (array);
  
  ASSERT_EQ (array[0], 1);
  ASSERT_EQ (array[1], 2);
  ASSERT_EQ (array[2], 3);
  ASSERT_EQ (array[3], 4);
  ASSERT_EQ (array[4], 7);
  ASSERT_EQ (array[5], 8);
  
  std::vector <int> array2 = {4};
  insertionSort <int> (array2);
  
  ASSERT_EQ (array2[0], 4);
  
  auto compareVector = [](const std::vector <int> & v1, const std::vector <int> & v2) { 
    if (v1.size() != v2.size()) return false;
    
    auto it1 = v1.begin();
    auto it2 = v2.begin();
    for (; it1 != v1.end(); ++it1, ++it2) 
      if ((*it1) != (*it2)) return false;
      
    return true;
  }; 
  
  std::vector <int> array3 = {9, 0, 1, 2, 1, 1, 1, 5};
  std::vector <int> array3_copy (array3);
  
  insertionSort <int> (array3);
  std::sort (array3_copy.begin(), array3_copy.end());
  
  ASSERT_EQ (compareVector (array3, array3_copy), true);
  
  auto printVector = [](const std::vector <int> & v) {
    for (auto it = v.begin(); it != v.end(); ++it) std::printf ("%i ", (*it));
    std::printf ("\n");
  };
  
  printVector (array3);
  printVector (array3_copy);
  
  // TODO: add randomized tests
  
}

int main (int argc, char* argv[]) {
  
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}