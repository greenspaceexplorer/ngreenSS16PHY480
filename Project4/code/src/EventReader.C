#include "EventReader.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


//======================================================================================
// Member Function Definitions
//======================================================================================


EventReader::EventReader( const std::string FileNameList, const std::string EventFileLocation) : fChain(0) 
{
  fChain = new TChain("STDHEP","");
  std::ostringstream FileName;
  std::ifstream FileList(FileNameList.c_str(), std::ios::in ); 
  if( !FileList ){
    std::cout << "Error: In EventReader.h, " << FileList << " does not exist" << std::endl;
    exit(1);
  }
  while( !FileList.eof() ){
    std::string NameOfFile;
    FileList >> NameOfFile;
    std::ostringstream comment;
    comment << NameOfFile[0];
     // use '#' to comment out files in the file list
    if( *comment.str().c_str() == *"#" || *comment.str().c_str() == *"" ) continue;
    std::ostringstream FileName;
    FileName << EventFileLocation << NameOfFile;
    fChain->Add( FileName.str().c_str() );
    std::cout << FileName.str() << " added to fChain" << std::endl;
  }
  Init(fChain);
  FileList.close();
}

//--------------------------------------------------------------------------------------

EventReader::~EventReader()
{
  if (!fChain) return;
   fChain->~TChain();
}

//--------------------------------------------------------------------------------------

Int_t EventReader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

//--------------------------------------------------------------------------------------

Long64_t EventReader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

//--------------------------------------------------------------------------------------

void EventReader::Init(TChain *NewChain)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!NewChain) return;
   fChain = NewChain;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Event", &Event_, &b_Event_);
   fChain->SetBranchAddress("Event.fUniqueID", Event_fUniqueID, &b_Event_fUniqueID);
   fChain->SetBranchAddress("Event.fBits", Event_fBits, &b_Event_fBits);
   fChain->SetBranchAddress("Event.Number", Event_Number, &b_Event_Number);
   fChain->SetBranchAddress("Event.Nparticles", Event_Nparticles, &b_Event_Nparticles);
   fChain->SetBranchAddress("Event.ProcessID", Event_ProcessID, &b_Event_ProcessID);
   fChain->SetBranchAddress("Event.Weight", Event_Weight, &b_Event_Weight);
   fChain->SetBranchAddress("Event.ScalePDF", Event_ScalePDF, &b_Event_ScalePDF);
   fChain->SetBranchAddress("Event.CouplingQED", Event_CouplingQED, &b_Event_CouplingQED);
   fChain->SetBranchAddress("Event.CouplingQCD", Event_CouplingQCD, &b_Event_CouplingQCD);
   fChain->SetBranchAddress("Event_size", &Event_size, &b_Event_size);
   fChain->SetBranchAddress("GenParticle", &GenParticle_, &b_GenParticle_);
   fChain->SetBranchAddress("GenParticle.fUniqueID", GenParticle_fUniqueID, &b_GenParticle_fUniqueID);
   fChain->SetBranchAddress("GenParticle.fBits", GenParticle_fBits, &b_GenParticle_fBits);
   fChain->SetBranchAddress("GenParticle.PID", GenParticle_PID, &b_GenParticle_PID);
   fChain->SetBranchAddress("GenParticle.Status", GenParticle_Status, &b_GenParticle_Status);
   fChain->SetBranchAddress("GenParticle.M1", GenParticle_M1, &b_GenParticle_M1);
   fChain->SetBranchAddress("GenParticle.M2", GenParticle_M2, &b_GenParticle_M2);
   fChain->SetBranchAddress("GenParticle.D1", GenParticle_D1, &b_GenParticle_D1);
   fChain->SetBranchAddress("GenParticle.D2", GenParticle_D2, &b_GenParticle_D2);
   fChain->SetBranchAddress("GenParticle.E", GenParticle_E, &b_GenParticle_E);
   fChain->SetBranchAddress("GenParticle.Px", GenParticle_Px, &b_GenParticle_Px);
   fChain->SetBranchAddress("GenParticle.Py", GenParticle_Py, &b_GenParticle_Py);
   fChain->SetBranchAddress("GenParticle.Pz", GenParticle_Pz, &b_GenParticle_Pz);
   fChain->SetBranchAddress("GenParticle.PT", GenParticle_PT, &b_GenParticle_PT);
   fChain->SetBranchAddress("GenParticle.Eta", GenParticle_Eta, &b_GenParticle_Eta);
   fChain->SetBranchAddress("GenParticle.Phi", GenParticle_Phi, &b_GenParticle_Phi);
   fChain->SetBranchAddress("GenParticle.Rapidity", GenParticle_Rapidity, &b_GenParticle_Rapidity);
   fChain->SetBranchAddress("GenParticle.T", GenParticle_T, &b_GenParticle_T);
   fChain->SetBranchAddress("GenParticle.X", GenParticle_X, &b_GenParticle_X);
   fChain->SetBranchAddress("GenParticle.Y", GenParticle_Y, &b_GenParticle_Y);
   fChain->SetBranchAddress("GenParticle.Z", GenParticle_Z, &b_GenParticle_Z);
   fChain->SetBranchAddress("GenParticle_size", &GenParticle_size, &b_GenParticle_size);
   Notify();
}

//--------------------------------------------------------------------------------------

Bool_t EventReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

//--------------------------------------------------------------------------------------


void EventReader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

//--------------------------------------------------------------------------------------

Double_t EventReader::MaxPt(){
  Double_t max = GenParticle_PT[0];
  for( Int_t i = 1; i < GenParticle_; i++ ){
    if( GenParticle_PT[i] > max ) max = GenParticle_PT[i];
  }
  return max;
}

//--------------------------------------------------------------------------------------

Double_t EventReader::MaxEta(){
  Double_t max = GenParticle_Eta[0];
  for( Int_t i = 1; i < GenParticle_; i++ ){
    if( GenParticle_Eta[i] > max ) max = GenParticle_Eta[i];
  }
  return max;
}


//--------------------------------------------------------------------------------------

Int_t EventReader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

//--------------------------------------------------------------------------------------

void EventReader::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L EventReader.C
//      Root > EventReader t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

//--------------------------------------------------------------------------------------
