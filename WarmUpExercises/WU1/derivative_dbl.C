#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>

using namespace std;

void equation1(double*, int, int, double, double);
void equation2(double*, int, int, double, double);

int main(){

  //declare variables
  
  int size = 40;
  double x = sqrt(2);
  double *step;
  double *d1h1;
  double *d1h2;
  double *err_d1h1;
  double *err_d1h2;

  step = new double[size];
  d1h1 = new double[size];
  d1h2 = new double[size];
  err_d1h1 = new double[size];
  err_d1h2 = new double[size];

  //build step size vector
  for(int index = 0; index < size; index++){
    step[index] = 1/pow(2,index);
  }

  //iterate over step vector
  for(int jndex = 0; jndex < size; jndex++){
    //first derivatives and errors
    //equation 1 (error h^1)
    equation1(d1h1, size, jndex, step[jndex], x);
    err_d1h1[jndex] = log10(abs(3*d1h1[jndex] - 1));
    //equation 2 (error h^2)
    equation2(d1h2, size, jndex, step[jndex], x);
    err_d1h2[jndex] = log10(abs(3*d1h2[jndex] - 1));    

  }

  //Output values to file
  ofstream error_file_1, error_file_2;
  error_file_1.open("errors_dbl_1.tsv", ios::out);
  error_file_2.open("errors_dbl_2.tsv", ios::out);
  for(int kndex = 0; kndex < size; kndex++){
    error_file_1 << log10(step[kndex]) << "\t" 
		 << err_d1h1[kndex] << endl;
    error_file_2 << log10(step[kndex]) << "\t"
		 << err_d1h2[kndex] << endl;

  }

  error_file_1.close();
  error_file_2.close();

  delete [] step;
  delete [] d1h1;
  delete [] d1h2;
  delete [] err_d1h1;
  delete [] err_d1h2;

  return 0;
}

//-----------------------------------------------------------------------------------------
void equation1(double *d1h1, int size, int index, double step, double x){
  if(index >= size){
    cout << "Error: index too large" << endl;
    exit(1);
  }
  d1h1[index] = (atan(x+step) - atan(x))/step; 
  return;
}

//-----------------------------------------------------------------------------------------

void equation2(double *d1h2, int size, int index, double step, double x){
  if(index >= size){
    cout << "Error: index too large" << endl;
    exit(1);
  }
  d1h2[index] = (atan(x+step) - atan(x-step))/(2*step);  
  return;  
}
