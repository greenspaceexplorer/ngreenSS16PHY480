// Project 1: Poisson Equation Solver
// PHY 480 Computational Physics
// Author: Noah Green
// Last Modified by: Noah Green
// Date: 1/14/2016
// Date Last Modified: 2/6/2016

#include <iostream>
#include <new>    
#include <math.h> 
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector_cls.hpp>
#include <solver_tools.hpp>

//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------

double source( double x );
double solution( double x );

//-----------------------------------------------------------------------------
// Main Body
//-----------------------------------------------------------------------------

// "argc" is the number of strings pointed to by "argv"
int main(int argc, const char* argv[]) {
    
    // Takes the first argument, converts it to an integer, and stores it as "n".
    // Default N = 100 if no argument given.
    int N;
    if( argc > 2 ){
      cout << "Error: invalid number of command line arguments" << endl;
      exit(1);	
    }
    else if( argc == 0 || argc == 1 ){
      N = 100;      
    }
    else{
      N = atoi( argv[1] );
    }

    // The length of the sample;
    double L = 1.;
    double step = L/(N+1);

    // strings for naming output files
    string sln_name = "SolutionCoords";
    string ext_name = ".txt";


    //=================================================================
    // solver for lu decomposition algorithm
    //=================================================================

    solver lu_decompose( source, solution, step, N );
    lu_decompose.lu_decomp();

    // build filename
    string lu_name = "_LU";    
    stringstream lu_stream;
    lu_stream << sln_name << lu_name << "_N" << N << ext_name;
    
    // print computation time and max error
    cout << "LU( N = " << N << " ): Time [s] = " 
	 << lu_decompose.time() << "\tLog10 Max Error = "
	 << lu_decompose.error_max() << endl;

    //=================================================================
    // solver for general tridiagonal problem
    //=================================================================

    vect<double> a(N+1,-1);
    vect<double> b(N+1, 2);
    vect<double> c(N+1,-1);
    solver gauss_decomp_gen( source, solution, a, b, c, step, N );
    gauss_decomp_gen.gauss_elim_tridiag();

    // build filename
    string gdg_name = "_GDG";    
    stringstream gdg_stream;
    gdg_stream << sln_name << gdg_name << "_N" << N << ext_name;

    // print computation time and max error
    cout << "GDG( N = " << N << " ): Time [s] = " 
    	 << gauss_decomp_gen.time() << "\tLog10 Max Error = "
    //      cout << N << "\t" 
	 << gauss_decomp_gen.error_max() << endl;

    //=================================================================
    // program output
    //=================================================================

    gauss_decomp_gen.print_sol(gdg_stream.str());
    lu_decompose.print_sol(lu_stream.str());

    // record names of solution files
    ofstream solution_names("CoordFiles.txt");
    if( !solution_names ){
      cout << "Error: file could not be opened." << endl;
      exit(1);
    }
    solution_names << gdg_stream.str() << endl 
		   << lu_stream.str()
		   << endl;
    solution_names.close();

    return 0;
}

//-----------------------------------------------------------------------------
// Function Definitions
//-----------------------------------------------------------------------------

double source( double x )
{
    return 100.* exp (-10. * x);
}

//-----------------------------------------------------------------------------

double solution( double x )
{
  return 1. - ( 1. - exp(-10.) ) * x - exp( -10. * x ) ;
}
