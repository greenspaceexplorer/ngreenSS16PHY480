#include "solver_tools.hpp"

using namespace std;

double square(double x);

int main(){
  solver sol(&square,&square,20.,100);


  return 0;
}

double square(double x){
  return x*x;
}
