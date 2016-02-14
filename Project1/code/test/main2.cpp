

#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include "time.h"
#include <new>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "lib.h"

using namespace std;
int main()
{
    cout << "Number of points" << endl;
    int N;
    double h;
    cin >> N;
    double n = N;
    h = 1.0/(n+1);
    cout << h << endl;

    int *indx;
    indx = new int[N];
    double d;
    double **Z;
    Z=new double*[N];
    for (int i = 0; i < N; i++){
            Z[i] = new double[N];
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (i==j){
                Z[i][j]=2.0;
                        }
            else if (i==j+1 || j == i+1){
                Z[i][j]=-1.0;
            }
            else{
                Z[i][j]=0.0;
            }

        }
    }
    double *b = new double[N];
    double *v = new double[N];
    // initialize b = h^2*f(x) = 100*exp(-10x)
    for(int i=0 ; i < N ; i++) {
      b[i]=h*h*100*exp(-10.0*h*(i+1));
      v[i] = 1.0-(1.0-exp(-10.0))*h*(i+1)-exp(-10.0*h*(i+1));
     }
    // LU decompose the matrix
    ludcmp(Z,N,indx,&d);
    // Then backward substitution
    for( int i = 0; i < N; i++ ){
      cout << "b0: " << b[i] << endl;
    }
    lubksb(Z, N, indx, b);
    for( int i = 0; i < N; i++ ){
      cout << "b1: " << b[i] << endl;
    }
    for (int i = 0 ; i < N; i++){ 
      cout << (i+1)*h <<  "   " << b[i] << "  " << log10(fabs( (v[i]-b[i])/v[i])) << endl;
    }

    // Free space 
    delete [] b; 
    for (int i = 0 ; i < N; i++) delete [] Z[i];
    delete [] Z;
    delete [] indx;
    delete [] v;

    return 0;
}
