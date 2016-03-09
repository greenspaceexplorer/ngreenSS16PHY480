// Schrodinger equation solver for PHY 480 project 2
// Written by: Noah Green
// Date: 2/24/2016
// Last Modified: 3/4/2016

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Solver.hpp"

using namespace std;

// Make omega_r global so we don't need a new function to change its value
double Wr = 1.0;

//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------

// Single electron harmonic oscillator potential
double sho( double r );

// Double electron harmonic oscillator potential
double dho( double r );

//-----------------------------------------------------------------------------
// Main Body
//-----------------------------------------------------------------------------

int main( int argc, const char* argv[] ){
  
  // Code for manual input of parameters upon execution
  // Note: current implementation overwrites some of the values entered
  // Can enter up to 4 values when calling executable
  //==============================================================
  //   Name (default ): description
  //==============================================================
  //   N    ( 100    ): dimension of matrix 
  //   range( 10.    ): max value of rho
  //   iter ( 100000 ): max number of iterations
  //   tol  ( 1.e-10 ): tolerance on off-diagonal matrix elements
  //==============================================================
  int N;
  int iter;
  double range;
  double tol;

  switch(argc){
  case 0:
    N     = 100;
    range = 10.;
    iter  = 100000;
    tol   = 1.e-10;
    break;
  case 1:
    N     = 100;
    range = 10.;
    iter  = 100000;
    tol   = 1.e-10;
    break;
  case 2:
    N     = atoi( argv[1] );
    range = 10.;
    iter  = 100000;
    tol   = 1.e-10;
    break;
  case 3:
    N     = atoi( argv[1] );
    range = atof( argv[2] );
    iter  = 100000;
    tol   = 1.e-10;
    break;
  case 4:
    N     = atoi( argv[1] );
    range = atof( argv[2] );
    iter  = atoi( argv[3] );
    tol   = 1.e-10;
    break; 
  case 5:
    N     = atoi( argv[1] );
    range = atof( argv[2] );
    iter  = atoi( argv[3] );
    tol   = atof( argv[4] );
    break;
  default:
    cout << "Error: invalid number of command line arguments" << endl;
    exit(1);	
  }
  
  // Array of omega_r values to test
  double Awr[] = { 0.01, 0.5, 1., 5. };
  string Swr[] = { "001", "05", "1", "5" };

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+++++++++++++++++++++ Single electron potential +++++++++++++++++++++++++++++
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
  double SepExp[] = { 3.0, 7.0, 11.0 };
  double SepErr[] = {0.0005, 0.0005, 0.005};

  // Approximate minimum values for eigenvalue solvers to return 
  //     a result consistent with analytical result up to 4 
  //     significant digits for omega_r = 1.0 
  int TestN = 250;
  double TestR = 4.61;
      
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //----GSL vs Jacobi test---
  // Test GSL results vs Jacobi results for various values 
  //     since Jacobi algorithm takes too long for moderate iteration

  // File output is:
  // " Method & N & Range & E1 & E2 & E3 "

  cout << "\n++++GSL vs Jacobi comparison test++++" << endl;
  string SeHoGvJFileName = "SeHoGslJacobiComparison.txt";
  ofstream SeHoGvJFile(SeHoGvJFileName.c_str(), ios::out);

  Solver SN010R10(10  , sho, 10. , iter, tol );
  Solver SN050R10(50  , sho, 10. , iter, tol );
  Solver SN100R05(100 , sho,  5. , iter, tol );
  Solver SN100R10(100 , sho, 10. , iter, tol );
  Solver SN100R20(100 , sho, 20. , iter, tol );
  Solver SN100R50(100 , sho, 50. , iter, tol );
  Solver SSIGF4  (TestN , sho, TestR ); 

  Solver *Compare[] = { &SN010R10, &SN050R10, &SN100R05, &SN100R10
			, &SN100R20, &SN100R50, &SSIGF4 };  
  // include 4 sig fig comparison (long time):
  //for( int i = 0 ; i < sizeof(Compare)/sizeof(&SN010R10); i++ ){ 
  // leave out 4 sig fig comparison:
  for( int i = 0 ; i < sizeof(Compare)/sizeof(&SN010R10)-1; i++ ){ 
    Compare[i]->EigenSolveGSL();
    SeHoGvJFile << "GSL"                   << " & " 
	    << Compare[i]->GetN()      << " & " 
	    << Compare[i]->GetRange()  << " & " 
	    << Compare[i]->GetEval(0)  << " & "   
	    << Compare[i]->GetEval(1)  << " & " 
	    << Compare[i]->GetEval(2)  << " \\\\\\hline" << endl;

    Compare[i]->Reset();
  
    Compare[i]->EigenSolveJacobi();
    SeHoGvJFile << "Jacobi"                << " & " 
	    << Compare[i]->GetN()      << " & " 
	    << Compare[i]->GetRange()  << " & " 
	    << Compare[i]->GetEval(0)  << " & "   
	    << Compare[i]->GetEval(1)  << " & " 
	    << Compare[i]->GetEval(2)  << " \\\\\\hline" << endl;
  }
  SeHoGvJFile.close();
  cout << "Comparison test results in " << SeHoGvJFileName << endl; 
 
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //----Test dependence on r----
  // Used chi squared test for combined estimate on significant figures

  // File output is:
  // "Range,E1,E2,E3,Chisq"

  cout << "\n++++ R test ++++" << endl;
  string SeHoRtestFileName = "SeHoRtestGSL.csv";
  ofstream SeHoRtestFile(SeHoRtestFileName.c_str(), ios::out);

  for( double Rdex = 4.0; Rdex < 5.01; Rdex += 0.01 ){
    SeHoRtestFile << Rdex << ",";
    double Chisq = 0.;
    Solver SRtest(TestN, sho, Rdex, iter, tol);
    SRtest.EigenSolveGSL();
    for( int i = 0; i < 3; i++ ){

      SeHoRtestFile << SRtest.GetEval(i) << ",";

      Chisq += (SRtest.GetEval(i) - SepExp[i])
	*(SRtest.GetEval(i) - SepExp[i])/(SepErr[i]*SepErr[i]);
    }

    SeHoRtestFile << Chisq << endl;

  }
  SeHoRtestFile.close();
  cout << "R test results in " << SeHoRtestFileName << endl; 
 
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //----Test dependence on n----
  // Used chi squared test for combined estimate on significant figures

  // File output is:
  // "N,E1,E2,E3,Chisq"

  cout << "\n++++ N test ++++" << endl;
  string SeHoNtestFileName = "SeHoNtestGSL.csv";
  ofstream SeHoNtestFile(SeHoNtestFileName.c_str(), ios::out);

  for( int Ndex = 240; Ndex < 261; Ndex++ ){
    SeHoNtestFile << Ndex << ",";
    double Chisq = 0.;
    Solver SeHoNtest(Ndex, sho, TestR, iter, tol);
    SeHoNtest.EigenSolveGSL();
    for( int i = 0; i < 3; i++ ){
      SeHoNtestFile << SeHoNtest.GetEval(i) << ",";
      Chisq += (SeHoNtest.GetEval(i) - SepExp[i])
	*(SeHoNtest.GetEval(i) - SepExp[i])/(SepErr[i]*SepErr[i]);
    }
    SeHoNtestFile << Chisq << endl;
  }

  SeHoNtestFile.close();
  cout << "N test results in " << SeHoNtestFileName << endl;  


  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  //----Test iterations and time of calculations----
  // Find the number of rotations to make all non-diagonal elements zero
  // Compare time for eigenvalue calculation of the Jacobi 
  //     and GSl (uses QR) algorithms

  // File output is:
  // "N,Rotations,TimeJacobi,TimeGSL"

  cout << "\n++++ Time comparison and iteration test ++++" << endl;
  string SeHoIterTimeTestFileName = "SeHoIterTimeTest.csv";
  ofstream SeHoIterTimeTestFile(SeHoIterTimeTestFileName.c_str(), ios::out);
  
  for( int Ndex = 10; Ndex < 105; Ndex += 5 ){
    Solver SeHoIterTimeTest(Ndex, sho, TestR, iter, tol);
    SeHoIterTimeTest.EigenSolveJacobi();
    SeHoIterTimeTestFile << Ndex << ","
			 << SeHoIterTimeTest.GetIter() << ","
			 << SeHoIterTimeTest.GetTime() << ",";
    SeHoIterTimeTest.Reset();
    SeHoIterTimeTest.EigenSolveGSL();
    SeHoIterTimeTestFile << SeHoIterTimeTest.GetTime() << endl;
  }

  SeHoIterTimeTestFile.close();
  cout << "Time comparison and iteration results in " << SeHoIterTimeTestFileName << endl;


  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  //----Calculate eigensystem for non-interacting case----
  // Calculate eigenvalues and eigenvectors for different values of omega_r 
  //     for the single-electron(non-interacting double electron)
  //     harmonic oscillator potential.

  // File output is:
  //      For eigenvalues:
  //           "omega_r & E1 & E2 & E3"
  //      For eigenvectors:
  //           "omega_r = Awr[0]"
  //           "X[0],EV1[0],EV2[0],EV3[0]"
  //            ... , ...  , ...  , ...
  //           "X[N-1],EV1[N-1],EV2[N-1],EV3[N-1]"
  //            repeat for subsequent omega_r values

  cout << "\n++++SeHo eigensystem calculation++++" << endl;
  
  string SeHoEvecFileName = "SeHoEvec.csv";
  string SeHoEvalFileName = "SeHoEval.txt";
  ofstream SeHoEvecFile(SeHoEvecFileName.c_str(), ios::out);
  ofstream SeHoEvalFile(SeHoEvalFileName.c_str(), ios::out);

  for( int i = 0; i < sizeof(Awr)/sizeof(double); i++ ){
    Wr = Awr[i];
    gsl_vector *iEvec = gsl_vector_alloc(N);
    Solver SeHoEsys(TestN, sho, TestR, iter, tol);
    SeHoEsys.EigenSolveGSL();
    // Solving with Jacobi algorithm is time intensive
    // SeHoEsys.EigenSolveJacobi();
    SeHoEvalFile << Wr << " & "
		 << SeHoEsys.GetEval(0) << " & "
		 << SeHoEsys.GetEval(1) << " & "
		 << SeHoEsys.GetEval(2) << " \\\\\\hline" << endl;

    SeHoEvecFile << "Wr = " << Wr << endl;
    for( int j = 0; j < TestN; j++ ){
      SeHoEvecFile << SeHoEsys.GetXval() ->data[j] << ","
		   << SeHoEsys.GetEvec(0)->data[j] << ","
		   << SeHoEsys.GetEvec(1)->data[j] << ","
		   << SeHoEsys.GetEvec(2)->data[j] << endl;
    }
  }

  SeHoEvecFile.close();
  SeHoEvalFile.close();
  cout << "Eigenvalues saved to "  << SeHoEvalFileName << endl;
  cout << "Eigenvectors saved to " << SeHoEvecFileName << endl;

  
  

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+++++++++++++++++++++ Double electron potential +++++++++++++++++++++++++++++
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  //----Calculate eigensystem for non-interacting case----
  // Calculate eigenvalues and eigenvectors for different values of omega_r 
  //     for the single-electron(non-interacting double electron)
  //     harmonic oscillator potential.

  // File output is:
  //      For eigenvalues:
  //           "omega_r & E1 & E2 & E3"
  //      For eigenvectors:
  //           "omega_r = Awr[0]"
  //           "X[0],EV1[0],EV2[0],EV3[0]"
  //            ... , ...  , ...  , ...
  //           "X[N-1],EV1[N-1],EV2[N-1],EV3[N-1]"
  //            repeat for subsequent omega_r values

  cout << "\n++++DeHo eigensystem calculation++++" << endl;
  
  string DeHoEvecFileName = "DeHoEvec.csv";
  string DeHoEvalFileName = "DeHoEval.txt";
  ofstream DeHoEvecFile(DeHoEvecFileName.c_str(), ios::out);
  ofstream DeHoEvalFile(DeHoEvalFileName.c_str(), ios::out);

  double RangeA[] = {20.,8.,6.,TestR};
  for( int i = 0; i < sizeof(Awr)/sizeof(double); i++ ){
    Wr = Awr[i];
    gsl_vector *iEvec = gsl_vector_alloc(N);
    Solver DeHoEsys(TestN, dho, RangeA[i], iter, tol);
    DeHoEsys.EigenSolveGSL();
    // Solving with Jacobi algorithm is time intensive
    // DeHoEsys.EigenSolveJacobi();
    DeHoEvalFile << Wr << " & "
		 << DeHoEsys.GetEval(0) << " & "
		 << DeHoEsys.GetEval(1) << " & "
		 << DeHoEsys.GetEval(2) << " \\\\\\hline" << endl;

    DeHoEvecFile << "Wr = " << Wr << endl;
    for( int j = 0; j < TestN; j++ ){
      DeHoEvecFile << DeHoEsys.GetXval() ->data[j] << ","
		   << DeHoEsys.GetEvec(0)->data[j] << ","
		   << DeHoEsys.GetEvec(1)->data[j] << ","
		   << DeHoEsys.GetEvec(2)->data[j] << endl;
    }
  }

  DeHoEvecFile.close();
  DeHoEvalFile.close();
  cout << "Eigenvalues saved to "  << DeHoEvalFileName << endl;
  cout << "Eigenvectors saved to " << DeHoEvecFileName << endl;

  return 0;

}

//-----------------------------------------------------------------------------
// Function Definitions
//-----------------------------------------------------------------------------

// Single electron (or non-interacting double electron) harmonic oscillator potential
double sho( double r ){

  return Wr*r*r;

}

//-----------------------------------------------------------------------------

// Double electron harmonic oscillator potential
double dho( double r ){
  if( r == 0. ){
    r = 1.0e-6; 
  }
  return Wr*r*r + 1/r;

}
