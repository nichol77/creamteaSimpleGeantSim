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
#include <TMath.h>
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
#include "DetectorDefs.hh"
#include "WorldSetup.hh"

using namespace std;

Analysis* Analysis::instance = 0;


//----------------------------------------------------------------------
// Constructor

Analysis::Analysis()
{
  Data = DataInput::GetDataInput();
#ifdef G4ANALYSIS_USE
#endif


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
    //This is a nasty hack but will do for now.
    WorldSetup *myWorld = new WorldSetup();
    myWorld->worldSize=WORLD_SIZE;
    myWorld->scintLength=SIDELENGTH;
    myWorld->planesPerSide=PLANES_PER_SIDE;
    myWorld->stripsPerPlane=STRIPS_PER_PLANE;
    myWorld->planeWidth=PLANE_WIDTH_CM*0.01; ///Convert to m
    myWorld->gapBetweenPlanes=GAP_BETWEEN_PLANES_CM*0.01;
    myWorld->background=BACKGROUND;
    myWorld->sphereRadius=SPHERE_RADIUS_CM*0.01;
    myWorld->sphereDensity=SPHERE_DENSITY_KG_M3;
    myWorld->sphereOriginX=SPHERE_X_M;
    myWorld->sphereOriginY=SPHERE_Y_M;
    myWorld->sphereOriginZ=SPHERE_Z_M;
    myWorld->verticalSeparation=VERTICAL_SEPARATION;

      

    fScintHitArray = new TClonesArray("ScintHitInfo",1000);

    G4cout << "Creating ntuple: "<< Data->NtupleName << G4endl;
    //    G4String name = Form("%s.root", Data->NtupleName.c_str());
    fScintFile = new TFile(Data->NtupleName.c_str(), "RECREATE");
    fWorldTree = new TTree("worldTree","Tree of Worldly Things");
    fWorldTree->Branch("world","WorldSetup",&myWorld);
    fWorldTree->Fill();
    fWorldTree->AutoSave();

    fScintTree = new TTree("scintTree","Tree of Scintillator Stuff");
    fScintTree->Branch("run",&fRun,"run/I");
    fScintTree->Branch("event",&fEvent,"event/I");
    fScintTree->Branch("ScintHitInfo","TClonesArray",&fScintHitArray,32000,1);
    fScintTree->Branch("numHits",&fCountHits,"numHits/I");
    fScintTree->Branch("intPos",fIntPos,"intPos[3]/D");
    fScintTree->Branch("intMom",fIntMom,"intMom[3]/D");
    fScintTree->Branch("intEng",&fIntEng,"intEng/D");
    fScintTree->Branch("genEng",&fGenEng,"genEng/D");
    fScintTree->Branch("phi",&fPhi,"phi/D");
    fScintTree->Branch("theta",&fTheta,"theta/D");
    fScintTree->Branch("intPDGCode",&fIntPDGCode,"intPDGCode/I");

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
void Analysis::addScintHits(const ScintillatorHitsCollection *hitCol) 
{
  if (!Data->CreateNtuple) return;

  TClonesArray &theHits = *fScintHitArray;
  fCountHits=0;


  G4RunManager* pRunManager = G4RunManager::GetRunManager();
  fRun = pRunManager->GetCurrentRun()->GetRunID();
  fEvent = pRunManager->GetCurrentEvent()->GetEventID();
  const G4Event *aEvent = pRunManager->GetCurrentEvent();
  
  fIntPos[0]=aEvent->GetPrimaryVertex()->GetX0();
  fIntPos[1]=aEvent->GetPrimaryVertex()->GetY0();
  fIntPos[2]=aEvent->GetPrimaryVertex()->GetZ0();
  G4PrimaryParticle *aParticle = aEvent->GetPrimaryVertex()->GetPrimary();
  fIntMom[0]=aParticle->GetPx();
  fIntMom[1]=aParticle->GetPy();
  fIntMom[2]=aParticle->GetPz();
  fIntEng=TMath::Sqrt(aParticle->GetMass()*aParticle->GetMass() +
		      fIntMom[0]*fIntMom[0]+
		      fIntMom[1]*fIntMom[1]+
		      fIntMom[2]*fIntMom[2]);
  fPhi=TMath::ATan2(fIntMom[1],fIntMom[0]);
  fTheta=TMath::ATan2(TMath::Sqrt(fIntMom[0]*fIntMom[0]+fIntMom[1]*fIntMom[1]),TMath::Abs(fIntMom[2]));
  fIntPDGCode=aParticle->GetPDGcode();
  for(int i=0;i<fTotNumScintStrips;i++) {
    ScintillatorHit* aHit = (*hitCol)[i];
    //Check if there was a hit
    if((aHit->GetLogV())) {
      Double_t pos[3]={aHit->GetTruePos()[0],aHit->GetTruePos()[1],aHit->GetTruePos()[2]};
      Int_t side=(aHit->GetPlane()/fNumScintPlanes);
      new(theHits[fCountHits])
	ScintHitInfo(side,aHit->GetPlane(),aHit->GetStrip(),
		     pos,aHit->GetEdep());
      fCountHits++;
    }
  }	  
  if(fCountHits>0) {
    fScintTree->Fill();
    fScintHitArray->Clear();
  }

}
//----------------------------------------------------------------------


