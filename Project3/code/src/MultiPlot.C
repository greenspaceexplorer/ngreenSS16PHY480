#include "MultiPlot.h"

//======================================================================================
// Member Function Definitions
//======================================================================================

MultiPlot::MultiPlot(){

  _title = "Plot of Planetary Orbits";
  _xlabel = "X distance from origin (AU)";
  _ylabel = "Y distance from origin (AU)";
  _CanvasX = 600;
  _CanvasY = 600;
  _lxmin = 0.64;
  _lymin = 0.12;
  _lxmax = 0.88;
  _lymax = 0.27;
  _isplots = false;
  _ismade = false;
  _squareplot = false;

}

//--------------------------------------------------------------------------------------

MultiPlot::~MultiPlot(){
  
  if(_isplots){
    for( unsigned int i = 0; i < _plots.size(); i++ ){
      delete _plots.at(i);
    }
  } 
   
  if(_ismade){
    delete _TheCanvas; 
    delete _TheLegend; 
    delete _ThePlot  ; 
  }
}

//--------------------------------------------------------------------------------------

void MultiPlot::Add( TGraph *NewGraph, TString name, unsigned int color ){
  if(!_isplots){ _isplots = true; }
  _plots.push_back(NewGraph);
  _names.push_back(name);
  _colors.push_back(color);

  // get max and min points among all plots
  double x_coord;
  double y_coord;

  static bool firstplot = true;
  if(firstplot){
    NewGraph->GetPoint(0,x_coord,y_coord);
    _xmin = x_coord;
    _xmax = x_coord;
    _ymin = y_coord;
    _ymax = y_coord;
    firstplot = false;
  }

  for( Int_t point = 0; point < NewGraph->GetN(); point++ ){
    NewGraph->GetPoint(point, x_coord, y_coord);
    if( _xmin > x_coord ) _xmin = x_coord;
    if( _xmax < x_coord ) _xmax = x_coord;
    if( _ymin > y_coord ) _ymin = y_coord;
    if( _ymax < y_coord ) _ymax = y_coord;
  }
}

//--------------------------------------------------------------------------------------

void MultiPlot::Save( string filename ){
  if(!_ismade){ _ismade = true; }

  if( _plots.size() == 0 ){
    cout << "Error: must add at least one plot before saving multiplot" << endl;
    exit(1);
  }

  string FName = filename + ".pdf";
  string CName = filename + ".csv";
  ofstream CFile(CName.c_str());
  if( !CFile ){
    cout << "Error: file could not be opened";
    exit(1);      
  }

  TString CanName(filename);
  _TheCanvas = new TCanvas(CanName,"Orbit Plots",_CanvasX,_CanvasY);
  _TheCanvas->cd();

  _ThePlot = new TMultiGraph();
  _TheLegend = new TLegend(_lxmin,_lymin,_lxmax,_lymax);

  Double_t x_coord, y_coord;

  for( unsigned int i = 0; i < _plots.size(); i++ ){
    _plots.at(i)->SetLineColor(_colors.at(i));
    _TheLegend->AddEntry(_plots.at(i), _names.at(i), "l");
    _ThePlot->Add(_plots.at(i));

    // save coordinates to csv
    for( Int_t j = 0; j < _plots.at(i)->GetN(); j++ ){
      _plots.at(i)->GetPoint(j,x_coord,y_coord);
      CFile << x_coord << "," << y_coord << endl;
    }
  }
  
  CFile.close();
  _ThePlot->Draw("AC");
  _ThePlot->SetTitle(_title);
  gPad->SetLeftMargin(0.15);
  _ThePlot->GetYaxis()->SetTitleOffset(2.0);
  if(_squareplot){
    double maxval = max(abs(_xmin),max(abs(_ymin),max(abs(_xmax),abs(_ymax))));
    _ThePlot->GetXaxis()->SetLimits(-1.05*maxval,1.05*maxval);
    _ThePlot->GetYaxis()->SetRangeUser(-1.05*maxval,1.05*maxval);  
  }
  else{
    _ThePlot->GetXaxis()->SetLimits(_xmin,_xmax);
    _ThePlot->GetYaxis()->SetRangeUser(_ymin,_ymax);
  }
  _ThePlot->GetXaxis()->SetTitle(_xlabel);
  _ThePlot->GetXaxis()->CenterTitle();
  _ThePlot->GetYaxis()->SetTitle(_ylabel);
  _ThePlot->GetYaxis()->CenterTitle();
  _ThePlot->Draw("AC");
  _TheLegend->Draw();

  _TheCanvas->SaveAs(FName.c_str());

}

//--------------------------------------------------------------------------------------
