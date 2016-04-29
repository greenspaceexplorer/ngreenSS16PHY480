//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Apr 16 18:29:20 2016 by ROOT version 5.34/36
// from TTree STDHEP/Analysis tree
// Modified by: Noah Green
// Date: 4/16/2016 
//////////////////////////////////////////////////////////

#ifndef EventReader_h
#define EventReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <TString.h>
#include <cstring>
#include <stdlib.h>

// Header file for the classes stored in the TTree if any.
#include <TClonesArray.h>
#include <TObject.h>

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxEvent = 1;
   const Int_t kMaxGenParticle = 9999;

class EventReader {
public :

   TChain* chain;
   EventReader(const std::string FileNameList, const std::string EventFileLocation);
   virtual ~EventReader();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TChain *NewChain);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   Double_t         MaxPt();
   Double_t         MaxEta();

   TChain         *fChain;   //!pointer to the analyzed TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           Event_;
   UInt_t          Event_fUniqueID[kMaxEvent];   //[Event_]
   UInt_t          Event_fBits[kMaxEvent];   //[Event_]
   Long64_t        Event_Number[kMaxEvent];   //[Event_]
   Int_t           Event_Nparticles[kMaxEvent];   //[Event_]
   Int_t           Event_ProcessID[kMaxEvent];   //[Event_]
   Double_t        Event_Weight[kMaxEvent];   //[Event_]
   Double_t        Event_ScalePDF[kMaxEvent];   //[Event_]
   Double_t        Event_CouplingQED[kMaxEvent];   //[Event_]
   Double_t        Event_CouplingQCD[kMaxEvent];   //[Event_]
   Int_t           Event_size;
   Int_t           GenParticle_;
   UInt_t          GenParticle_fUniqueID[kMaxGenParticle];   //[GenParticle_]
   UInt_t          GenParticle_fBits[kMaxGenParticle];   //[GenParticle_]
   Int_t           GenParticle_PID[kMaxGenParticle];   //[GenParticle_]
   Int_t           GenParticle_Status[kMaxGenParticle];   //[GenParticle_]
   Int_t           GenParticle_M1[kMaxGenParticle];   //[GenParticle_]
   Int_t           GenParticle_M2[kMaxGenParticle];   //[GenParticle_]
   Int_t           GenParticle_D1[kMaxGenParticle];   //[GenParticle_]
   Int_t           GenParticle_D2[kMaxGenParticle];   //[GenParticle_]
   Double_t        GenParticle_E[kMaxGenParticle];   //[GenParticle_]
   Double_t        GenParticle_Px[kMaxGenParticle];   //[GenParticle_]
   Double_t        GenParticle_Py[kMaxGenParticle];   //[GenParticle_]
   Double_t        GenParticle_Pz[kMaxGenParticle];   //[GenParticle_]
   Double_t        GenParticle_PT[kMaxGenParticle];   //[GenParticle_]
   Double_t        GenParticle_Eta[kMaxGenParticle];   //[GenParticle_]
   Double_t        GenParticle_Phi[kMaxGenParticle];   //[GenParticle_]
   Double_t        GenParticle_Rapidity[kMaxGenParticle];   //[GenParticle_]
   Double_t        GenParticle_T[kMaxGenParticle];   //[GenParticle_]
   Double_t        GenParticle_X[kMaxGenParticle];   //[GenParticle_]
   Double_t        GenParticle_Y[kMaxGenParticle];   //[GenParticle_]
   Double_t        GenParticle_Z[kMaxGenParticle];   //[GenParticle_]
   Int_t           GenParticle_size;

   // List of branches
   TBranch        *b_Event_;   //!
   TBranch        *b_Event_fUniqueID;   //!
   TBranch        *b_Event_fBits;   //!
   TBranch        *b_Event_Number;   //!
   TBranch        *b_Event_Nparticles;   //!
   TBranch        *b_Event_ProcessID;   //!
   TBranch        *b_Event_Weight;   //!
   TBranch        *b_Event_ScalePDF;   //!
   TBranch        *b_Event_CouplingQED;   //!
   TBranch        *b_Event_CouplingQCD;   //!
   TBranch        *b_Event_size;   //!
   TBranch        *b_GenParticle_;   //!
   TBranch        *b_GenParticle_fUniqueID;   //!
   TBranch        *b_GenParticle_fBits;   //!
   TBranch        *b_GenParticle_PID;   //!
   TBranch        *b_GenParticle_Status;   //!
   TBranch        *b_GenParticle_M1;   //!
   TBranch        *b_GenParticle_M2;   //!
   TBranch        *b_GenParticle_D1;   //!
   TBranch        *b_GenParticle_D2;   //!
   TBranch        *b_GenParticle_E;   //!
   TBranch        *b_GenParticle_Px;   //!
   TBranch        *b_GenParticle_Py;   //!
   TBranch        *b_GenParticle_Pz;   //!
   TBranch        *b_GenParticle_PT;   //!
   TBranch        *b_GenParticle_Eta;   //!
   TBranch        *b_GenParticle_Phi;   //!
   TBranch        *b_GenParticle_Rapidity;   //!
   TBranch        *b_GenParticle_T;   //!
   TBranch        *b_GenParticle_X;   //!
   TBranch        *b_GenParticle_Y;   //!
   TBranch        *b_GenParticle_Z;   //!
   TBranch        *b_GenParticle_size;   //!


};

#endif

