#ifndef PLANET_H
#define PLANET_H

#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <TString.h>
#include <TGraph.h>

#define _USE_MATH_DEFINES
#define G 4*M_PI*M_PI

using namespace std;

struct coordinates{
vector<double> t;
vector<double> x;
vector<double> y;
vector<double> z;
vector<double> vx;
vector<double> vy;
vector<double> vz;
};

class Planet{
public:
  
// Default constructor
Planet(TString = "Planet X", double M = 0., double X = 0., double Y = 0., double Z = 0.
	 , double Vx = 0., double Vy = 0., double Vz = 0.);
// Destructor
~Planet();

// Return stored variables
TString Name();
double M();
double T( unsigned int );
double X( unsigned int );
double Y( unsigned int );
double Z( unsigned int );
double Vx( unsigned int );
double Vy( unsigned int );
double Vz( unsigned int ); 

// Returns relative coordinate with other
double X( Planet&, unsigned int );
double Y( Planet&, unsigned int );
double Z( Planet&, unsigned int );
double Vx( Planet&, unsigned int );
double Vy( Planet&, unsigned int );
double Vz( Planet&, unsigned int ); 

// Return coordinate length
unsigned int N();

// Set variables
void SetM( double );
void AddT( double);
void AddX( double );
void AddY( double );
void AddZ( double );
void AddVx( double );
void AddVy( double );
void AddVz( double );

void SetT( double, unsigned int );
void SetX( double, unsigned int );
void SetY( double, unsigned int );
void SetZ( double, unsigned int );
void SetVx( double, unsigned int );
void SetVy( double, unsigned int );
void SetVz( double, unsigned int );

void AddCoordinates( double, double, double, double, double, double, double );
void SetCoordinates( unsigned int, double, double, double, double, double, double, double ); 

// Fix planet position. Default is false
void SetFixed( bool );
bool Fixed();

// Returns position wrt origin
double R( unsigned int );

// Returns postition wrt another planet
double R( Planet&, unsigned int );

// Returns velocity
double V( unsigned int );

// Returns (component of) force on planet due to other
double F( Planet&, unsigned int );
double Fx( Planet&, unsigned int );
double Fy( Planet&, unsigned int );
double Fz( Planet&, unsigned int );

// Calculate kinetic energy
double KE( unsigned int );

// Calculate potential energy b/w planet and other
double PE( Planet&, unsigned int);

// Calculate angular momentum vector components
void Lv( double&, double&, double&, unsigned int );
// Calculate magnitude of angular momentum
double L( unsigned int );

// check for consistent coordinates
void Check();
void Check( unsigned int );

// output functions:
  
// print a set of coordinates to the terminal
void PrintCoordinates( unsigned int );
  
// print all coordinates to specified filename in .csv format
void SaveCoordinates( string );

// returns pointer to a root tgraph of x and y coordinates
TGraph *PlotCoordinates2D();
TGraph *PlotKEvsT();
TGraph *PlotPEvsT( Planet& );

private: 
double _M;
coordinates _C;
bool _fixed;
TString _name;
};


#endif

