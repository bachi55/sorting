#include <gtest/gtest.h>

#include "sorting-algorithms.h"

#include "meter.h"

#include <cstdio>
#include <cstdlib>
#include <string>

// function to check, wether two vectors are equal
auto isEqual = [](const std::vector <int> & v1, const std::vector <int> & v2) { 
  return std::equal (v1.begin(), v1.end(), v2.begin());
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

// function to deliver a sorted vector of length n filled with random numbers 
std::vector <int> getSortedRandomVector (uint n) {
  // initialize the random generator with a fixed seed point
  std::srand (0); 
  
  std::vector <int> vector (n);
  for (auto it = vector.begin(); it != vector.end(); ++it) 
    // generate random numbers so that there is a low probability of repeatitions
    *it = std::rand () % (100 * n);
  
  // sort the vector with the std::sort ascend (true) or descend (false)
  std::sort (vector.begin(), vector.end());
  
  return vector;
}

std::vector <int> getSortedRandomVectorAsc (uint n) {
  auto vector = getSortedRandomVector (n);
  return vector;
}

std::vector <int> getSortedRandomVectorDes (uint n) {
  auto vector = getSortedRandomVector(n);
  std::reverse (vector.begin(), vector.end());
  return vector;
}

// function to deliver a vector of length n filled with random numbers 
std::vector <int> getRandomVector (uint n) {
  // initialize the random generator with a fixed seed point
  std::srand (0); 
  
  std::vector <int> vector (n);
  for (auto it = vector.begin(); it != vector.end(); ++it) 
    // generate random numbers so that there is a low probability of repeatitions
    *it = std::rand () % (n * 10);
  
  return vector;
}

// function to deliver a vector of length n filled with random numbers (lots of repeatitions)
std::vector <int> getRandomVectorRep (uint n) {
  // initialize the random generator with a fixed seed point
  std::srand (0); 
  
  std::vector <int> vector (n);
  
  for (auto it = vector.begin(); it != vector.end(); ++it) 
    // generate random numbers so that there is a high probability of repeatitions
    *it = std::rand () % (n / 10 + 1);
  
  return vector;
}

// ------------------------------------------------------------------------------
// CORRECTNESS
// ------------------------------------------------------------------------------

TEST (correctness, instertionSort) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (insertionSort <std::vector <int>::iterator>),
    true
  );
  
  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (insertionSort <std::vector <int>::iterator>),
    true
  );
}

TEST (correctness, quicksort) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (quicksort <std::vector <int>::iterator>),
    true
  );
  
  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (quicksort <std::vector <int>::iterator>),
    true
  );
}

TEST (correctness, mergesort) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (mergesort <std::vector <int>::iterator>),
    true
  );
  
  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (mergesort <std::vector <int>::iterator>),
    true
  );
}

// ------------------------------------------------------------------------------
// MEASUREMENTS
// ------------------------------------------------------------------------------

typedef std::function <void (RandomAccessIteratorInt, RandomAccessIteratorInt)> SortFunctionHandle;
typedef std::vector <std::function <std::vector <int> (uint)>>			ScenarioFunctionHandle;

TEST (measurements, sorting) {  
  std::vector <SortFunctionHandle> sortFunctions;
  sortFunctions.push_back (insertionSortInt);
  sortFunctions.push_back (quicksortInt);
  sortFunctions.push_back (mergesortInt);
  std::vector <std::string> sortFunctionNames;
  sortFunctionNames.push_back ("insertionSort");
  sortFunctionNames.push_back ("quicksort");
  sortFunctionNames.push_back ("mergesort");
  
  // configure benchmark
  uint nrun = 10;
  uint minInputLength = 10, maxInputLength = 1000; 
  std::vector <uint> sortInputLenghts (maxInputLength - minInputLength + 1);
  std::iota (sortInputLenghts.begin(), sortInputLenghts.end(), minInputLength);
  
  std::vector <std::string> scenarioNames = {"sorted", "inv_sorted", "permuted", "repeated_elements"};
  // NOTE: here it is fixed, that 'int' values are sorted
  ScenarioFunctionHandle scenarioFunctions;
  scenarioFunctions.push_back (getSortedRandomVectorAsc);
  scenarioFunctions.push_back (getSortedRandomVectorDes);
  scenarioFunctions.push_back (getRandomVector);
  scenarioFunctions.push_back (getRandomVectorRep);
  
  // configure file-operations
  const std::string resultDir = "/home/bach/Documents/algorithm-exercises/sort/measurements/";
  
  char temp [256];
  std::sprintf (temp, "# %2s %10s %10s %10s %10s %15s\n", "n", "min[us]", "max[us]", "mean[us]", "sd[us]", "measurements[us]");
  std::string headerTimes (temp);
  std::sprintf (temp, "# %2s %10s %10s %10s %10s %15s\n", "n", "min[cyc]", "max[cyc]", "mean[cyc]", "sd[cyc]", "measurements[cyc]");
  std::string headerCycles (temp);
  
  // run for every sorting algorithm
  for (uint ind = 0; ind < sortFunctions.size(); ind++) {
    uint sceIndex = 0;
    
    std::printf ("sort function %i/%i\n", ind + 1, sortFunctions.size());
    
    // run for every scenario
    for (auto & sceFct : scenarioFunctions) {
      
      std::printf ("scenario %i/%i\n", sceIndex + 1, scenarioFunctions.size());
      
      // create matrices to store the measuring results
      Matrix <timeDuration> timeDurationMeasurements (sortInputLenghts.size(), nrun, timeDuration());
      Matrix <uint64_t> cycleMeasurements (sortInputLenghts.size(), nrun, 0);
      uint i = 0;
      
      // run for increasing vector length, which has to be sorted
      for (auto it = sortInputLenghts.begin(); it != sortInputLenghts.end(); ++it) {
	auto input = sceFct (*it);
	timeDurationMeasurements.setRow (i
				      , benchmark <timeDuration, timePoint, void, RandomAccessIteratorInt, RandomAccessIteratorInt> (myClock, nrun, sortFunctions[ind], input.begin(), input.end()));
	cycleMeasurements.setRow (i
				, benchmark <ulong, ulong, void, RandomAccessIteratorInt, RandomAccessIteratorInt> (myCycles, nrun, sortFunctions[ind], input.begin(), input.end()));
	i++;
      }
    
      // write out measurements
      const std::string filename_time = resultDir + sortFunctionNames[ind] + "-" + scenarioNames[sceIndex] + "-time";
      writeMeasurements <timeDuration> (filename_time, headerTimes, sortInputLenghts, timeDurationMeasurements);
      
      const std::string filename_cycles = resultDir + sortFunctionNames[ind] + "-" + scenarioNames[sceIndex] + "-cycles";
      writeMeasurements <uint64_t> (filename_cycles, headerCycles, sortInputLenghts, cycleMeasurements);
      
      sceIndex++;
    }
  }
}



// TEST (correctness, vector_generators) {
//   auto vector = getRandomVectorRep (10);
//   printVector (vector);
// }

int main (int argc, char* argv[]) {
  
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}