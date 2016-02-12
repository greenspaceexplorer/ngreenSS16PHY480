// Project 1: Solver Class
// PHY 480 Computational Physics
// Authors: Noah Green and Curtis Rau
// Last Modified by: Noah Green
// Date Last Modified: 2/11/2016

#include "solver_tools.hpp"

//-----------------------------------------------------------------------------
// Class Definitions
//-----------------------------------------------------------------------------
solver::solver( double (*src)( double )
		, double (*asolution)( double ), double interval, int num )
  :_N(num), _interval(interval), _source(num+1,interval,src)
  , _csolution(num+1,interval,src), _asolution(num+1,interval,asolution)
  , _error(num+1,0.), tri_a(1,0.), tri_b(1,0.), tri_c(1,0.), _ctwidd(1,0.)
{
  // calculate step size
  _step = _interval/_N;
  // multiply starting solution elements by _step^2 for algorithm
  for( int i = 0; i < _csolution.length(); i++ ){
    _csolution.set( i, _csolution.get(i) * _step * _step );
  }
  bsolved = false;
  berror = false;
  _ssolver = "gauss_elim_poisson";
}

//-----------------------------------------------------------------------------

solver::solver( double (*src)( double ), double (*asolution)( double )
		, vect<double> a, vect<double> b, vect<double> c
		, double interval, int num )
  :_N(num), _interval(interval), _source(num+1,interval,src)
  , _csolution(num+1, 0.), _ctwidd(num+1,interval,src)
  , _asolution(num+1,interval,asolution)
  , tri_a(a), tri_b(b), tri_c(c), _error(num+1,0.)
{
  // check that diagonals have proper dimensions
  if( ( tri_a.length() < _N+1 ) ||
      ( tri_b.length() < _N+1 ) ||
      ( tri_c.length() < _N+1 ) ){
    cout << "Error: insufficient diagonal dimensions." << endl;
    exit(1);
  }
  tri_a.set(1,0.);
  tri_c.set(num,0.);
  // calculate step size
  _step = _interval/_N;
  // multiply starting solution elements by _step^2 for algorithm
  for( int i = 0; i < _ctwidd.length(); i++ ){
    _ctwidd.set( i, _ctwidd.get(i) * _step * _step );
  }  
  bsolved = false;
  berror = false;
  _ssolver = "gauss_elim_tridiag";

}

//-----------------------------------------------------------------------------

solver::~solver(){

}

//-----------------------------------------------------------------------------

void solver::gauss_elim_poisson(){
  // ensure proper constructor called
  if( _ssolver != "gauss_elim_poisson" ){
    cout << "Error: solver constructor mismatch." << endl;
    exit(1);
  }

  // Protection against solving more than once
  if( bsolved ){
    cout << "Error: Problem has already been solved." << endl;
    exit(1);
  }

  _time = clock();

  // ---------start algorithm------------

  // Forward Substitution Step
  for( int i = 0; i < _csolution.length()-1; i++ ){
    _csolution.set( i+1, _csolution.get( i+1 ) + (i/(i+1.))*_csolution.get( i ) );
  }

  // Backwards Substitution Step
  for( int i = _csolution.length()-2; i >= 0; i-- ){
    _csolution.set( i, _csolution.get(i) + ((i+2.)/(i+3.))*_csolution.get(i+1));
  } 

  for( int i = 0; i < _csolution.length(); i++ ){
    _csolution.set(i, _csolution.get(i)*((i+1.)/(i+2.)));
  }

  // Ensure boundary conditions
  _csolution.set(0,0.);
  _csolution.set(_N,0);

  // -----------end algorithm-------------

  // calculate time for solution
  _time = clock()-_time;

  bsolved = true;
}

//-----------------------------------------------------------------------------

void solver::gauss_elim_tridiag(){
  
  // ensure proper constructor called
  if( _ssolver != "gauss_elim_tridiag" ){
    cout << "Error: solver constructor mismatch." << endl;
    exit(1);
  }

  // Protection against solving more than once
  if( bsolved ){
    cout << "Error: Problem has already been solved." << endl;
    exit(1);
  }

  // temporary vector for algorithm
  vect<double> vect_temp( _csolution.length(), 0. );

  _time = clock();

  // ---------start algorithm------------

  // forward substitution
  double b_temp = tri_b.get(1);
  _csolution.set( 1, _ctwidd.get(1)/b_temp );
  for( int i = 2; i < _csolution.length(); i++){
    vect_temp.set( i, tri_c.get(i-1)/b_temp );
    b_temp = tri_b.get(i) - tri_a.get(i)*vect_temp.get(i);
    _csolution.set( i, 
		    ( _ctwidd.get(i) - _csolution.get(i-1)*tri_a.get(i) )
		    /b_temp);
  }

  // backwards substitution
  for( int i = _csolution.length()-2; i >= 1; i-- ){
    _csolution.set( i, _csolution.get(i) 
		    - vect_temp.get(i+1)*_csolution.get(i+1) );
  }

  // Ensure boundary conditions
  _csolution.set(0,0.);
  _csolution.set(_N,0);

  // -----------end algorithm-------------

  // calculate time for solution
  _time = clock()-_time;

  bsolved = true;
  
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
  if(!bsolved){
    cout << "Warning: problem has not yet been solved." << endl;
  }
  return _csolution;
}

//-----------------------------------------------------------------------------

float solver::time(){
  if(!bsolved){
    cout << "Error: cannot return time if no problem was solved." << endl;
    exit(1);
  }
  return ((float)_time/CLOCKS_PER_SEC);
}

//-----------------------------------------------------------------------------

void solver::print_sol(string filename){
  // protect against printing if problem has not been solved
  if(!bsolved){
    cout << "Error: must solve problem before printing." << endl;
    exit(1);
  }

  ofstream solution_file( filename.c_str(), ios::out );
  // check if file was successfully opened 
  if( !solution_file ){
    cout << "Error: file could not be opened" << endl;
    exit(1);
  } 

  // calculate error vector if not done so already
  if(!berror){ error_all(); }

  // write to file (x, y_actual, y_calculated, error) 
  for( int j = 0; j < _N+1; j++ ){
    solution_file << j*_step << "," 
		  << _asolution.get(j) << ","
		  << _csolution.get(j) << ","
		  << _error.get(j)     << endl;
  }
  // close the file
  solution_file.close();

}

//-----------------------------------------------------------------------------

double solver::error( double act, double calc ){
  // divide by zero protection
  if( act == 0 ){ return 0.;}
  return sqrt(( calc - act )*( calc - act ) / (act*act)) ;
}

//-----------------------------------------------------------------------------

void solver::error_all(){
  // must have a calculated solution prior to calculating error
  if(!bsolved){
    cout << "Error: must solve problem before calculating error." << endl;
    exit(1);
  }
  // fill error vector
  for( int i = 0; i < _csolution.length(); i++ ){
    _error.set( i, error( _asolution.get(i), _csolution.get(i) ) );
  }
  berror = true;
}

//-----------------------------------------------------------------------------

double solver::error_max(){
  // must have a calculated solution prior to calculating error
  if(!bsolved){
    cout << "Error: must solve problem before calculating error." << endl;
    exit(1);
  }

  // calculate error vector if not done so already
  if(!berror){ error_all(); }

  // initialize max error at 0
  double max_error = 0.;    

  // iterate over error vector; replace max error if larger than current value
  for( int i = 0; i < _error.length(); i++ ){
    if( _error.get(i) > max_error ){
      max_error = _error.get(i);
    }
  }
  return max_error;
}
