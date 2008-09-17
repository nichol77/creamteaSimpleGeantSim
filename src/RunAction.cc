//
// NumiRunAction.cc
//

#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "RunAction.hh"
#include "Analysis.hh"
#include "DataInput.hh"
#include "Randomize.hh"
#include "RunManager.hh"

RunAction::RunAction()
{  
}


RunAction::~RunAction()
{ 
}


void RunAction::BeginOfRunAction(const G4Run* aRun)
{

  RunManager *pRunManager = (RunManager*)RunManager::GetRunManager();
  G4cout << "Starting run " << aRun->GetRunID()<<G4endl;

  G4cout << "Processing " << pRunManager->GetNumberOfEvents() << " particles" << G4endl;

  //--------------------------------------------------
  //Book histograms and ntuples
  Analysis* analysis = Analysis::getInstance();
  analysis->book(); 
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  G4cout << "Ending run: " << aRun->GetRunID() << G4endl;
  Analysis* analysis = Analysis::getInstance();
  analysis->finish();
}




















