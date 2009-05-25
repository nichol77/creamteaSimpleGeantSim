//
// RunManager.cc
//

#include "G4RunManager.hh"
#include "RunManager.hh"
#include "TStopwatch.h"
#include "TTime.h"

RunManager::RunManager(){;}

RunManager::~RunManager(){;}

void RunManager::BeamOn(G4int n_event, const char* placeholder, G4int n_select)
{
  nEvents = n_event;
  G4bool runOn(true);
  G4bool cond = ConfirmBeamOnCondition();
   if(cond)
     {

       if (runOn){
	 TStopwatch *sWatch=new TStopwatch();
	 sWatch->Start(true);

	 numberOfEventToBeProcessed = n_event;
	 RunInitialization();

	 if(n_event>0){
	   DoEventLoop(n_event, placeholder, n_select);
	 }

	 RunTermination();
	 
	 sWatch->Stop();
	 G4cout << "Processed " << n_event << " particles in ";
	 G4cout.precision(3);
	 G4cout << sWatch->RealTime() <<  " s" << G4endl;
	 delete sWatch;
       }
     }
}

