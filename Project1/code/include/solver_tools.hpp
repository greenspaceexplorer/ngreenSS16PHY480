// Project 1: Solver Tool Class
// PHY 480 Computational Physics
// Authors: Noah Green and Curtis Rau
// Last Modified by: Noah Green
// Date Last Modified: 2/6/2016

#ifndef SOLVER_TOOLS_HPP
#define SOLVER_TOOLS_HPP

#include "vector_cls.hpp"
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>

//-----------------------------------------------------------------------------
// Class Declaration
//-----------------------------------------------------------------------------

class solver{

public:
  // default constructor
  solver( double (*src)( double ), double (*asolution)( double )
	  , double interval, int num );
  // destructor
  ~solver();
  // Gaussian elimination algorithm specifically for poisson equation: by Noah Green
  void gauss_elim_poisson();
  // Gaussian elimination algorithm for general tridiagonal matrix
  void gauss_elim_tridiag();
  // LU decomposition solver using armadillo: by Noah Green
  void lu_decompadillo();
  // get source vector
  vect<double> get_src();
  // get analytical solution
  vect<double> get_asol();
  // get calculated solution
  vect<double> get_csol();
  // time to solve problem
  float time();
  // print solution to a text file (csv format)
  void print_sol(string filename);
  

private:
  // number of steps in function discretization
  int _N;
  // interval over which function is defined
  double _interval;
  // step size defined as interval/number of steps
  double _step;
  // time to solve problem
  clock_t _time;
  // source term vector
  vect<double> _source;
  // analytical solution vector
  vect<double> _asolution;
  // calculated solution vector
  vect<double> _csolution;
  // boolean set to true after a solution algorithm has been called
  bool solved;
};


#endif
