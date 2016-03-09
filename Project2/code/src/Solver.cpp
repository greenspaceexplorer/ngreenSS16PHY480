// Eigenvalue solver class for PHY 480 project 2
// Written by: Noah Green
// Date: 2/25/2016
// Last Modified: 3/4/2016

#include "Solver.hpp"

//-----------------------------------------------------------------------------

// Default constructor
Solver::Solver( int Dimension, double (*Potential)(double), double MaxRange
		, int Iter, double Tol ){
  if( Dimension <= 0 || MaxRange <= 0. || Iter <= 0){
    cout << "Error: invalid dimension, range, or iterations." << endl;
    exit(1);
  }

  Function = Potential;
  N = Dimension;
  Range = MaxRange;
  MaxIter = Iter;
  Tolerance = Tol;

  SolveMe = gsl_matrix_alloc(N,N);
  Evec    = gsl_matrix_alloc(N,N);
  Eval    = gsl_vector_alloc(N)  ;
  Xval    = gsl_vector_alloc(N)  ;

  if(Function){
    SetPotential(Function);
  }

  NumIter = 0;
  solved = false;
}

//-----------------------------------------------------------------------------

// Destructor
Solver::~Solver(){
  // Clear non-null pointers
  if(SolveMe->data){ gsl_matrix_free( SolveMe ); }
  if(Evec->data)   { gsl_matrix_free( Evec    ); }
  if(Eval->data)   { gsl_vector_free( Eval    ); }
  if(Xval->data)   { gsl_vector_free( Xval    ); }

}

//-----------------------------------------------------------------------------

// Solve for the eigensystem of a symmetric matrix using GSL
void Solver::EigenSolveGSL(){

  // Allocate gsl solver workspace
  gsl_eigen_symmv_workspace *work = gsl_eigen_symmv_alloc( N );

  // Run solver and get time to run
  _time = clock();
  gsl_eigen_symmv( SolveMe, Eval, Evec, work );
  _time = clock() - _time;

  // Sort eigensystem
  gsl_eigen_symmv_sort( Eval, Evec, GSL_EIGEN_SORT_VAL_ASC );
  
  // Free memory
  gsl_eigen_symmv_free( work );
  solved = true;
}

//-----------------------------------------------------------------------------

// Solve for the eigensystem of a symmetric matrix using the Jacobi algorithm
void Solver::EigenSolveJacobi(){
  // Initialize eigenvector matrix as identity
  gsl_matrix_set_identity( Evec );

  _time = clock();
  // Loop over rotations until off-diagonal sum is < tolerance or the number
  //      of iterations exceeds the maximum number of iterations
  do{
    NumIter++;
    // Get the row and column of the max off-diagonal element
    int k,l;
    double Akl, Akk, All;

    Akl = MaxVal(k,l);
    Akk = gsl_matrix_get( SolveMe, k, k );
    All = gsl_matrix_get( SolveMe, l, l );

    double sn, cs;

    // If max off-diagonal element is zero, then rotation is the identity matrix
    if( Akl != 0.0 ){

      // Solve for values of sine and cosine that will rotate max off-diagonal
      //     matrix element to zero
      double tn, tau;
      tau = ( All - Akk )/(2.*Akl);

      // Choose minimum root for rotation <= pi/4
      if( tau >= 0 ){
	tn = 1./( tau + sqrt(1. + tau*tau) );
      }
      else{
	tn = -1./( -tau + sqrt(1. + tau*tau) );
      }

      cs = 1./sqrt(1+tn*tn);
      sn = tn*cs;
    }
    else{
      // Set rotation to identity if max off-diagonal element is zero
      cs = 1.;
      sn = 0.;
    }

    // Apply rotation to the matrix A (represented by 'SolveMe'): A' = (R^T)(A)(R)
    double Aik, Ail, Rik, Ril;
  
    gsl_matrix_set( SolveMe, k, k, cs*cs*Akk 
		    - 2.*cs*sn*Akl + sn*sn*All );
    gsl_matrix_set( SolveMe, l, l, sn*sn*Akk 
		    + 2.*cs*sn*Akl + cs*cs*All );
    gsl_matrix_set( SolveMe, k, l, 0. );
    gsl_matrix_set( SolveMe, l, k, 0. );
    for( int i = 0; i < N; i++ ){
      if( i != k && i != l ){
	Aik = gsl_matrix_get( SolveMe, i, k );
	Ail = gsl_matrix_get( SolveMe, i, l );
	gsl_matrix_set( SolveMe, i, k, cs*Aik - sn*Ail );
	gsl_matrix_set( SolveMe, k, i, gsl_matrix_get( SolveMe, i, k ) );
	gsl_matrix_set( SolveMe, i, l, cs*Ail + sn*Aik );
	gsl_matrix_set( SolveMe, l, i, gsl_matrix_get( SolveMe, i, l ) );
      }
    
      Rik = gsl_matrix_get( Evec, i, k );
      Ril = gsl_matrix_get( Evec, i, l );

      gsl_matrix_set( Evec, i, k, cs*Rik - sn*Ril );
      gsl_matrix_set( Evec, i, l, cs*Ril + sn*Rik );
    }

  }while( Tolerance < SumOffDiag() && NumIter < MaxIter );
  
  _time = clock() - _time;

  // Extract diagonal elements of 'SolveMe' to get eigenvalues
  for( int index = 0; index < N; index++ ){
    gsl_vector_set( Eval, index, gsl_matrix_get( SolveMe, index, index ) );
  }
  // Sort eigensystem in order of ascending eigenvalues
  gsl_eigen_symmv_sort( Eval, Evec, GSL_EIGEN_SORT_VAL_ASC );
  solved = true;
}

//-----------------------------------------------------------------------------

// Returns quadrature sum of off-diagonal elements
double Solver::SumOffDiag(){
  double sum = 0;
  for( int i = 0; i < N; i++){
    for(int j = i; j < N; j++){
      if( i != j ){
	sum += gsl_matrix_get( SolveMe, i, j )*gsl_matrix_get( SolveMe, i, j );
      }
    }
  }
  return sqrt(2*sum);
}

//-----------------------------------------------------------------------------

double Solver::MaxVal( int &i, int &j ){
  double max = 0.;
  // Symmetric matrix. Only have to iterate over upper triangle.
  for( int row = 0; row < N; row++ ){
    for( int col = row; col < N; col++){
      if( row != col && abs(max) < abs( gsl_matrix_get( SolveMe, row, col ) ) ){
	max = gsl_matrix_get( SolveMe, row, col );
	i = row;
	j = col;
      }
    }
  } 
  return max;
}

//-----------------------------------------------------------------------------

// Reset to initial solver values
void Solver::Reset(){
  SetPotential(Function);
  NumIter = 0;
  solved = false;
}

//-----------------------------------------------------------------------------

// Option to manually set matrix to be solved
void Solver::SetMatrix( gsl_matrix* other ){
  if( other->size1 != N || other->size2 != N ){
    cout << "Error: invalid dimensions" << endl;
    exit(1);
  }
  gsl_matrix_memcpy( SolveMe, other );
}

//-----------------------------------------------------------------------------

// Set up potential matrix for a given potential function
void Solver::SetPotential( double (*Potential)(double) ){
  // Initialize to zero
  gsl_matrix_set_zero( SolveMe );

  double step = Range/(N+1);

  // Start at upper bound of lowest interval
  // End at lower bound of highest interval
  for( int i = 0; i < N; i++ ){
    // Make x value vector for plotting
    double xvalue = (i+1)*step;
    gsl_vector_set( Xval, i, xvalue );
    // Diagonal elements
    gsl_matrix_set( SolveMe, i, i, 2./(step*step) + Potential(xvalue) );

    // Off-diagonal elements
    if( i == 0 ){
      gsl_matrix_set( SolveMe, 0, 1, -1./(step*step) );
    }
    else if( i == N-1 ){
      gsl_matrix_set( SolveMe, N-1, N-2, -1./(step*step) );
    }
    else{
      gsl_matrix_set( SolveMe, i, i-1, -1./(step*step) );
      gsl_matrix_set( SolveMe, i, i+1, -1./(step*step) );
    }
  }
}

//-----------------------------------------------------------------------------

// Set new max iterations
void Solver::SetMaxIter( int iters ){ MaxIter = iters; }

//-----------------------------------------------------------------------------

// Set new tolerance
void Solver::SetTolerance( double tol ){ Tolerance = tol; }

//-----------------------------------------------------------------------------

// Get the ith eigenvalue
double Solver::GetEval( int i ){
  if( i < 0 || i >= N ){
    cout << "Error: Invalid index" << endl;
    exit(1);
  }
  if( !solved ){
    cout << "Error: must solve eigensystem first" << endl;
    exit(1);
  }
  return gsl_vector_get( Eval, i );  
}

//-----------------------------------------------------------------------------

// Get vector of x-values for current range
gsl_vector *Solver::GetXval(){
  if(!Function){
    cout << "Error: must set a function before getting x-values" << endl;
    exit(1);
  }
  return Xval;
}

//-----------------------------------------------------------------------------

// Get the ith eigenvector
gsl_vector *Solver::GetEvec( int i ){
  if( i < 0 || i >= N ){
    cout << "Error: Invalid index" << endl;
    exit(1);
  }
  if( !solved ){
    cout << "Error: must solve eigensystem first" << endl;
    exit(1);
  }
  gsl_vector *temp = gsl_vector_alloc(N);
  gsl_vector *tempcpy = gsl_vector_alloc(N);
  gsl_matrix_get_col( temp, Evec, i );
  // ensure normalization
  double norm,scl;
  norm = gsl_blas_dnrm2(temp);
  scl = 1./sqrt(norm);
  gsl_vector_scale(temp,norm);
  return temp;
}

//-----------------------------------------------------------------------------

int Solver::GetIter(){
  return NumIter;
}

//-----------------------------------------------------------------------------

float Solver::GetTime(){
  if(!solved){
    cout << "Error: cannot return time if no problem was solved." << endl;
    exit(1);
  }
  return ((float)_time/CLOCKS_PER_SEC);
}

//-----------------------------------------------------------------------------

int Solver::GetN(){
  return N;
}

//-----------------------------------------------------------------------------

double Solver::GetRange(){
  return Range;
}
