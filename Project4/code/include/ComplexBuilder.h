#ifndef COMPLEXBUILDER_H
#define COMPLEXBUILDER_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <TString.h>
#include <string>
#include <stdlib.h>
#include <TClonesArray.h>
#include <TObject.h>
#include <EventReader.h>
#include <TLorentzVector.h>
#include <vector>

using namespace std;

// Clustering Algorithms
// akt: Anti-kt
// ca:  Cambridge-Aachen
// kt:  kt
// dp:  distance in momentum space
enum ClusterAlg{ akt, ca, kt, dp };

class ComplexBuilder{
 public:
  // default contstructor
  ComplexBuilder( EventReader* );
  // destructor
  ~ComplexBuilder();
  
  // loads an event
  void SelectEvent( Long64_t );

  // return number of events loaded
  Long64_t Nevent() const;
  // return number of particles in currently selected event
  Long64_t Nparticle() const;

  // indicates if particle has no daughters and is qcd colorless
  bool IsFinalParticle( Long64_t );
  void CheckParticleIndex( Long64_t );

  // return distance b/w two particles for given clustering algorithm
  Double_t Distance( Long64_t, Long64_t, ClusterAlg );

  // builds explicit metric space based on given clustering algorithm
  //   warning: clears previously stored metric space
  void MetricSpace( Long64_t, ClusterAlg );

  // filter out points with a nearest neighbor farther away than the given tolerance
  void DensityFilter( Double_t );

  // writes explicit metric space to .csv
  void MetricSpaceCSV( string );

  EventReader *event;  

 private:
  vector< vector< Double_t > > _vMetricSpace;
  Long64_t nevents;

};

#endif
