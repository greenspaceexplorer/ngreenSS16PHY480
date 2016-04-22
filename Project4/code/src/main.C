#include <iostream>
#include <EventReader.h>
#include <ComplexBuilder.h>

using namespace std;

void GetReaderEntry( EventReader*, Long64_t );

int main(){

  // directory with .root madgraph output files
  string DataDirectory = "/home/noah/Dropbox/SS16/PHY480/data/";
  // location of file with list of madgraph output files
  string EventFile = "/home/noah/Dropbox/git-repos/ngreenSS16PHY480/Project4/code/src/eventfiles.dat";

  EventReader *TopoEvents= new EventReader( EventFile, DataDirectory );
  ComplexBuilder TopComplex( TopoEvents );
  cout << TopComplex.Nevent() << " events loaded." << endl;
  
  double progress;
  Double_t pt_cut = 500.;

  string sample_cluster = "top_ca_";
  for( unsigned int i = 0; i < 1000; i++ ){
    TopComplex.SelectEvent(i);
    if(  TopComplex.event->MaxPt() > pt_cut ){
      ostringstream name;
      name << sample_cluster << i ;
      TopComplex.MetricSpace(i,ca);
      TopComplex.DensityFilter(50.0);
      TopComplex.MetricSpaceCSV(name.str());
    }
    
    int barWidth = 70;
    progress = (double)i/1000;
    cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
      if (i < pos) cout << "=";
      else if (i == pos) cout << ">";
      else cout << " ";
    }
    cout << "] " << int(progress * 100.0) << " %\r";
    cout.flush();
    
  }
 
  
  /*
    TopComplex.MetricSpace(4,ca);

    cout << "MaxPt = " << TopComplex.event->MaxPt() << endl;
    TopComplex.DensityFilter(50.0);
    TopComplex.MetricSpaceCSV("top_ca_5");
  */
  delete TopoEvents;
  
  return 0;
}

