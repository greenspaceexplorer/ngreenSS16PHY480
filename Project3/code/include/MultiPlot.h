#ifndef MULTIPLOT_H
#define MULTIPLOT_H

#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TString.h>
#include <TLegend.h>
#include <TAxis.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class MultiPlot{
public:

// default constructor
MultiPlot();

// destructor
~MultiPlot();

// add a tgraph to the multiplot
// Add( TGraph, legend name, color code )
void Add( TGraph*, TString, unsigned int );

// save multiplot as a pdf
void Save( string );

// plot labels
TString _title;
TString _xlabel;
TString _ylabel;

// size of canvas
int _CanvasX;
int _CanvasY;

// size of legend
Double_t _lxmin;
Double_t _lxmax;
Double_t _lymin;
Double_t _lymax;

// plot limits
Double_t _xmin;
Double_t _xmax;
Double_t _ymin;
Double_t _ymax;

// set to true for square plot
bool _squareplot;

private:

TCanvas *_TheCanvas;
TMultiGraph *_ThePlot;
TLegend *_TheLegend;

// info for individual graphs
vector<TGraph*> _plots;
vector<TString> _names;
vector<unsigned int> _colors;

bool _isplots;
bool _ismade;

};

#endif
