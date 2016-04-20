#include <iostream>
#include <EventReader.h>
#include <ComplexBuilder.h>

using namespace std;

void GetReaderEntry( EventReader*, Long64_t );

int main(){

  string DataDirectory = "/home/noah/Dropbox/git-repos/ngreenSS16PHY480/Project4/code/data/";
  string EventFile = "/home/noah/Dropbox/git-repos/ngreenSS16PHY480/Project4/code/src/eventfiles.dat";
  EventReader *TopoEvents= new EventReader( EventFile, DataDirectory );
  ComplexBuilder TopComplex( TopoEvents );
  cout << TopComplex.Nevent() << " events loaded." << endl;
  
  TopComplex.MetricSpace(20,dp,"top_dp_20");
  
  
  return 0;
}

