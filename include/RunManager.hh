//
// RunManager.hh
//

#ifndef RunManager_h
#define RunManager_h 1

#include "G4RunManager.hh"

class PrimaryGeneratorAction;

class RunManager : public G4RunManager
{
 public:
  RunManager();
  virtual ~RunManager();

  virtual void BeamOn(G4int n_event, const char *, G4int n_select=-1);
  inline G4int GetNumberOfEvents(){
    return numberOfEventToBeProcessed;
  }

  G4int nEvents;

};

#endif
