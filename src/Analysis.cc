//----------------------------------------------------------------------
// Analysis.cc
//
// Particle IDs are in the PDG StdHep format. The Analysis class handles
// all the data processing as well as filling the TTree in the outpute
// ROOT TFile. Any calculcations should be handled by this class.
//
//----------------------------------------------------------------------

#include <fstream>
#include <iomanip>
#include <stdlib.h>

//Root 
#include "TROOT.h"          // Top level (or root) structure for all classes
#include "TApplication.h"   // ROOT head file for GUI application singleton
#include <TH1.h>            // ROOT head file for 1 dimension histograms
#include <TH2.h>            // ROOT head file for 2 dimension histograms
#include <TSystem.h>        // ROOT head file for a generic interface to the OS
#include <TStopwatch.h>     // ROOT head file for stopwatch for real and cpu time
#include <TStyle.h>         // ROOT head file for all graphics attributes
#include <TFile.h>          
#include <TText.h>
#include <TTree.h>
#include <TF1.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TPaveLabel.h>
#include <TPostScript.h>
#include <TGraph.h>
#include <TClonesArray.h>

//GEANT4 
#include "globals.hh"
#include "G4ios.hh"
#include "G4Track.hh"
#include "G4SteppingManager.hh"
#include "G4ThreeVector.hh"
#include "G4TrajectoryContainer.hh"
#include "G4RunManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Navigator.hh"
#include "G4TransportationManager.hh"
#include "G4Run.hh"

//simpleGeantSim
#include "ScintHitInfo.hh"
#include "ScintillatorHit.hh"
#include "Analysis.hh"
#include "PrimaryGeneratorAction.hh"
#include "DataInput.hh"

using namespace std;

Analysis* Analysis::instance = 0;


//----------------------------------------------------------------------
// Constructor

Analysis::Analysis()
{
  Data = DataInput::GetDataInput();
#ifdef G4ANALYSIS_USE
#endif

#include "DetectorParams.icc"

}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// Destructor

Analysis::~Analysis()
{ 
#ifdef G4ANALYSIS_USE
  // delete things
#endif
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// Create the needed ntuples for filling

void Analysis::book(){
  if(Data->CreateNtuple){
    fScintHitArray = new TClonesArray("ScintHitInfo",1000);

    G4cout << "Creating ntuple: "<< Data->NtupleName << G4endl;
    //    G4String name = Form("%s.root", Data->NtupleName.c_str());
    fScintFile = new TFile(Data->NtupleName.c_str(), "RECREATE");
    fScintTree = new TTree("scintTree","Tree of Scintillator Stuff");
    fScintTree->Branch("run",&fRun,"run/I");
    fScintTree->Branch("event",&fEvent,"event/I");
    fScintTree->Branch("ScintHitInfo","TClonesArray",&fScintHitArray,32000,1);
  }
}

//----------------------------------------------------------------------


//----------------------------------------------------------------------
// Return an instance of the Analysis class

Analysis* Analysis::getInstance()
{
  if (instance == 0) instance = new Analysis;
  return instance;
}

void Analysis::finish()
{  
  if (Data->CreateNtuple){
    fScintFile->cd();
    fScintTree->AutoSave();
    fScintFile->Close();
  }
}

//----------------------------------------------------------------------


//----------------------------------------------------------------------
// Fill the created Ntuple. 
void Analysis::FillTree(const ScintillatorHitsCollection *hitCol) 
{
  if (!Data->CreateNtuple) return;

  TClonesArray &theHits = *fScintHitArray;
  Int_t countHits=0;


  G4RunManager* pRunManager = G4RunManager::GetRunManager();
  fRun = pRunManager->GetCurrentRun()->GetRunID();
  fEvent = pRunManager->GetCurrentEvent()->GetEventID();


  for(int i=0;i<fTotNumScintStrips;i++) {
    ScintillatorHit* aHit = (*hitCol)[i];
    //Check if there was a hit
    if((aHit->GetLogV())) {
      Double_t pos[3]={aHit->GetTruePos()[0],aHit->GetTruePos()[1],aHit->GetTruePos()[2]};
      Int_t side=(aHit->GetPlane()/fNumScintPlanes);
      new(theHits[countHits])
	ScintHitInfo(side,aHit->GetPlane(),aHit->GetStrip(),
		     pos,aHit->GetEdep());
      countHits++;
    }
  }	  
  if(countHits>0) {
    fScintTree->Fill();
    fScintHitArray->Clear();
  }

}
//----------------------------------------------------------------------


