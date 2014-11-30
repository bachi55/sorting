//TODO: Come clear about the return type of function for complex objects (for ex. like matrices). 
// 	Keywords are: const reference, rvalue moving, const access, copies
//TODO: Come clear about moving-constructor
//	Key questions: Do I need to delete something? When the constructor will be called?

#ifndef MATRIX_H
#define MATRIX_H

#include <cstdio>
#include <utility>
#include <stdexcept>
#include <sys/types.h>
#include <vector>

#include "mytypes.h"


template <class T>
class Matrix {
  uint _nrow, _ncol;
  std::vector <T> _data;
  bool _init; 
  
public:
  // TODO: What would be a useful default constructor?
//   Matrix ();
  // constructs an not initialized matrix
  //
  // The matrix has a give size, but no data. 
  // TODO: how to make this efficient? Do not copy to much?
  Matrix (uint nrow, uint ncol, const T & initElement);
  
  // constructor _move_ data from vector: requires c++11 or later
  Matrix (uint nrow, uint ncol, std::vector <T> && data);
  
  // constructor _copy_ data from vector 
  Matrix (uint nrow, uint ncol, const std::vector <T> & data);
  
  // print matrix
  void printMatrix ();
  
  // access operator (e.g. matrix (i,j) = 0 --> lvalue) 
  T & operator() (uint row, uint col); 
  
  // access operator (for access from constant objects)
  const T & operator() (uint row, uint col) const; 
  
  // matrix multiplication
  Matrix <T> operator* (const Matrix <T> & rhs);
  
  // extract a row from the matrix
  //
  // TODO: prevent copying data
  std::vector <T> getRow (uint row) const;  
  
  // set a row of the matrix
  //
  // TODO: prevent unessary copying of data
  void setRow (uint row, std::vector<T> && newData);
  
 
  // check whether the matrix is empty
  bool isEmpty () const { return (_nrow * _nrow) == 0; };
  
  // get number of rows
  uint rows () const { return _nrow; };
  
  // get number of cols
  uint cols () const { return _ncol; };
  
};

template <typename T>
Matrix <T> createIdentityMatrix (uint nrow);


#include "matrix.tpp"

#endif