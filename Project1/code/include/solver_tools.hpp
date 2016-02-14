// Project 1: Solver Tool Class
// PHY 480 Computational Physics
// Author: Noah Green
// Date: 2/10/2016
// Date Last Modified: 2/12/2016



#ifndef SOLVER_TOOLS_HPP
#define SOLVER_TOOLS_HPP

#include "vector_cls.hpp"
#include "lib.h"
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

//-----------------------------------------------------------------------------
// Class Declaration
//-----------------------------------------------------------------------------

class solver{

public:
  // constructor for lu_decomp
  solver( double (*src)( double ), double (*asolution)( double )
	  , double step, int num );

  // constructor for gauss_elim_tridiag
  solver( double (*src)( double ), double (*asolution)( double )
	  , vect<double> a, vect<double> b, vect<double> c
	  , double step, int num );
  
  // destructor
  ~solver();
  // Gaussian elimination algorithm specifically for poisson equation
  //  void gauss_elim_poisson();
  // Gaussian elimination algorithm for general tridiagonal matrix
  void gauss_elim_tridiag();
  // LU decomposition solver
  void lu_decomp();
  // get source vector
  vect<double> get_src();
  // get analytical solution
  vect<double> get_asol();
  // get calculated solution
  vect<double> get_csol();
  // time to solve problem
  float time();
  // print solution to a text file (csv format)
  void print_sol( string filename );
  // calculate error between given points
  double error( double act, double calc );
  // calculate all errors
  void error_all();
  // return maximum error
  double error_max();
  // return vector of errors b/w all points
  vect<double> error_vec();
  

private:
  // number of steps in function discretization
  int _N;
  // step size
  double _step;
  // timer variable
  clock_t _time;
  // source term vector
  vect<double> _source;
  // analytical solution vector
  vect<double> _asolution;
  // calculated solution vector
  vect<double> _csolution;
  // error vector
  vect<double> _error;
  // boolean set to true after a solution algorithm has been called
  bool bsolved;
  // boolean set to true if error vector has been calculated
  bool berror;
  // string to match constructor with solving method
  string _ssolver;
  
  // diagonals for tridiagonal matrix - top, middle, bottom resp.
  vect<double> tri_a;
  vect<double> tri_b; 
  vect<double> tri_c;
  // source*step*step vector for general tridiagonal solver
  vect<double> _ctwidd;
  
};


#endif
