// Test Solver class on a simple eigenvalue problem to check correctness

//#include solver when done
#include <Solver.hpp>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){

  gsl_matrix *test = gsl_matrix_alloc(3,3);
  gsl_matrix_set_zero(test);
  gsl_matrix_set( test, 0, 0, 2);
  gsl_matrix_set( test, 1, 1, 2);
  gsl_matrix_set( test, 2, 2, 2);
  gsl_matrix_set( test, 0, 2, 1);
  gsl_matrix_set( test, 2, 0, 1);

  // test matrix:
  // 2  0  1
  // 0  2  0
  // 1  0  2
  // Should have eigenvalues of 1, 2, and 3

  int row,col;
  Solver Test( 3  );
  Test.SetMatrix(test);
  Test.EigenSolveJacobi();
  cout << "Eigenvalues: " << endl;
  cout << "\t" << Test.GetEval(0)
       << "\t" << Test.GetEval(1) 
       << "\t" << Test.GetEval(2) << endl;
  cout << "Eigenvectors: " << endl;
  for(int i = 0; i < 3; i++ ){
    cout << "\t" << Test.GetEvec(0)->data[i]
	 << "\t" << Test.GetEvec(1)->data[i]
	 << "\t" << Test.GetEvec(2)->data[i] << endl;
  }

  return 0;
}

