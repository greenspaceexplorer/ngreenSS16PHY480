#ifndef COMPLEXBUILDER_H
#define COMPLEXBUILDER_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <TString.h>
#include <string>
#include <stdlib.h>
#include <TClonesArray.h>
#include <TObject.h>
#include <EventReader.h>
#include <TLorentzVector.h>

using namespace std;

// Clustering Algorithms
// akt: Anti-kt
// ca:  Cambridge-Aachen
// kt:  kt
// dp:  distance in momentum space
enum ClusterAlg{ akt, ca, kt, dp};

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

  // saves explicit metric space of particles in an event,
  //   based on the given clustering algorithm, to a .csv file
  void MetricSpace( Long64_t, ClusterAlg, string );

  EventReader *event;  
 private:
  
  Long64_t nevents;

};

#endif
