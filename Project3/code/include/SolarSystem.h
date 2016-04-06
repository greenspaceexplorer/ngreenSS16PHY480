#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "Planet.h"
#include <vector>

class SolarSystem{
 public:
  // Default constructor
  SolarSystem( double time, int intervals );
  // Destructor
  ~SolarSystem();

  // Add another planet to solar system
  void AddPlanet( Planet );
  // Get i-1th planet
  Planet GetPlanet( unsigned int );
  // Get number of bodies in solar system
  unsigned int GetN();
  // Returns the total force on a planet i from all other bodies in solar system  
  void TotalForce( unsigned int, unsigned int, double&, double&, double& );
  // Returns combined ke of entire system
  double SystemKE( unsigned int );
  // Returns combined pe of entire system
  double SystemPE( unsigned int );
  // Returns combined angular momentum entire system
  double SystemL( unsigned int );
  // 4th order runge-kutta method
  void RK4();
  // velocity verlet method
  void Verlet();
  // return pointers to TGraphs of ke,pe,and angular momentum for given time interval
  TGraph *PlotKEvsT();
  TGraph *PlotPEvsT();
  TGraph *PlotLvsT();
 private:
  vector<Planet> _vPlanets;
  double _Time;
  double _Ntime;
  double _step;
  bool _solved;

};


#endif
