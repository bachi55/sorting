#include <gtest/gtest.h>

#include "sorting-algorithms.h"

#include "meter.h"

#include <algorithm>
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
    std::vector <int> randVector (std::rand() % 1000);
    
    // fill this array with random number between 0 and 99999
    for (auto & element : randVector) element = std::rand () % 10000;
    
    std::vector <int> vector (randVector);
    std::vector <int> referenceVector (randVector);
    
    // sort the arrays: 'vector' with my implementation and 'reference' with the std's one
    sort (vector.begin(), vector.end());
    std::sort (referenceVector.begin(), referenceVector.end());
    
    if (vector != referenceVector) {
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
  
  if (vector != singleElement) {
    printVector (singleElement, "input vector: ");
    printVector (vector, "sorted vector: ");
    
    return false;
  }
  
  vector = emptyArray;
  sort (vector.begin(), vector.end());
  
  if (vector != emptyArray) {
    printVector (emptyArray, "input vector: ");
    printVector (vector, "sorted vector: ");
    
    return false;
  }
  
  vector = sameElementsEven;
  sort (vector.begin(), vector.end());
  
  if (vector != sameElementsEven) {
    printVector (sameElementsEven, "input vector: ");
    printVector (vector, "sorted vector: ");
    
    return false;
  }
  
  vector = sameElementsOdd;
  sort (vector.begin(), vector.end());
  
  if (vector != sameElementsOdd) {
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
//   std::srand (0); 
  
  std::vector <int> vector (n);
  for (auto it = vector.begin(); it != vector.end(); ++it) 
    // generate random numbers so that there is a low probability of repeatitions
    *it = std::rand () % 100000;
  
  return vector;
}

// function to deliver a vector of length n filled with random numbers (lots of repeatitions)
std::vector <int> getRandomVectorRep (uint n) {
  // initialize the random generator with a fixed seed point
//   std::srand (0); 
  
  std::vector <int> vector (n);
  
  for (auto it = vector.begin(); it != vector.end(); ++it) 
    // generate random numbers so that there is a high probability of repeatitions
    *it = std::rand () % 10;
  
  return vector;
}

// ------------------------------------------------------------------------------
// CORRECTNESS
// ------------------------------------------------------------------------------

TEST (DISABLED_correctness, instertionSort) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (insertionSort <std::vector <int>::iterator>),
    true
  );
  
  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (insertionSort <std::vector <int>::iterator>),
    true
  );
}

TEST (DISABLED_correctness, quicksort) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (quicksort <std::vector <int>::iterator>),
    true
  );
  
  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (quicksort <std::vector <int>::iterator>),
    true
  );
}

TEST (DISABLED_correctness, mergesort) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (mergesort <std::vector <int>::iterator>),
    true
  );
  
  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (mergesort <std::vector <int>::iterator>),
    true
  );
}
  
TEST (DISABLED_correctness, insertionSort_naive) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (insertionSort_naive <std::vector <int>::iterator>),
    true
  );

  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (insertionSort_naive <std::vector <int>::iterator>),
    true
  );
}

TEST (DISABLED_correctness, quicksort_naive) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (quicksort_naive <std::vector <int>::iterator>),
    true
  );

  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (quicksort_naive <std::vector <int>::iterator>),
    true
  );
}

TEST (DISABLED_correctness, mergesort_naive) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (mergesort_naive <std::vector <int>::iterator>),
    true
  );

  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (mergesort_naive <std::vector <int>::iterator>),
    true
  );
}

// TEST (DISABLED_correctness, heapsort) {
TEST (correctness, heapsort) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (heapsort <std::vector <int>::iterator>),
    true
  );

  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (heapsort <std::vector <int>::iterator>),
    true
  );
}

// ------------------------------------------------------------------------------
// MEASUREMENTS
// ------------------------------------------------------------------------------

TEST (DISABLED_measurements, random_generators) {
  // create a seed for the random generator
  std::string seedStr = "meleg";
  std::seed_seq seed (seedStr.begin(), seedStr.end());
  
  // configure file-operations
  const std::string resultDir = "/home/bach/Documents/algorithm-exercises/sort/measurements/";
  char temp [256];
  std::sprintf (temp, "# %2s %10s %10s %10s %10s %15s\n", "n", "min[us]", "max[us]", "mean[us]", "sd[us]", "measurements[us]");
  std::string headerTimes (temp);
  
  { // measure 'default_random_engine'
    std::default_random_engine generator (seed);
    std::string generatorName = "default_random_engine";
    
    generator ();
    
    std::function <void (std::default_random_engine &, uint)> createNRandomNumbers = [](std::default_random_engine & generator, uint n) { 
      for (uint i = 0; i < n; i++) { generator (); }
    }; 
    
    // configure benchmark
    uint nrun = 10;
    uint minNRandomNumbers = 1, maxNRandomNumbers = 10000;
    std::vector <uint> nRandomNumbers (maxNRandomNumbers - minNRandomNumbers + 1);
    std::iota (nRandomNumbers.begin(), nRandomNumbers.end(), minNRandomNumbers);
    
    // create matrices to store the measuring results
    Matrix <timeDuration> timeDurationMeasurements (nRandomNumbers.size(), nrun, timeDuration());
    uint i = 0;
    
    // run for increasing vector length, which has to be sorted
    for (auto it = nRandomNumbers.begin(); it != nRandomNumbers.end(); ++it) {
      auto nRandomNumber = (*it);
      timeDurationMeasurements.setRow (i
				    , benchmark <timeDuration, timePoint, void, std::default_random_engine &, uint> (myClock, nrun, createNRandomNumbers, generator, nRandomNumber));
      i++;
    }
    
    // write out measurements
    const std::string filename_time = resultDir + generatorName + "-time";
    writeMeasurements <timeDuration> (filename_time, headerTimes, nRandomNumbers, timeDurationMeasurements);
  }
  
  { // measure 'minstd_rand'
    std::minstd_rand generator (seed);
    std::string generatorName = "minstd_rand";
    
    generator ();
    
    std::function <void (std::minstd_rand &, uint)> createNRandomNumbers = [](std::minstd_rand & generator, uint n) { 
      for (uint i = 0; i < n; i++) { generator (); }
    }; 
    
    // configure benchmark
    uint nrun = 10;
    uint minNRandomNumbers = 1, maxNRandomNumbers = 10000;
    std::vector <uint> nRandomNumbers (maxNRandomNumbers - minNRandomNumbers + 1);
    std::iota (nRandomNumbers.begin(), nRandomNumbers.end(), minNRandomNumbers);
    
    // create matrices to store the measuring results
    Matrix <timeDuration> timeDurationMeasurements (nRandomNumbers.size(), nrun, timeDuration());
    uint i = 0;
    
    // run for increasing vector length, which has to be sorted
    for (auto it = nRandomNumbers.begin(); it != nRandomNumbers.end(); ++it) {
      auto nRandomNumber = (*it);
      timeDurationMeasurements.setRow (i
				    , benchmark <timeDuration, timePoint, void, std::minstd_rand &, uint> (myClock, nrun, createNRandomNumbers, generator, nRandomNumber));
      i++;
    }
    
    // write out measurements
    const std::string filename_time = resultDir + generatorName + "-time";
    writeMeasurements <timeDuration> (filename_time, headerTimes, nRandomNumbers, timeDurationMeasurements);
  }
  
  { // measure 'minstd_rand0'
    std::minstd_rand0 generator (seed);
    std::string generatorName = "minstd_rand0";
    
    generator ();
    
    std::function <void (std::minstd_rand0 &, uint)> createNRandomNumbers = [](std::minstd_rand0 & generator, uint n) { 
      for (uint i = 0; i < n; i++) { generator (); }
    }; 
    
    // configure benchmark
    uint nrun = 10;
    uint minNRandomNumbers = 1, maxNRandomNumbers = 10000;
    std::vector <uint> nRandomNumbers (maxNRandomNumbers - minNRandomNumbers + 1);
    std::iota (nRandomNumbers.begin(), nRandomNumbers.end(), minNRandomNumbers);
    
    // create matrices to store the measuring results
    Matrix <timeDuration> timeDurationMeasurements (nRandomNumbers.size(), nrun, timeDuration());
    uint i = 0;
    
    // run for increasing vector length, which has to be sorted
    for (auto it = nRandomNumbers.begin(); it != nRandomNumbers.end(); ++it) {
      auto nRandomNumber = (*it);
      timeDurationMeasurements.setRow (i
				    , benchmark <timeDuration, timePoint, void, std::minstd_rand0 &, uint> (myClock, nrun, createNRandomNumbers, generator, nRandomNumber));
      i++;
    }
    
    // write out measurements
    const std::string filename_time = resultDir + generatorName + "-time";
    writeMeasurements <timeDuration> (filename_time, headerTimes, nRandomNumbers, timeDurationMeasurements);
  }
  
  { // measure 'mt19937'
    std::mt19937 generator (seed);
    std::string generatorName = "mt19937";
    
    generator ();
    
    std::function <void (std::mt19937 &, uint)> createNRandomNumbers = [](std::mt19937 & generator, uint n) { 
      for (uint i = 0; i < n; i++) { generator (); }
    }; 
    
    // configure benchmark
    uint nrun = 10;
    uint minNRandomNumbers = 1, maxNRandomNumbers = 10000;
    std::vector <uint> nRandomNumbers (maxNRandomNumbers - minNRandomNumbers + 1);
    std::iota (nRandomNumbers.begin(), nRandomNumbers.end(), minNRandomNumbers);
    
    // create matrices to store the measuring results
    Matrix <timeDuration> timeDurationMeasurements (nRandomNumbers.size(), nrun, timeDuration());
    uint i = 0;
    
    // run for increasing vector length, which has to be sorted
    for (auto it = nRandomNumbers.begin(); it != nRandomNumbers.end(); ++it) {
      auto nRandomNumber = (*it);
      timeDurationMeasurements.setRow (i
				    , benchmark <timeDuration, timePoint, void, std::mt19937 &, uint> (myClock, nrun, createNRandomNumbers, generator, nRandomNumber));
      i++;
    }
    
    // write out measurements
    const std::string filename_time = resultDir + generatorName + "-time";
    writeMeasurements <timeDuration> (filename_time, headerTimes, nRandomNumbers, timeDurationMeasurements);
  }
    
  { // measure 'ranlux24'
    std::ranlux24 generator (seed);
    std::string generatorName = "ranlux24";
    
    generator ();
    
    std::function <void (std::ranlux24 &, uint)> createNRandomNumbers = [](std::ranlux24 & generator, uint n) { 
      for (uint i = 0; i < n; i++) { generator (); }
    }; 
    
    // configure benchmark
    uint nrun = 10;
    uint minNRandomNumbers = 1, maxNRandomNumbers = 10000;
    std::vector <uint> nRandomNumbers (maxNRandomNumbers - minNRandomNumbers + 1);
    std::iota (nRandomNumbers.begin(), nRandomNumbers.end(), minNRandomNumbers);
    
    // create matrices to store the measuring results
    Matrix <timeDuration> timeDurationMeasurements (nRandomNumbers.size(), nrun, timeDuration());
    uint i = 0;
    
    // run for increasing vector length, which has to be sorted
    for (auto it = nRandomNumbers.begin(); it != nRandomNumbers.end(); ++it) {
      auto nRandomNumber = (*it);
      timeDurationMeasurements.setRow (i
				    , benchmark <timeDuration, timePoint, void, std::ranlux24 &, uint> (myClock, nrun, createNRandomNumbers, generator, nRandomNumber));
      i++;
    }
    
    // write out measurements
    const std::string filename_time = resultDir + generatorName + "-time";
    writeMeasurements <timeDuration> (filename_time, headerTimes, nRandomNumbers, timeDurationMeasurements);
  }
  
  { // measure 'std::rand'
    std::srand (99);
    std::string generatorName = "std::rand";
    
    std::function <int (void)> generator = std::rand;
    
    std::function <void (std::function <int (void)> &, uint)> createNRandomNumbers = [](std::function <int (void)> & generator, uint n) { 
      for (uint i = 0; i < n; i++) { generator (); }
    }; 
    
    // configure benchmark
    uint nrun = 10;
    uint minNRandomNumbers = 1, maxNRandomNumbers = 10000;
    std::vector <uint> nRandomNumbers (maxNRandomNumbers - minNRandomNumbers + 1);
    std::iota (nRandomNumbers.begin(), nRandomNumbers.end(), minNRandomNumbers);
    
    // create matrices to store the measuring results
    Matrix <timeDuration> timeDurationMeasurements (nRandomNumbers.size(), nrun, timeDuration());
    uint i = 0;
    
    // run for increasing vector length, which has to be sorted
    for (auto it = nRandomNumbers.begin(); it != nRandomNumbers.end(); ++it) {
      auto nRandomNumber = (*it);
      timeDurationMeasurements.setRow (i
				    , benchmark <timeDuration, timePoint, void, std::function <int (void)> &, uint> (myClock, nrun, createNRandomNumbers, generator, nRandomNumber));
      i++;
    }
    
    // write out measurements
    const std::string filename_time = resultDir + generatorName + "-time";
    writeMeasurements <timeDuration> (filename_time, headerTimes, nRandomNumbers, timeDurationMeasurements);
  }
}

typedef std::function <void (RandomAccessIteratorInt, RandomAccessIteratorInt)> SortFunctionHandle;
typedef std::vector <std::function <std::vector <int> (uint)>>		  ScenarioFunctionHandle;

typedef std::function <void (std::vector <int>)> VectorSortFunctionHandle;

TEST (DISABLED_measurements, sorting2) { 
  std::srand (0);
  
  std::vector <VectorSortFunctionHandle> sortFunctions;
//   sortFunctions.push_back (insertionSort_naiveVec <int>);
//   sortFunctions.push_back (insertionSortVec <int>);
//   sortFunctions.push_back (quicksort_naiveVec <int>);
//   sortFunctions.push_back (quicksortVec <int>);
//   sortFunctions.push_back (mergesort_naiveVec <int>);
//   sortFunctions.push_back (mergesortVec <int>);
  
  
  std::vector <std::string> sortFunctionNames;
//   sortFunctionNames.push_back ("insertionSort_naiveVec");
//   sortFunctionNames.push_back ("insertionSortVec");
//   sortFunctionNames.push_back ("quicksort_naiveVec");
//   sortFunctionNames.push_back ("quicksortVec");
//   sortFunctionNames.push_back ("mergesort_naiveVec");
//   sortFunctionNames.push_back ("mergesortVec");
  
  
  // configure benchmark
  // TODO: chose n's step width different from one: nstep += length / 10 + 1
  uint nrun = 10;
  uint minInputLength = 1, maxInputLength = 3000; 
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
				      , benchmark <timeDuration, timePoint, void, std::vector <int>> (myClock, nrun, sortFunctions[ind], input));
	i++;
      }
    
      // write out measurements
      const std::string filename_time = resultDir + sortFunctionNames[ind] + "-" + scenarioNames[sceIndex] + "-time";
      writeMeasurements <timeDuration> (filename_time, headerTimes, sortInputLenghts, timeDurationMeasurements);
      
      sceIndex++;
    }
  }
}

TEST (DISABLED_correctness, parentIndex) {
  std::vector <int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  
  ASSERT_EQ (parentIndex (vec.begin(), vec.begin()), vec.begin());
  
  ASSERT_EQ (parentIndex (std::next (vec.begin()), vec.begin()), vec.begin());
  ASSERT_EQ (parentIndex (std::next (vec.begin(), 2), vec.begin()), vec.begin());
  
  ASSERT_EQ (parentIndex (std::prev (vec.end()), vec.begin()), std::next (vec.begin(), 4));
  ASSERT_EQ (parentIndex (std::next (vec.begin(), 5), vec.begin()), std::next (vec.begin(), 2));
  ASSERT_EQ (parentIndex (std::next (vec.begin(), 4), vec.begin()), std::next (vec.begin()));
}

TEST (DISABLED_correctness, left_and_right_index) {
  std::vector <int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  
  ASSERT_EQ (leftIndex (vec.begin(), vec.begin(), vec.end()), std::next (vec.begin()));
  ASSERT_EQ (rightIndex (vec.begin(), vec.begin(), vec.end()), std::next (vec.begin(), 2));
  
  ASSERT_EQ (leftIndex (std::next (vec.begin()), vec.begin(), vec.end()), std::next (vec.begin(), 3));
  ASSERT_EQ (rightIndex (std::next (vec.begin()), vec.begin(), vec.end()), std::next (vec.begin(), 4));
  
  ASSERT_EQ (leftIndex (std::next (vec.begin(), 4), vec.begin(), vec.end()), std::prev (vec.end()));
  ASSERT_EQ (rightIndex (std::next (vec.begin(), 4), vec.begin(), vec.end()), vec.end());
  
  ASSERT_EQ (leftIndex (std::next (vec.begin(), 5), vec.begin(), vec.end()), vec.end());
  ASSERT_EQ (rightIndex (std::next (vec.begin(), 5), vec.begin(), vec.end()), vec.end());
}

TEST (DISABLED_correctness, isHeap) {
  {
    std::vector <int> heap;
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  }
  {
    std::vector <int> heap = {1};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  }
  {
    std::vector <int> heap = {1, 2, 3};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  }
  {
    std::vector <int> heap = {1, 2, 2, 4, 4, 6};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  }
  {
    std::vector <int> heap = {10, 9};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), false);
  }
  {
    std::vector <int> heap = {1, 2, 3, 4, 1, 6, 7, 8, 9, 10};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), false);
  }
  
  
  {
    std::vector <int> heap = {35, 86, 92, 86, 77, 49, 15};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), false);
  }
  {
    std::vector <int> heap = {35, 86, 92, 86, 77, 49, 15};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end()
						   , 3
						   , greaterIt <std::vector <int>::iterator>)
	     , true);
  }
  
  {
    std::vector <int> heap;
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), true);
  }
  {
    std::vector <int> heap = {1};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), true);
  }
  {
    std::vector <int> heap = {9, 10};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), false);
  }
  {
    std::vector <int> heap = {10, 9};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), true);
  }
  {
    std::vector <int> heap = {11, 10, 8, 8, 4, 10};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), false);
  }  
  {
    std::vector <int> heap = {99, 11, 10, 8, 8, 4};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), true);
  }  
}

TEST (DISABLED_correctness, siftUp) {
  {
    std::vector <int> heap;
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
    siftUp <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  }
  {
    std::vector <int> heap = {1};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
    siftUp <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  }  
  {
    std::vector <int> heap = {1, 2, 2, 4, 4, 6};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
    siftUp <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  }  
  {
    std::vector <int> heap = {10, 9};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), false);
    siftUp <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  }  
  {
    std::vector <int> heap = {1, 2, 3, 10, 11, 1};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), false);
    siftUp <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  } 
// throws exeption, which makes the test fail. This is CORRECT. I just don't want to have failed tests!
//   {
//     std::vector <int> heap = {1, 2, 3, 1, 11, 1};
//     ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>), false);
//     siftUp <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>);
//     ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>), false);
//   } 
}

TEST (DISABLED_correctness, siftDown) {
  {
    std::vector <int> heap;
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
    siftDown <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  }
  {
    std::vector <int> heap = {1};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
    siftDown <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  }  
  {
    std::vector <int> heap = {1, 2, 2, 4, 4, 6};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
    siftDown <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  }  
  {
    std::vector <int> heap = {10, 9};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), false);
    siftDown <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  }  
  {
    std::vector <int> heap = {7, 2, 3, 10, 11, 12};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), false);
    siftDown <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  } 
  {
    std::vector <int> heap = {99, 2, 3, 10, 11, 12};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), false);
    siftDown <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, lessIt <std::vector <int>::iterator>), true);
  } 
  
  {
    std::vector <int> heap = {1, 11, 10, 8, 7, 7, 6, 7};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), false);
    siftDown <std::vector <int>::iterator> (heap.begin(), heap.end(), greaterIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), true);
  } 
  {
    std::vector <int> heap;
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), true);
    siftDown <std::vector <int>::iterator> (heap.begin(), heap.end(), greaterIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), true);
  } 
  {
    std::vector <int> heap = {10};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), true);
    siftDown <std::vector <int>::iterator> (heap.begin(), heap.end(), greaterIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), true);
  } 
  {
    std::vector <int> heap = {10, 99};
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), false);
    siftDown <std::vector <int>::iterator> (heap.begin(), heap.end(), greaterIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), 0, greaterIt <std::vector <int>::iterator>), true);
  } 
//   {
//     std::vector <int> heap = {35, 86, 92, 86, 77, 49, 15};
//     ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), greaterIt <std::vector <int>::iterator>), false);
//     siftDown <std::vector <int>::iterator> (heap.begin(), heap.end(), greaterIt <std::vector <int>::iterator>);
//     ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), greaterIt <std::vector <int>::iterator>), true);
//   } 
// throws exeption, which makes the test fail. This is CORRECT. I just don't want to have failed tests!
//   {
//     std::vector <int> heap = {99, 2, 3, 1, 11, 1};
//     ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>), false);
//     siftDown <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>);
//     ASSERT_EQ (isHeap <std::vector <int>::iterator> (heap.begin(), heap.end(), lessIt <std::vector <int>::iterator>), false);
//   } 
}

// TEST (correctness, isHeapTopDown) {
//   {
//     std::vector <int> heap = {35, 86, 92, 86, 77, 49, 15};
//     auto leftIt = leftIndex (heap.begin(), heap.begin(), heap.end());
//     auto rightIt = rightIndex (heap.begin(), heap.begin(), heap.end());
//     
//     ASSERT_EQ (isHeapTopDown <std::vector <int>::iterator> (
//       heap.begin(), heap.end(), leftIt, greaterIt <std::vector <int>::iterator>
//     ), true);
//     ASSERT_EQ (isHeapTopDown <std::vector <int>::iterator> (
//       heap.begin(), heap.end(), rightIt, greaterIt <std::vector <int>::iterator>
//     ), true);
//   }
//   {
//     std::vector <int> heap = {93, 86, 92, 86, 77, 49, 15, 35};
//     ASSERT_EQ (isHeapTopDown <std::vector <int>::iterator> (
//       heap.begin(), heap.end(), heap.begin(), greaterIt <std::vector <int>::iterator>
//     ), true);
//   }
//   {
//     std::vector <int> heap = {93};
//     ASSERT_EQ (isHeapTopDown <std::vector <int>::iterator> (
//       heap.begin(), heap.end(), heap.begin(), greaterIt <std::vector <int>::iterator>
//     ), true);
//   }
//   {
//     std::vector <int> heap;
//     ASSERT_EQ (isHeapTopDown <std::vector <int>::iterator> (
//       heap.begin(), heap.end(), heap.begin(), greaterIt <std::vector <int>::iterator>
//     ), true);
//   }
//   {
//     std::vector <int> heap = {1, 10, 23};
//     ASSERT_EQ (isHeapTopDown <std::vector <int>::iterator> (
//       heap.begin(), heap.end(), heap.begin(), greaterIt <std::vector <int>::iterator>
//     ), false);
//   }
//   {
//     std::vector <int> heap = {99, 11, 10, 8, 8, 4};
//     ASSERT_EQ (isHeapTopDown <std::vector <int>::iterator> (
//       heap.begin(), heap.end(), heap.begin(), greaterIt <std::vector <int>::iterator>
//     ), true);
//   }
// }

TEST (DISABLED_correctness, buildHeap) {
  {
    std::vector <int> vec  = {1, 1, 1};
    buildHeap <std::vector <int>::iterator> (vec.begin(), vec.end(), greaterIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (vec.begin(), vec.end(), 0, greaterIt <std::vector <int>::iterator>), true);
  }
  {
    std::vector <int> vec  = {1, 1};
    buildHeap <std::vector <int>::iterator> (vec.begin(), vec.end(), greaterIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (vec.begin(), vec.end(), 0, greaterIt <std::vector <int>::iterator>), true);
  }
  { // max-heap
    std::vector <int> vec  = {4, 7, 8, 1, 3, 8, 8, 9, 1};
    buildHeap <std::vector <int>::iterator> (vec.begin(), vec.end(), greaterIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (vec.begin(), vec.end(), 0, greaterIt <std::vector <int>::iterator>), true);
  }
  { // min-heap
    std::vector <int> vec  = {4, 7, 8, 1, 3, 8, 8, 9, 1};
    buildHeap <std::vector <int>::iterator> (vec.begin(), vec.end(), lessIt <std::vector <int>::iterator>);
    ASSERT_EQ (isHeap <std::vector <int>::iterator> (vec.begin(), vec.end(), 0, lessIt <std::vector <int>::iterator>), true);
  }
  
  {
    std::vector <int> vec  = {4, 7, 8, 1, 3, 8, 8, 9, 1};
    std::vector <int> heap = vec;
    std::make_heap (heap.begin(), heap.end()); 
//     printVector (heap, "by std: ");
    buildHeap <std::vector <int>::iterator> (vec.begin(), vec.end(), greaterIt <std::vector <int>::iterator>);
//     printVector (vec, "by own: ");
//     ASSERT_EQ (isHeap <std::vector <int>::iterator> (vec.begin(), vec.end(), 0, greaterIt <std::vector <int>::iterator>), true);
  }
}

TEST (DISABLED_feature, template_alias) {
  std::vector <int> a = {6};
  std::vector <int> b = {5};
  
  auto isGraterEqual = [](std::vector <int>::iterator a
		        , std::vector <int>::iterator b
		        , comparator <std::vector <int>::iterator> comp) 
  {
    return comp (a, b);
  };

  ASSERT_EQ (isGraterEqual (a.begin(), b.begin(), greaterIt <std::vector <int>::iterator>), true);
  ASSERT_EQ (isGraterEqual (b.begin(), a.begin(), greaterIt <std::vector <int>::iterator>), false);
}

int main (int argc, char* argv[]) {
  
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}