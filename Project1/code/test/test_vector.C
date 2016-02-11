#include "vector_cls.hpp"
#include <iostream>

using namespace std;

double square( double x );

int main(){
  int length = 5;
  double interval = 5;
  vect<double> vec_a(length,0.);
  //test length function
  cout << "Length of vec_a: " << vec_a.length() << endl; 
  //test setting and getting
  for( unsigned int index = 0; index < length; index++ ){
    vec_a.set(index, index + 1.);
  }
  cout << "vec_a.get(3): " << vec_a.get(3) << endl;
  cout << "*vec_a[3]: " << *vec_a[3] << endl;

  vect<double> vec_f(length,interval, square);
  cout << "vec_f.get(3): " << vec_f.get(3) << endl;

  return 0;
}

double square( double x ){
  return x*x;
}
