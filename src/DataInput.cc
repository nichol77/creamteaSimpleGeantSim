#include "DataInput.hh"
#include "G4ThreeVector.hh"
#include "DetectorDefs.hh"
#include <math.h>

static const G4double inch=2.54*cm;
static const G4double ft=12*2.54*cm;

DataInput* DataInput::fDataInput = 0;

DataInput* DataInput::GetDataInput()
{
  if(!fDataInput)
    return new DataInput();
  return fDataInput;
}

DataInput::DataInput()
{
  if (fDataInput){ 
    G4Exception("DataInput constructed twice.");
  }
  fDataInput = this;
  WorldX = WORLD_SIZE*m;
  WorldY = WORLD_SIZE*m;
  WorldZ = WORLD_SIZE*m;
  KillTracking = false;
  KillTrackingEnergy = .05*MeV;
  CreateNtuple = true;
  NtupleName = "scintHits.root";
}

//----------------------------------------------------------------------

G4bool DataInput::GetKillTracking(){
  return KillTracking;
}

//----------------------------------------------------------------------

G4double DataInput::GetKillTrackingThreshold(){
  return KillTrackingEnergy;
}


