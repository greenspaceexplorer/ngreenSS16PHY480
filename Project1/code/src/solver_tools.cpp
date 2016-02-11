// Project 1: Solver Class
// PHY 480 Computational Physics
// Authors: Noah Green and Curtis Rau
// Last Modified by: Noah Green
// Date Last Modified: 2/6/2016

#include "solver_tools.hpp"

//-----------------------------------------------------------------------------
// Class Definitions
//-----------------------------------------------------------------------------
solver::solver( double (*src)( double )
		, double (*asolution)( double ), double interval, int num )
  :_N(num), _interval(interval), _source(num+1,interval,src)
  , _csolution(num+1,interval,src), _asolution(num+1,interval,asolution)
{
  // calculate step size
  _step = _interval/(_N);
  // multiply starting solution elements by _step^2 for algorithm
  for( int i = 0; i < _csolution.length(); i++ ){
    _csolution.set( i, _csolution.get(i) * _step * _step );
  }
  solved = false;
}


//-----------------------------------------------------------------------------

solver::~solver(){

}

//-----------------------------------------------------------------------------

void solver::gauss_elim_poisson(){
  //Protection against solving more than once

  if( solved ){
    cout << "Error: Problem has already been solved." << endl;
    exit(1);
  }

  _time = clock();

  // Forward Substitution Step

  for( int i = 1; i < _N; i++ ){
    _csolution.set( i+1, _csolution.get( i+1 ) + (i/(i+1.))*_csolution.get( i ) );
  }

  // Backwards Substitution Step
  for( int i = _N-1; i > 0; i-- ){
    _csolution.set( i, _csolution.get(i) + ((i+2.)/(i+3.))*_csolution.get(i+1));
  } 

  for( int i = 1; i < _N; i++ ){
    double tmp =  _csolution.get(i)*((i+1.)/(i+2.));
    _csolution.set(i, tmp);
  }
  // Ensure boundary conditions
  _csolution.set(0,0.);
  _csolution.set(_N,0);

  // calculate time for solution
  _time = clock()-_time;

  solved = true;
}

//-----------------------------------------------------------------------------

void solver::gauss_elim_tridiag(){

}

//-----------------------------------------------------------------------------

vect<double> solver::get_src(){
  return _source;
}

//-----------------------------------------------------------------------------

vect<double> solver::get_asol(){
  return _asolution;
}

//-----------------------------------------------------------------------------

vect<double> solver::get_csol(){
  if(!solved){
    cout << "Warning: problem has not yet been solved." << endl;
  }
  return _csolution;
}

//-----------------------------------------------------------------------------

float solver::time(){
  if(!solved){
    cout << "Error: cannot return time if no problem was solved." << endl;
    exit(1);
  }
  return ((float)_time/CLOCKS_PER_SEC);
}

//-----------------------------------------------------------------------------

void solver::print_sol(string filename){
  // protect against printing if problem has not been solved
  if(!solved){
    cout << "Error: must solve problem before printing." << endl;
    exit(1);
  }

  ofstream solution_file( filename.c_str(), ios::out );
  // check if file was successfully opened 
  if( !solution_file ){
    cout << "Error: file could not be opened" << endl;
    exit(1);
  } 

  // write to file (x, y_actual, y_calculated) 
  for( int j = 0; j < _N+1; j++ ){
    solution_file << j*_step << "," 
		  << _asolution.get(j) << ","
		  << _csolution.get(j) << endl;
  }
  // close the file
  solution_file.close();
}

//-----------------------------------------------------------------------------
