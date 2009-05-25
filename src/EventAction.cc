//
// NumiEventAction.cc
//

#include "G4Event.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "EventAction.hh"
#include "Analysis.hh"
#include "Randomize.hh"

EventAction::EventAction()
{  
}


EventAction::~EventAction()
{ 
}


void EventAction::BeginOfEventAction(const G4Event* aEvent)
{
  //In here we tag useful info such as the particles initial 
  //energy and trajectory etc.
  G4cout << aEvent->GetPrimaryVertex() << "\n";
}



void EventAction::EndOfEventAction(const G4Event* aEvent)
{
 
}




















