//
// SteppingAction.cc
//

#include "SteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4TrajectoryContainer.hh"
#include "G4RunManager.hh"
#include "Analysis.hh"



SteppingAction::SteppingAction()
{
  G4cout << "stepping action" << G4endl;
}

SteppingAction::~SteppingAction()
{
}


void SteppingAction::UserSteppingAction(const G4Step * theStep)
{

  G4Track *theTrack = theStep->GetTrack();

  //--------------------------------------------------
  // Checks to see whether the particle has entered the 
  // scintillator, and if so calls the Analysis class to 
  // record the particle  properties.-DJK

  if (theStep->GetPostStepPoint()->GetPhysicalVolume()!=NULL)
    {

    //--------------------------------------------------
    // Debuggin tool to follow the particle along each 
    // step. Outputs the volume at each step.

    //    G4cout << theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() << G4endl;


    //--------------------------------------------------
    // Establishes if the particel is the Scintillator 
    // section of the nested boxes. If the particle is
    // in the Scintillator then the G4Track object is
    // passed to the Analysis class to, fittingly 
    // enough, get analyzed. 

      

 //    if (theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "pvBox0_outer"){
//       Analysis* analysis = Analysis::getInstance();
//       analysis->FillNtuple(*theTrack,0);
//     }
//     if (theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "pvBox1_outer"){
//       Analysis* analysis = Analysis::getInstance();
//       analysis->FillNtuple(*theTrack,1);
//     }
//     if (theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "pvBox2_outer"){
//       Analysis* analysis = Analysis::getInstance();
//       analysis->FillNtuple(*theTrack,2);
//     }
  }  
}


