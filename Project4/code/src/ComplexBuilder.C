#include <ComplexBuilder.h>

//======================================================================================
// Member Function Definitions
//======================================================================================

ComplexBuilder::ComplexBuilder( EventReader *EventsIn ){
  event = EventsIn;
  if(!event){
	cout << "Error: no event available to build simplicial complexes" << endl;
	exit(1);
  }
  nevents = event->fChain->GetEntries();
}

//--------------------------------------------------------------------------------------

ComplexBuilder::~ComplexBuilder(){}

//--------------------------------------------------------------------------------------

void ComplexBuilder::SelectEvent( Long64_t ievent ){
  if( ievent > nevents || ievent < 0 ){
	cout << "Error: invalid event index" << endl;
	exit(1);
  }
  
  event->LoadTree(ievent);
  event->b_Event_->GetEntry(ievent);
  event->b_Event_fUniqueID->GetEntry(ievent);
  event->b_Event_fBits->GetEntry(ievent);
  event->b_Event_Number->GetEntry(ievent);
  event->b_Event_Nparticles->GetEntry(ievent);
  event->b_Event_ProcessID->GetEntry(ievent);
  event->b_Event_Weight->GetEntry(ievent);
  event->b_Event_ScalePDF->GetEntry(ievent);
  event->b_Event_CouplingQED->GetEntry(ievent);
  event->b_Event_CouplingQCD->GetEntry(ievent);
  event->b_Event_size->GetEntry(ievent);
  event->b_GenParticle_->GetEntry(ievent);
  event->b_GenParticle_fUniqueID->GetEntry(ievent);
  event->b_GenParticle_fBits->GetEntry(ievent);
  event->b_GenParticle_PID->GetEntry(ievent);
  event->b_GenParticle_Status->GetEntry(ievent);
  event->b_GenParticle_M1->GetEntry(ievent);
  event->b_GenParticle_M2->GetEntry(ievent);
  event->b_GenParticle_D1->GetEntry(ievent);
  event->b_GenParticle_D2->GetEntry(ievent);
  event->b_GenParticle_E->GetEntry(ievent);
  event->b_GenParticle_Px->GetEntry(ievent);
  event->b_GenParticle_Py->GetEntry(ievent);
  event->b_GenParticle_Pz->GetEntry(ievent);
  event->b_GenParticle_PT->GetEntry(ievent);
  event->b_GenParticle_Eta->GetEntry(ievent);
  event->b_GenParticle_Phi->GetEntry(ievent);
  event->b_GenParticle_Rapidity->GetEntry(ievent);
  event->b_GenParticle_T->GetEntry(ievent);
  event->b_GenParticle_X->GetEntry(ievent);
  event->b_GenParticle_Y->GetEntry(ievent);
  event->b_GenParticle_Z->GetEntry(ievent);
  event->b_GenParticle_size->GetEntry(ievent);
}

//--------------------------------------------------------------------------------------

Long64_t ComplexBuilder::Nevent() const{ return nevents; }

//--------------------------------------------------------------------------------------

Long64_t ComplexBuilder::Nparticle() const{ return event->GenParticle_; }

//--------------------------------------------------------------------------------------

bool ComplexBuilder::IsFinalParticle( Long64_t iparticle ){

  // true if particle is one of the original protons in the collision
  bool proton   = (event->GenParticle_PID[iparticle] == 2212 &&
		   event->GenParticle_M1[iparticle]  == -1   &&
		   event->GenParticle_M2[iparticle]  == -1   &&
		   event->GenParticle_D1[iparticle]  == -1   &&  
		   event->GenParticle_D2[iparticle]  == -1);
  // true for qcd particles
  bool q_or_glu = (abs(event->GenParticle_PID[iparticle]) < 9 ||
		   event->GenParticle_PID[iparticle] == 21);
  // true for weak bosons
  bool w_or_z   = (abs(event->GenParticle_PID[iparticle]) == 24 ||
		   event->GenParticle_PID[iparticle] == 23);
  // true if particle has daughters
  bool has_daughters = (event->GenParticle_D1[iparticle] >= 0 &&
			event->GenParticle_D2[iparticle] >= 0);
  
  return (!proton && !q_or_glu && !w_or_z && !has_daughters);

}

//--------------------------------------------------------------------------------------

void ComplexBuilder::CheckParticleIndex( Long64_t i ){
  if( i < 0 || i > event->GenParticle_ ){
    cout << "Error: particle index out of range" << endl;
    exit(1); 
  }
}

//--------------------------------------------------------------------------------------

Double_t ComplexBuilder::Distance( Long64_t i_p1, Long64_t i_p2, ClusterAlg alg ){
  CheckParticleIndex(i_p1);
  CheckParticleIndex(i_p2);

  Double_t dist;

  switch(alg){
  case akt:
    {
      Double_t KT1  = event->GenParticle_PT[i_p1];
      Double_t ETA1 = event->GenParticle_Eta[i_p1];
      Double_t PHI1 = event->GenParticle_Phi[i_p1];  
      Double_t KT2  = event->GenParticle_PT[i_p2];
      Double_t ETA2 = event->GenParticle_Eta[i_p2];
      Double_t PHI2 = event->GenParticle_Phi[i_p2];

      dist = max( 1./(KT1*KT1), 1./(KT2*KT2) ) 
	* ( (ETA1 - ETA2)*(ETA1 - ETA2) + (PHI1 - PHI2)*(PHI1 - PHI2) );
    }
    break;

  case ca:    
    {
      Double_t KT1  = event->GenParticle_PT[i_p1];
      Double_t ETA1 = event->GenParticle_Eta[i_p1];
      Double_t PHI1 = event->GenParticle_Phi[i_p1];  
      Double_t KT2  = event->GenParticle_PT[i_p2];
      Double_t ETA2 = event->GenParticle_Eta[i_p2];
      Double_t PHI2 = event->GenParticle_Phi[i_p2];

      dist = (ETA1 - ETA2)*(ETA1 - ETA2) + (PHI1 - PHI2)*(PHI1 - PHI2);
    }
    break;
  case kt:
    {
      Double_t KT1  = event->GenParticle_PT[i_p1];
      Double_t ETA1 = event->GenParticle_Eta[i_p1];
      Double_t PHI1 = event->GenParticle_Phi[i_p1];  
      Double_t KT2  = event->GenParticle_PT[i_p2];
      Double_t ETA2 = event->GenParticle_Eta[i_p2];
      Double_t PHI2 = event->GenParticle_Phi[i_p2];

      dist = max( KT1*KT1, KT2*KT2 ) 
	* ( (ETA1 - ETA2)*(ETA1 - ETA2) + (PHI1 - PHI2)*(PHI1 - PHI2) );
    }
    break;
  case dp:
    {
      Double_t PX1 = event->GenParticle_Px[i_p1];
      Double_t PY1 = event->GenParticle_Py[i_p1];
      Double_t PZ1 = event->GenParticle_Pz[i_p1];
      Double_t PX2 = event->GenParticle_Px[i_p2];
      Double_t PY2 = event->GenParticle_Py[i_p2];
      Double_t PZ2 = event->GenParticle_Pz[i_p2];

      dist = sqrt( (PX1-PX2)*(PX1-PX2) + (PY1-PY2)*(PY1-PY2) + (PZ1-PZ2)*(PZ1-PZ2) );

    }
    break;
  default:
    cout << "Error: invalid clustering algorithm" << endl;
    exit(1);    
  }
  return dist;
}

//--------------------------------------------------------------------------------------

void ComplexBuilder::MetricSpace( Long64_t ievent, ClusterAlg alg ){

  SelectEvent(ievent);

  // clear any previously stored metric space
  _vMetricSpace.clear();

  // store metric space in _vMetricSpace
  //for( Long64_t i = 0; i < 150; i++ ){
  for( Long64_t i = 0; i < Nparticle(); i++ ){
    vector< Double_t > row;
    //for( Long64_t j = 0; j < 150; j++ ){
    for( Long64_t j = 0; j < Nparticle(); j++ ){
      if( IsFinalParticle(i) && IsFinalParticle(j) ){
	row.push_back(Distance(i,j,alg)); 
      }
    }
    if( IsFinalParticle(i) ){
      _vMetricSpace.push_back(row);
    }
  }
}

//--------------------------------------------------------------------------------------

void ComplexBuilder::DensityFilter( Double_t tolerance ){

  if( _vMetricSpace.size() == 0 ){
    cout << "Error: must calculate a metric space before applying filter"
	 << endl;
    exit(1);
  }

  unsigned int min;
  for( unsigned int i = 0; i < _vMetricSpace.size(); i++ ){
    // get distance to nearest neighbour
    if(i == 0 ){
       min = 1;
    }
    else{
       min = 0;
    }
    for( unsigned int j = 0; j < _vMetricSpace.at(i).size(); j++ ){
      if( i == j ) continue;
      if( _vMetricSpace.at(i).at(j) <_vMetricSpace.at(i).at(min) ){
	min = j;
      }
    }

    // check if distance is > tolerance and delete point if so
    if( _vMetricSpace.at(i).at(min) > tolerance ){
      for( unsigned int k = 0; k < _vMetricSpace.size(); k++ ){
	_vMetricSpace.at(k).erase(_vMetricSpace.at(k).begin()+i-1);
      }
      _vMetricSpace.erase(_vMetricSpace.begin()+i-1);
      i--;
    }
  }

  if( _vMetricSpace.size() == 0 ){
    cout << "Error: density tolerance too small - no points remaining" << endl;
    exit(1);
  }  

}

//--------------------------------------------------------------------------------------

void ComplexBuilder::MetricSpaceCSV( string filename ){
  if( _vMetricSpace.size() == 0 ){
    cout << "Error: must calculate a metric space before attempting to write to file"
	 << endl;
    exit(1);
  }

  string outfilename = filename + ".csv";
  ofstream fileout( outfilename.c_str(), ios::out );
 
  if(!fileout){
    cout << "Error: could not open " << outfilename << endl;
    exit(1);
  }

  unsigned int nrow = _vMetricSpace.size();
  //cout << "Size of metric space = " << nrow << endl;
  for( unsigned int i = 0; i < nrow; i++ ){
    unsigned int ncol = _vMetricSpace.at(i).size();
    if( nrow != ncol ){
      cout << "Error: metric space not a square matrix" << endl;
      exit(1);
    }
    for( unsigned int j = 0; j < ncol; j++ ){
      fileout << setprecision(5) << _vMetricSpace.at(i).at(j);
      if( j != ncol- 1 ){
	fileout << ",";
      }
    }
    fileout << endl;
  }
  fileout.close();
}

//--------------------------------------------------------------------------------------
