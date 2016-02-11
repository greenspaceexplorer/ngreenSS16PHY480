// Project 1: Poisson Equation Solver
// PHY 480 Computational Physics
// Authors: Noah Green and Curtis Rau
// Last Modified by: Noah Green
// Date Last Modified: 2/6/2016

#include <iostream>
#include <new>          // Is this necessary?
#include <math.h>       // exp squt 
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
    double L = 1;

    // solver for poisson-specific gaussian elimination algorithm
    solver gauss_decomp_fast( source, solution, L, N );
    gauss_decomp_fast.gauss_elim_poisson();
    vect<double> vec_gdf(gauss_decomp_fast.get_csol());
  
    // print computation time
    std::cout << "Total computation time [s] = " 
   	      << gauss_decomp_fast.time() << endl;

    // print reslts to file
    gauss_decomp_fast.print_sol("sltn_dbl.txt");

    return 0;
}

//-----------------------------------------------------------------------------
// Function Definitions
//-----------------------------------------------------------------------------

double source( double x )
{
    return 100* exp (-10 * x);
}

//-----------------------------------------------------------------------------

double solution( double x )
{
  return 1 - ( 1 - exp(-10) ) * x - exp( -10 * x ) ;
}
