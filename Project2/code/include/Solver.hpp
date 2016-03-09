// Eigenvalue solver class for PHY 480 project 2
// Written by: Noah Green
// Date: 2/25/2016
// Last Modified: 3/4/2016

#ifndef SOLVER_H
#define SOLVER_H

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_blas.h>
#include <time.h>
#include <cmath>
#include <iostream>

using namespace std;

class Solver{

public:

  // Default constructor
  Solver( int = 100, double (*Potential)(double) = NULL, double = 10.
	  , int = 100000, double = 1.e-10 );
  ~Solver();

  void EigenSolveGSL(); 
  void EigenSolveJacobi();

  double SumOffDiag();
  double MaxVal( int&, int& );
  void Reset();

  void SetMatrix( gsl_matrix* );
  void SetPotential( double (*)(double) );
  void SetMaxIter( int );
  void SetTolerance( double );

  double GetEval( int );
  gsl_vector *GetXval();
  gsl_vector *GetEvec( int );
  int GetIter();
  float GetTime();
  int GetN();
  double GetRange();

private:
  // Variables for all solvers
  gsl_matrix *SolveMe;
  gsl_matrix *Evec;
  gsl_vector *Eval;
  gsl_vector *Xval;
  double (*Function)(double);
  double Range;
  int N;
  bool solved;

  clock_t _time;
  
  // Variables for Jacobi solver
  int MaxIter;
  double Tolerance;
  int NumIter;
  
};

#endif
