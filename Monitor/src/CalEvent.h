//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar  6 11:41:20 2007 by ROOT version 5.10/00
// from TTree CalTuple/Glast tuple
// found on file: /nfs/farm/g/glast/u41/Integration/rootData/077014005/v7r0913p10/recon/recon-v3r9p1_077014005_cal_ntuple.root
//////////////////////////////////////////////////////////

#ifndef CalEvent_h
#define CalEvent_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TObject.h>

class CalEvent:public TObject {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
   Int_t           RunID;
   Int_t           EventID;
   Float_t         CalXtalAdcPed[16][8][12][2];
   Float_t         CalXtalAdcPedAllRange[16][8][12][2][4];
   Int_t           CalXtalAdcRng[16][8][12][2];
   Float_t         CalXtalFaceSignal[16][8][12][2];
   Float_t         CalXtalFaceSignalAllRange[16][8][12][2][4];

   // List of branches
   TBranch        *b_RunID;   //!
   TBranch        *b_EventID;   //!
   TBranch        *b_CalXtalAdcPed;   //!
   TBranch        *b_CalXtalAdcPedAllRange;   //!
   TBranch        *b_CalXtalAdcRng;   //!
   TBranch        *b_CalXtalFaceSignal;   //!
   TBranch        *b_CalXtalFaceSignalAllRange;   //!

   CalEvent(TTree *tree=0);
   virtual ~CalEvent();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef CalEvent_cxx
CalEvent::CalEvent(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/nfs/farm/g/glast/u41/Integration/rootData/077014005/v7r0913p10/recon/recon-v3r9p1_077014005_cal_ntuple.root");
      if (!f) {
         f = new TFile("/nfs/farm/g/glast/u41/Integration/rootData/077014005/v7r0913p10/recon/recon-v3r9p1_077014005_cal_ntuple.root");
      }
      tree = (TTree*)gDirectory->Get("CalTuple");

   }
   Init(tree);
}

CalEvent::~CalEvent()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t CalEvent::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t CalEvent::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->IsA() != TChain::Class()) return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void CalEvent::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses of the tree
   // will be set. It is normaly not necessary to make changes to the
   // generated code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running with PROOF.

   // Set branch addresses
   if (tree == 0) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunID",&RunID);
   fChain->SetBranchAddress("EventID",&EventID);
   fChain->SetBranchAddress("CalXtalAdcPed[16][8][12][2]",CalXtalAdcPed);
   fChain->SetBranchAddress("CalXtalAdcPedAllRange[16][8][12][2][4]",CalXtalAdcPedAllRange);
   fChain->SetBranchAddress("CalXtalAdcRng[16][8][12][2]",CalXtalAdcRng);
   fChain->SetBranchAddress("CalXtalFaceSignal[16][8][12][2]",CalXtalFaceSignal);
   fChain->SetBranchAddress("CalXtalFaceSignalAllRange[16][8][12][2][4]",CalXtalFaceSignalAllRange);
   Notify();
}

Bool_t CalEvent::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. Typically here the branch pointers
   // will be retrieved. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed.

   // Get branch pointers
   b_RunID = fChain->GetBranch("RunID");
   b_EventID = fChain->GetBranch("EventID");
   b_CalXtalAdcPed = fChain->GetBranch("CalXtalAdcPed[16][8][12][2]");
   b_CalXtalAdcPedAllRange = fChain->GetBranch("CalXtalAdcPedAllRange[16][8][12][2][4]");
   b_CalXtalAdcRng = fChain->GetBranch("CalXtalAdcRng[16][8][12][2]");
   b_CalXtalFaceSignal = fChain->GetBranch("CalXtalFaceSignal[16][8][12][2]");
   b_CalXtalFaceSignalAllRange = fChain->GetBranch("CalXtalFaceSignalAllRange[16][8][12][2][4]");

   return kTRUE;
}

void CalEvent::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t CalEvent::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef CalEvent_cxx
