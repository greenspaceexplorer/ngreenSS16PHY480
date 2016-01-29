//
//  poisson.cpp
//  computationalPhysics1
//
//  Created by Curtis Rau on 1/15/16.
//  Copyright © 2016 Curtis Rau. All rights reserved.
//  Last Modified by: Noah Green
//  Date Last Modified:1/29/2016

#include <iostream>
#include <new>          // Is this necessary?
#include <math.h>       /* exp squt */
#include <time.h>

// Declare Functions Here
double source (double x)
{
    return 10 * exp (-10 * x);
}

double solution (double x)
{
    return 0.1 * (
                  exp(-10 * x) +
                  (1 - exp(-10)) * x -
                  1
                  );
}

// "argc" is the number of strings pointed to by "argv"
int main(int argc, const char* argv[]) {
    
    const clock_t begin_time = clock();
    
    // takes the first argument, converts it to an integer, and stores it as "n".
    const int N = 80;//std::stoi(argv[1]);
    double L = 1;                                // The length of the sample;
    double h = L / N;                            // The step size;
    
    // Create the vectors representing the "A" matrix
    double* a = new double[N];                               // todo: replace array with a constant             
    for (int i = 0; i < N; i++) {
        a[i] = 1;
        //std::cout << a[i] << "\r";                    // For debugging purposes
    }
    
    double* b = new double[N];                                // todo: replace array with a constant
    for (int i = 0; i < N; i++) {
        b[i] = -2;
        //std::cout << b[i] << "\r";                    // For debugging purposes
    }
    
    double* c = new double[N];                              // todo: replace array with a constant
    for (int i = 0; i < N; i++) {
        c[i] = 1;
        //std::cout << c[i] << "\r";                    // For debugging purposes
    }

        
    // Create the source term vector "f"
    double* f = new double[N];
    for (int i = 0; i < N; i++) {
        f[i] = source(i * h) * h * h;
        //std::cout << f[i] << "\r";                    // For debugging purposes
    }
  
    
    // Setup solution vector "u"
    double* u = new double[N+1];
    
    // Boundary conditions:
    u[0] = 0;
    u[N] = 0;
    
    // Setup mystery vectors from online example
    double* cStar = new double[N];
    double* fStar = new double[N];
    
    cStar[0] = c[0] / b[0];                             // May not be nceessary
    fStar[0] = f[0] / b[0];                             // May not be necessary
    
    
    
    // Forward substitution
    double m;
    for (int i=1; i<N; i++) {
        m = 1 / (b[i] - a[i] * cStar[i-1]);
        cStar[i] = c[i] * m;
        fStar[i] = (f[i] - a[i] * fStar[i-1]) * m;
    }
        

    delete [] a;
    delete [] b;
    delete [] c;
    
    
    //std::cout << " Here comes the data";              // For debugging purposes
    
    // Backwards substitution
    for (int i = N; i >= 0; i--) {
        u[i] = fStar[i] - cStar[i] * f[i+1];
        //u[i] = solution(i * h);
        //std::cout << u[i] << "\r";                    // For debugging purposes
    }
    
    delete [] f;
    delete [] cStar;
    delete [] fStar;
    
    std::cout << "Total computation time [s] = " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << std::endl;
    
    // Plot the solution
    for (int i = 0; i < N; i = i+2) {
        double num = -10000 * u[i];
        //std:: cout << "Here's that val:" << num;      // For debugging purposes
        for (int i = 0; i < num; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;
    }
    
    delete [] u;
    
    return 0;
}
