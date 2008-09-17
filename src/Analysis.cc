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

//JDet
#include "data_t.hh"
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

  g4data = new data_t();
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
    G4cout << "Creating ntuple: "<< Data->NtupleName << G4endl;
    G4String name = Form("%s.root", Data->NtupleName.c_str());
    Ntuple = new TFile(name.c_str(), "RECREATE");
    tree = new TTree("data","JDet ntuple");
    tree->Branch("data", "data_t", &g4data, 32000, 1);
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
    Ntuple->cd();
    tree->Write();
    Ntuple->Close();
    delete Ntuple;
  }
}

//----------------------------------------------------------------------


//----------------------------------------------------------------------
// Fill the created Ntuple. 
void Analysis::FillNtuple(const G4Track& track,const int a_box_index)
{
  if (!Data->CreateNtuple) return;

  G4RunManager* pRunManager = G4RunManager::GetRunManager();

  g4data->run = pRunManager->GetCurrentRun()->GetRunID();
  g4data->evtno = pRunManager->GetCurrentEvent()->GetEventID();

  g4data->x_trk_pos = track.GetPosition()[0];
  g4data->y_trk_pos = track.GetPosition()[1];
  g4data->z_trk_pos = track.GetPosition()[2];

  g4data->x_p = track.GetMomentum()[0];
  g4data->y_p = track.GetMomentum()[1];
  g4data->z_p = track.GetMomentum()[2];

  g4data->penergy = track.GetMomentum()[2];

  g4data->box_index = a_box_index;

  G4ParticleDefinition* particleDefinition = track.GetDefinition();

  g4data->ptype = particleDefinition->GetPDGEncoding();

  tree->Fill();
}
//----------------------------------------------------------------------


