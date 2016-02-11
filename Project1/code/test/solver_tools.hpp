// Project 1: Solver Tool Class
// PHY 480 Computational Physics
// Authors: Noah Green and Curtis Rau
// Last Modified by: Noah Green
// Date Last Modified: 2/6/2016

#ifndef SOLVER_TOOLS_HPP
#define SOLVER_TOOLS_HPP

#include "vector_cls.hpp"

//-----------------------------------------------------------------------------
// Class Declaration
//-----------------------------------------------------------------------------

class solver{

public:
  // default constructor
  solver( double (*source)( double ), double (*solution)( double )
	  , double interval, int num );
  // destructor
  ~solver();
  // Gaussian elimination algorithm specifically for poisson equation: by Noah Green
  void gauss_elim_poisson();
  // Gaussian elimination algorithm for general tridiagonal matrix
  void gauss_elim_tridiag();
  // LU decomposition solver using armadillo: by Noah Green
  void lu_decompadillo();
  

private:
  // number of steps in function discretization
  int _N;
  double _interval;
  // source term function and vector
  vect<double> *_source;
  // solution function and vector
  vect<double> *_solution;




};


#endif
