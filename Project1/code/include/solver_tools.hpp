// Project 1: Solver Tool Class
// PHY 480 Computational Physics
// Authors: Noah Green and Curtis Rau
// Last Modified by: Noah Green
// Date Last Modified: 2/6/2016
//
// Note: NG or CR denotes function written by Noah Green or Curtis Rau 
//       respecitvely

#ifndef SOLVER_TOOLS_HPP
#define SOLVER_TOOLS_HPP

#include "vector_cls.hpp"
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
  // constructor for gauss_elim_poisson: NG
  solver( double (*src)( double ), double (*asolution)( double )
	  , double interval, int num );
  
  // constructor for gauss_elim_tridiag: NG
  solver( double (*src)( double ), double (*asolution)( double )
	  , vect<double> a, vect<double> b, vect<double> c
	  , double interval, int num );
  
  // destructor: NG
  ~solver();
  // Gaussian elimination algorithm specifically for poisson equation: NG
  void gauss_elim_poisson();
  // Gaussian elimination algorithm for general tridiagonal matrix: NG
  void gauss_elim_tridiag();
  // LU decomposition solver using armadillo: NG
  void lu_decompadillo();
  // get source vector: NG
  vect<double> get_src();
  // get analytical solution: NG
  vect<double> get_asol();
  // get calculated solution: NG
  vect<double> get_csol();
  // time to solve problem: NG
  float time();
  // print solution to a text file (csv format): NG
  void print_sol( string filename );
  // calculate error between given points: NG
  double error( double act, double calc );
  // calculate all errors: NG
  void error_all();
  // return maximum error: NG
  double error_max();
  // return vector of errors b/w all points: NG
  vect<double> error_vec();
  

private:
  // number of steps in function discretization
  int _N;
  // interval over which function is defined
  double _interval;
  // step size defined as interval/number of steps
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
