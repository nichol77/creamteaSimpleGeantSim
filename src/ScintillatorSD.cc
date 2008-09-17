//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: ScintillatorSD.cc,v 1.6 2006/06/29 16:32:33 gunter Exp $
// --------------------------------------------------------------
//
#include "ScintillatorSD.hh"
#include "ScintillatorHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "../../global_vars.hh"

ScintillatorSD::ScintillatorSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="ScintillatorColl");
  HCID = -1;
  float boxSize = SIDELENGTH; //allows all the scintillator boxed to be scaled from here. 
  #include "DetectorParams.icc"
  fTotNumScintStrips=2*fNumScintPlanes*fNumScintStrips;
     

}

ScintillatorSD::~ScintillatorSD(){;}

void ScintillatorSD::Initialize(G4HCofThisEvent*HCE)
{
  hitsCollection = new ScintillatorHitsCollection
                   (SensitiveDetectorName,collectionName[0]);
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection); }
  HCE->AddHitsCollection(HCID,hitsCollection);

  for(int plane=0;plane<fNumScintPlanes*2;plane++) { //*2 for top & bottom
     for(int strip=0;strip<fNumScintStrips;strip++) {
	ScintillatorHit *aHit = new ScintillatorHit(plane,strip);
	hitsCollection->insert(aHit);
     }
  }

}

G4bool ScintillatorSD::ProcessHits(G4Step*aStep,G4TouchableHistory* /*ROhist*/)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  if(edep==0.) return true;

  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  G4VPhysicalVolume* thePhysical = theTouchable->GetVolume();
  G4ThreeVector thePos=preStepPoint->GetPosition();

  G4int planeNum=0;
  G4int stripNum=0;

  //There is almost certainly a better way to determine which plane and strip
  //but for now this lazy method will just about work
  sscanf(thePhysical->GetName().data(),
	 "av_1_impr_%d_lvScintStrip_pv_%d",
	 &planeNum,&stripNum);

  //  G4cout << edep << "\t" << thePhysical->GetName() << "\t"
  //	 << thePos.getX() << "\t" << thePos.getY() << "\t"
  //	 << thePos.getZ() << "\t" << planeNum << "\t" << stripNum << "\n";
  
  int logInd=(stripNum-1) + fNumScintStrips*(planeNum-1);

  ScintillatorHit* aHit = (*hitsCollection)[logInd];
  // check if it is first touch
  if(!(aHit->GetLogV()))
  {
    // fill volume information
    aHit->SetLogV(thePhysical->GetLogicalVolume());
    G4AffineTransform aTrans = theTouchable->GetHistory()->GetTopTransform();
    aTrans.Invert();
    aHit->SetRot(aTrans.NetRotation());
    aHit->SetPos(aTrans.NetTranslation());
  }
  // add energy deposition
  aHit->AddEdep(edep);

  return true;
}

void ScintillatorSD::EndOfEvent(G4HCofThisEvent* /*HCE*/)
{  
   for(int i=0;i<fTotNumScintStrips;i++) {
      ScintillatorHit* aHit = (*hitsCollection)[i];
      //Check if there was a hit
      if((aHit->GetLogV())) {
	 aHit->Print();
      }
   }	  
}

