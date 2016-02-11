// Project 1: Solver Class
// PHY 480 Computational Physics
// Authors: Noah Green and Curtis Rau
// Last Modified by: Noah Green
// Date Last Modified: 2/6/2016

#include "solver_tools.hpp"

//-----------------------------------------------------------------------------
// Class Definitions
//-----------------------------------------------------------------------------
solver::solver( double (*source)( double )
		, double (*solution)( double ), double interval, int num ){
  _N = num;
  _interval = interval;
  // construct source and solution vectors
  _source = new vect<double>(_N+1,_interval,source);
  _solution = new vect<double>(_N+1,_interval,solution);

}


//-----------------------------------------------------------------------------

solver::~solver(){

}

//-----------------------------------------------------------------------------

void solver::gauss_elim_poisson(){


}

//-----------------------------------------------------------------------------

void solver::gauss_elim_tridiag(){

}

