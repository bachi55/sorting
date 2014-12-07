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
  for (uint i = 0; i < 200; i++) {
    // create an array of size 10000
    std::vector <int> randVector (std::rand() % 10000);
    
    // fill this array with random number between 0 and 99999
    for (auto & element : randVector) element = std::rand () % 100000;
    
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
  
TEST (correctness, insertionSort2) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (insertionSort2 <std::vector <int>::iterator>),
    true
  );

  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (insertionSort2 <std::vector <int>::iterator>),
    true
  );
}

TEST (correctness, quicksort2) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (quicksort2 <std::vector <int>::iterator>),
    true
  );

  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (quicksort2 <std::vector <int>::iterator>),
    true
  );
}

TEST (correctness, quicksort3) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (quicksort3 <std::vector <int>::iterator>),
    true
  );

  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (quicksort3 <std::vector <int>::iterator>),
    true
  );
}

TEST (correctness, quicksort4) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (quicksort4 <std::vector <int>::iterator>),
    true
  );

  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (quicksort4 <std::vector <int>::iterator>),
    true
  );
}

TEST (correctness, quicksort5) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (quicksort5 <std::vector <int>::iterator>),
    true
  );

  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (quicksort5 <std::vector <int>::iterator>),
    true
  );
}

TEST (correctness, quicksort6) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (quicksort6 <std::vector <int>::iterator>),
    true
  );

  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (quicksort6 <std::vector <int>::iterator>),
    true
  );
}

TEST (correctness, mergesort2) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (mergesort2 <std::vector <int>::iterator>),
    true
  );

  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (mergesort2 <std::vector <int>::iterator>),
    true
  );
}

TEST (correctness, mergesort3) {
  ASSERT_EQ (
    feedSortAlgoWithBorderCases <std::vector <int>::iterator> (mergesort3 <std::vector <int>::iterator>),
    true
  );

  ASSERT_EQ (
    feedSortAlgoWithRandData <std::vector <int>::iterator> (mergesort3 <std::vector <int>::iterator>),
    true
  );
}

TEST (correctness, getMedianOfThree) {
  {
    uint mC[] = {1, 1, 1};
    ASSERT_EQ (getMedianOfThree <uint> (mC), 1);
  }
  {
    uint mC[] = {1, 2, 1};
    ASSERT_EQ (getMedianOfThree <uint> (mC), 1);
  }
  {
    uint mC[] = {2, 1, 1};
    ASSERT_EQ (getMedianOfThree <uint> (mC), 1);
  }
  {
    uint mC[] = {1, 1, 2};
    ASSERT_EQ (getMedianOfThree <uint> (mC), 1);
  }
  
  {
    uint mC[] = {2, 1, 2};
    ASSERT_EQ (getMedianOfThree <uint> (mC), 2);
  }
  {
    uint mC[] = {2, 2, 1};
    ASSERT_EQ (getMedianOfThree <uint> (mC), 2);
  }
  {
    uint mC[] = {1, 2, 2};
    ASSERT_EQ (getMedianOfThree <uint> (mC), 2);
  }
  
  {
    uint mC[] = {1, 2, 3};
    ASSERT_EQ (getMedianOfThree <uint> (mC), 2);
  }
  {
    uint mC[] = {3, 2, 1};
    ASSERT_EQ (getMedianOfThree <uint> (mC), 2);
  }
  {
    uint mC[] = {2, 3, 1};
    ASSERT_EQ (getMedianOfThree <uint> (mC), 2);
  }
  {
    uint mC[] = {1, 3, 2};
    ASSERT_EQ (getMedianOfThree <uint> (mC), 2);
  }
}

TEST (correctness, partition) {
  {
    std::vector <int> v = {3, 1, 2, 4, 5};
    auto p = partition (v.begin(), v.end(), v.begin());
    
    std::printf ("partition index %lu \n", p - v.begin()) ;
    std::printf ("partition value %i \n", *p); 
    
    printVector (std::vector <int> (v.begin(), p));
    printVector (std::vector <int> (p, v.end()));
  }
  
  {
    std::vector <int> v = {8, 1, 1, 4, 5};
    auto p = partition (v.begin(), v.end(), v.begin());
    
    std::printf ("partition index %lu \n", p - v.begin()) ;
    std::printf ("partition value %i \n", *p); 
    
    printVector (std::vector <int> (v.begin(), p));
    printVector (std::vector <int> (p, v.end()));
  }
  
  {
    std::vector <int> v = {1, 9, 2, 7, 2, 9};
    auto p = partition (v.begin(), v.end(), v.begin());
    
    std::printf ("partition index %lu \n", p - v.begin()) ;
    std::printf ("partition value %i \n", *p); 
    
    printVector (std::vector <int> (v.begin(), p));
    printVector (std::vector <int> (p, v.end()));
  }
  
  {
    std::vector <int> v = {6, 7, 2, 8, 2, 9};
    auto p = partition (v.begin(), v.end(), v.begin());
    
    std::printf ("partition index %lu \n", p - v.begin()) ;
    std::printf ("partition value %i \n", *p); 
    
    printVector (std::vector <int> (v.begin(), p));
    printVector (std::vector <int> (p, v.end()));
  }
  
  {
    std::vector <int> v = {1, 2, 2, 9, 9};
    auto p = partition (v.begin(), v.end(), v.begin());
    
    std::printf ("partition index %lu \n", p - v.begin()) ;
    std::printf ("partition value %i \n", *p); 
    
    printVector (std::vector <int> (v.begin(), p));
    printVector (std::vector <int> (p, v.end()));
  }
//   ASSERT_EQ (*partition (v.begin(), v.end(), v.begin()), *(v.begin() + 2));
}



// ------------------------------------------------------------------------------
// MEASUREMENTS
// ------------------------------------------------------------------------------



TEST (measurements, random_generators) {
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

TEST (measurements, sorting2) { 
  std::srand (0);
  
  std::vector <VectorSortFunctionHandle> sortFunctions;
//   sortFunctions.push_back (insertionSortVec <int>);
//   sortFunctions.push_back (insertionSort2Vec <int>);
//   sortFunctions.push_back (quicksortVec <int>);
//   sortFunctions.push_back (quicksort2Vec <int>);
  sortFunctions.push_back (quicksort3Vec <int>);
//   sortFunctions.push_back (quicksort4Vec <int>);
//   sortFunctions.push_back (quicksort5Vec <int>);
  sortFunctions.push_back (quicksort6Vec <int>);
//   sortFunctions.push_back (qsortVec <int>);
//   sortFunctions.push_back (mergesortVec <int>);
//   sortFunctions.push_back (mergesort2Vec <int>);
//   sortFunctions.push_back (mergesort3Vec <int>);
  
  
  std::vector <std::string> sortFunctionNames;
//   sortFunctionNames.push_back ("insertionSortVec");
//   sortFunctionNames.push_back ("insertionSort2Vec");
//   sortFunctionNames.push_back ("quicksortVec");
//   sortFunctionNames.push_back ("quicksort2Vec");
  sortFunctionNames.push_back ("quicksort3Vec");
//   sortFunctionNames.push_back ("quicksort4Vec");
//   sortFunctionNames.push_back ("quicksort5Vec");
  sortFunctionNames.push_back ("quicksort6Vec");
//   sortFunctionNames.push_back ("qsortVec");
//   sortFunctionNames.push_back ("mergesortVec");
//   sortFunctionNames.push_back ("mergesort2Vec");
//   sortFunctionNames.push_back ("mergesort3Vec");
  
  
  // configure benchmark
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

int main (int argc, char* argv[]) {
  
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}