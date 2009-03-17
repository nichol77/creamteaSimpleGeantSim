#ifndef DataInput_h
#define DataInput_h 1

#include "globals.hh"
#include "G4ThreeVector.hh"
#include <vector>

class DataInput
{
 public:
  DataInput();
  ~DataInput();
  G4double GetKillTrackingThreshold();
  G4bool GetKillTracking();
  
  void setWorldXYZ(G4double x, G4double y, G4double z);
  static DataInput* GetDataInput();
 
 private:
  static DataInput* fDataInput;
    
 public:
  G4double WorldX, WorldY, WorldZ;
  G4bool CreateNtuple, KillTracking;
  G4double KillTrackingEnergy;
  G4String NtupleName;

  
};
#endif
