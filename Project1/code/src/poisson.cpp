//
//  poisson.cpp
//  computationalPhysics1
//
//  Created by Curtis Rau on 1/15/16.
//  Copyright © 2016 Curtis Rau. All rights reserved.
//  Last Modified by: Noah Green
//  Date Last Modified:1/31/2016

#include <iostream>
#include <new>          // Is this necessary?
#include <math.h>       // exp squt 
#include <time.h>
#include <vector_cls.hpp>

//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------
double source( double x);
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

    // takes the first argument, converts it to an integer, and stores it as "n".
    const int N = 80;//std::stoi(argv[1]);
    double L = 1;                                // The length of the sample;
    double h = L / N;                            // The step size;

    debug(1);
    
    // Create the vectors representing the "A" matrix
    vec<double> a(N,1.); //todo: replace with a constant
    vec<double> b(N,-2.); //todo: replace with a constant
    vec<double> c(N,1.); //todo: replace with a constant
 
   debug(2);

    // Create the source term vector "f"
    vec<double> f(N,0.); //todo: make vec constructor that accepts function as input
    for (int i = 0; i < N; i++) {
      f.set(i, source(i * h) * h * h ); 
    }

    debug(3);

    // Setup solution vector "u"
    vec<double> u(N+1,0.); //note: boundary conditions included in fill value

    // Setup mystery vectors from online example
    vec<double> cStar(N,0);
    vec<double> fStar(N,0);

    cStar.set(0, c.get(0) / b.get(0) ); //todo: not necessary?
    fStar.set(0, f.get(0) / b.get(0) ); //todo: not necessary?
 
    debug(4);
    
    // Forward substitution
    double m;
    for (int i=1; i<N; i++) {
      m = 1 / ( b.get(i) - a.get(i) * cStar.get(i-1));
      cStar.set(i, c.get(i)*m);
      fStar.set(i, (f.get(i) - a.get(i)*fStar.get(i-1)) * m);
    }
    
    debug(5);
    
    // Backwards substitution
    for (int i = N - 1; i > 0; i--) {
      u.set(i, fStar.get(i-1) - cStar.get(i-1) * f.get(i));
    }
    
    debug(6);

    std::cout << "Total computation time [s] = " 
	      << float( clock () - begin_time ) /  CLOCKS_PER_SEC << std::endl;

    debug(7);
    
    // Plot the solution
    for (int i = 0; i < N; i = i+2) {
      double num = -10000 * u.get(i);
        for (int i = 0; i < num; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;
    }
    
    debug(8);

    return 0;
}

//-----------------------------------------------------------------------------
// Function Definitions
//-----------------------------------------------------------------------------

double source( double x )
{
    return 10 * exp (-10 * x);
}

//-----------------------------------------------------------------------------

double solution( double x )
{
    return 0.1 * (
                  exp(-10 * x) +
                  (1 - exp(-10)) * x -
                  1
                  );
}

//-----------------------------------------------------------------------------

void debug( int num ){
  if( b_debug ){
    cout << "---------Debug[" << num << "]---------" << endl;
  }
}
