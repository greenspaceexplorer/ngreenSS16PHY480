// Project 1: Poisson Equation Solver
// PHY 480 Computational Physics
// Authors: Noah Green and Curtis Rau
// Last Modified by: Noah Green
// Date Last Modified:2/4/2016

#include <iostream>
#include <new>          // Is this necessary?
#include <math.h>       // exp squt 
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector_cls.hpp>

//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------

double source( double x );
double solution( double x );
void debug( int num );
bool b_debug = false; //set to true for debugging flags

//-----------------------------------------------------------------------------
// Main Body
//-----------------------------------------------------------------------------

// "argc" is the number of strings pointed to by "argv"
int main(int argc, const char* argv[]) {
    
    const clock_t begin_time = clock();

    debug(0);    

    // Takes the first argument, converts it to an integer, and stores it as "n".
    // Default N = 100 if no argument given.
    int hold;
    if( argc > 2 ){
      cout << "Error: invalid number of command line arguments" << endl;
      exit(1);	
    }
    else if( argc == 0 || argc == 1 ){
      hold = 100;      
    }
    else{
      hold = atoi( argv[1] );
    }
    const int N = hold;   

    double L = 1;                                // The length of the sample;
    double h = L / N;                            // The step size;

    debug(1);

    // Create the source term vector "f"
    vec<double> f(N+1,0.); //todo: make vec constructor that accepts function as input
    for (int i = 0; i <= N; i++) {
      f.set(i, source(i * h) * h * h ); 
    }

    // Forward Substitution Step
    for( int i = 0; i <= N-1; i++ ){
      f.set( i+1, f.get( i+1 ) + (i/(i+1.))*f.get( i ) );
    }
    debug(2);
    // Backwards Substitution Step
    for( int i = N-2; i >= 0; i-- ){
      f.set( i, f.get(i) + ((i+2.)/(i+3.))*f.get(i+1));
      //cout << "Step 2: " << f.get(i) << endl;
    } 
    debug(3);
    for( int i = 0; i <= N; i++ ){
      double tmp =  f.get(i)*(-(i+1.)/(i+2.));
      f.set(i, tmp);
    }
    
    debug(4);

    std::cout << "Total computation time [s] = " 
	      << float( clock () - begin_time ) /  CLOCKS_PER_SEC << std::endl;

    debug(7);
    
    /*
//-----------------------------------------------------------------------------
// Alternate Solution
//-----------------------------------------------------------------------------

    // Solution Vector
    vec<double> u(N+1,0.);

   // Create the source term vector "f"
    vec<double> f(N+1,0.); //todo: make vec constructor that accepts function as input
    for(int i = 0; i <= N; i++) {
      f.set(i, source(i * h) * h * h ); 
    }

    u.set( 1, -f.get(0) + 2*u.get(0) );
    for(int j = 2; j < N; j++){
      //      cout << "f(j-1): " << f.get(j-1)
      //	   << "\nu(j-1): " << u.get(j-1)
      //	   << "\nu(j-2): " << u.get(j-2) << endl;
      u.set( j, -f.get(j-1) + 2*u.get(j-1) - u.get(j-2) );
    }

//-----------------------------------------------------------------------------
// Alternate Solution
//-----------------------------------------------------------------------------
*/
    // Write the solution to file
    ofstream solution_file( "sltn_dbl.txt", ios::out );

    if( !solution_file ){
      cout << "Error: file could not be opened" << endl;
      exit(1);
    } 
    
    for( int j = 0; j <= N; j++ ){
      solution_file << j*h << "," 
		    << solution(j*h) << "," 
		    << f.get(j) << endl;
    }

    solution_file.close();

    debug(8);

    return 0;
}

//-----------------------------------------------------------------------------
// Function Definitions
//-----------------------------------------------------------------------------

double source( double x )
{
    return -100* exp (-10 * x);
}

//-----------------------------------------------------------------------------

double solution( double x )
{
  return 1 - ( 1 - exp(-10) ) * x - exp( -10 * x ) ;
}

//-----------------------------------------------------------------------------

void debug( int num ){
  if( b_debug ){
    cout << "---------Debug[" << num << "]---------" << endl;
  }
}
