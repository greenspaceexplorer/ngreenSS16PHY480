// Project 1: Solver Class
// PHY 480 Computational Physics
// Author: Noah Green
// Date: 2/10/2016
// Date Last Modified: 2/12/2016

#include "solver_tools.hpp"

//-----------------------------------------------------------------------------
// Class Definitions
//-----------------------------------------------------------------------------

solver::solver( double (*src)( double ), double (*asolution)( double )
	, double step, int num )
  :_N(num), _step(step), _asolution(num, 0.), _source(num, 0.)
  , _error(num,0.), tri_a(1,0.), tri_b(1,0.), tri_c(1,0.)
  , _ctwidd(1,0.), _csolution(num,0.)
{
  for( int i = 0; i < _N; i++ ){
    _csolution.set( i, _step * _step * src( (i + 1) * _step) );
    _asolution.set( i, asolution( (i + 1) * _step ) );
  }

  bsolved = false;
  berror = false;
  _ssolver = "lu_decomp";
}

//-----------------------------------------------------------------------------

solver::solver( double (*src)( double ), double (*asolution)( double )
		, vect<double> a, vect<double> b, vect<double> c
		, double step, int num )
  :_N(num), _step(step), _source(num+2,step,src)
  , _csolution(num+2, 0.), _ctwidd(num+1,step,src)
  , _asolution(num+2,step,asolution)
  , tri_a(a), tri_b(b), tri_c(c), _error(num+2,0.)
{
  // check that diagonals have proper dimensions
  if( ( tri_a.length() < _N+1 ) ||
      ( tri_b.length() < _N+1 ) ||
      ( tri_c.length() < _N+1 ) ){
    cout << "Error: insufficient diagonal dimensions." << endl;
    exit(1);
  }

  // multiply starting solution elements by _step^2 for algorithm
  for( int i = 0; i < _ctwidd.length(); i++ ){
    _ctwidd.set( i, _ctwidd.get(i) * _step * _step );
  }  
  _ctwidd.set(0, 0.);
  bsolved = false;
  berror = false;
  _ssolver = "gauss_elim_tridiag";

}

//-----------------------------------------------------------------------------

solver::~solver(){

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

  _time = clock();

  // ---------start algorithm------------

  // temporary vector for algorithm
  vect<double> vect_temp( _N+1, 0. );

  // forward substitution
  double b_temp = tri_b.get(1);
  _csolution.set( 1, _ctwidd.get(1)/b_temp );
  for( int i = 2; i < _N+1; i++){
    vect_temp.set( i, tri_c.get(i-1)/b_temp );
    b_temp = tri_b.get(i) - tri_a.get(i)*vect_temp.get(i);
    _csolution.set( i, 
		    ( _ctwidd.get(i) - _csolution.get(i-1)*tri_a.get(i) )
		    /b_temp);
  }

  // backwards substitution
  for( int i = _N-1; i >= 1; i-- ){
    _csolution.set( i, _csolution.get(i) 
		    - vect_temp.get(i+1)*_csolution.get(i+1) );
  }

  // Ensure boundary conditions
  _csolution.set(0,0.);
  _csolution.set(_csolution.length()-1,0);

  // -----------end algorithm-------------

  // calculate time for solution
  _time = clock()-_time;

  bsolved = true;
  
}

//-----------------------------------------------------------------------------

void solver::lu_decomp(){
   // ensure proper constructor called
  if( _ssolver != "lu_decomp" ){
    cout << "Error: solver constructor mismatch." << endl;
    exit(1);
  }

  // Protection against solving more than once
  if( bsolved ){
    cout << "Error: Problem has already been solved." << endl;
    exit(1);
  }

  // build tridiagonal matrix
  double **TDM;
  TDM = new double*[_N];
  for (int i = 0; i < _N; i++){
    TDM[i] = new double[_N];
  }
  for (int i = 0; i < _N; i++){
    for (int j = 0; j < _N; j++){
      if (i==j){
	TDM[i][j]=2.0;
      }
      else if (i==j+1 || j == i+1){
	TDM[i][j]=-1.0;
      }
      else{
	TDM[i][j]=0.0;
      }
    }
  }

  // variables for lu decomp algorithm
  int *index;
  index = new int[_N];
  double d;
  
  _time = clock(); 

  // ---------start algorithm------------

  // matrix lu decomposition step
  ludcmp( TDM, _N, index, &d );
  // backwards substitution step
  lubksb( TDM, _N, index, _csolution[0] );

  // -----------end algorithm-------------

  // calculate time for solution
  _time = clock()-_time;

  // clear pointers
  for( int i = 0; i < _N; i++ ){
    delete[] TDM[i];
  }
  delete[] TDM;
  delete[] index;

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
    cout << "Error: file could not be opened." << endl;
    exit(1);
  } 

  // calculate error vector if not done so already
  if(!berror){ error_all(); }

  // write to file (x, y_actual, y_calculated, error) 
  if( _ssolver == "lu_decomp" ){
    for( int j = 0; j < _csolution.length(); j++ ){
      solution_file << (j+1.)*_step << "," 
		    << _asolution.get(j) << ","
		    << _csolution.get(j) << ","
		    << _error.get(j)     << endl;
    }
  }
  else{
    for( int j = 0; j < _csolution.length(); j++ ){
      solution_file << j*_step << "," 
		    << _asolution.get(j) << ","
		    << _csolution.get(j) << ","
		    << _error.get(j)     << endl;
    }
  }
  // close the file
  solution_file.close();

}

//-----------------------------------------------------------------------------

double solver::error( double act, double calc ){
  // divide by zero protection
  if( act == 0 ){ return 0.;}
  return log10(fabs(( calc - act ) / act));
}

//-----------------------------------------------------------------------------

void solver::error_all(){
  // must have a calculated solution prior to calculating error
  if(!bsolved){
    cout << "Error: must solve problem before calculating error." << endl;
    exit(1);
  }
  // fill error vector
  for( int i = 1; i < _csolution.length()-1; i++ ){
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
  double max_error = -1e8;    

  // iterate over error vector; replace max error if larger than current value
  for( int i = 0; i < _error.length(); i++ ){
    // skip divide-by-zero error calculations
    if( _error.get(i) == 0 ){ continue; }
    // comparison step
    if( _error.get(i) > max_error ){
      max_error = _error.get(i);
    }
  }
  return max_error;
}
