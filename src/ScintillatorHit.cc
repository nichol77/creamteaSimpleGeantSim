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
// $Id: ScintillatorHit.cc,v 1.12 2006/11/14 07:11:19 perl Exp $
// --------------------------------------------------------------
//

#include "ScintillatorHit.hh"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4ios.hh"

G4Allocator<ScintillatorHit> ScintillatorHitAllocator;

ScintillatorHit::ScintillatorHit()
{
  fPlaneNum = -1;
  fStripNum = -1;
  edep = 0.;
  pLogV = 0;
}

ScintillatorHit::ScintillatorHit(G4int planeNum, G4int stripNum)
{
   fPlaneNum=planeNum;
   fStripNum=stripNum;
   edep = 0.;
   pLogV = 0;
}

ScintillatorHit::~ScintillatorHit()
{;}

ScintillatorHit::ScintillatorHit(const ScintillatorHit &right)
    : G4VHit() {
   fPlaneNum=right.fPlaneNum;
   fStripNum=right.fStripNum;
  edep = right.edep;
  pos = right.pos;
  fTruePos = right.fTruePos;
  rot = right.rot;
  pLogV = right.pLogV;
}

const ScintillatorHit& ScintillatorHit::operator=(const ScintillatorHit &right)
{
  fStripNum = right.fStripNum;
  fPlaneNum = right.fPlaneNum;
  edep = right.edep;
  pos = right.pos;
  fTruePos = right.fTruePos;
  rot = right.rot;
  pLogV = right.pLogV;
  return *this;
}

int ScintillatorHit::operator==(const ScintillatorHit &right) const
{
  return (fPlaneNum==right.fPlaneNum && fStripNum==right.fStripNum);
}

void ScintillatorHit::weightTruePos(G4ThreeVector xyz, G4double energy)
{
  edep+=energy;
  sumX+=energy*xyz[0];
  sumY+=energy*xyz[1];
  sumZ+=energy*xyz[2];

  fTruePos[0]=sumX/edep;
  fTruePos[1]=sumY/edep;
  fTruePos[2]=sumZ/edep;

  countHits++;

  //  G4cout << sumZ << "\t" << fTruePos[2] << "\n";

}

void ScintillatorHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager&&(edep>0.))
  {
    // Draw a calorimeter cell with a color corresponding to its energy deposit
    G4Transform3D trans(rot.inverse(),pos);
    G4VisAttributes attribs;
    const G4VisAttributes* pVA = pLogV->GetVisAttributes();
    if(pVA) attribs = *pVA;
    G4double rcol = edep/(0.7*GeV);
    if(rcol>1.) rcol = 1.;
    if(rcol<0.4) rcol = 0.4;
    G4Colour colour(rcol,0.,0.);
    attribs.SetColour(colour);
    attribs.SetForceSolid(true);
    pVVisManager->Draw(*pLogV,attribs,trans);
  }
}

const std::map<G4String,G4AttDef>* ScintillatorHit::GetAttDefs() const
{
  G4bool isNew;
  std::map<G4String,G4AttDef>* store
    = G4AttDefStore::GetInstance("ScintillatorHit",isNew);
  if (isNew) {
    G4String HitType("HitType");
    (*store)[HitType] = G4AttDef(HitType,"Hit Type","Physics","","G4String");

    G4String Plane("Plane");
    (*store)[Plane] = G4AttDef(Plane,"Plane","Physics","","G4int");

    G4String Strip("Strip");
    (*store)[Strip] = G4AttDef(Strip,"Plane","Physics","","G4int");

    G4String Energy("Energy");
    (*store)[Energy] = G4AttDef(Energy,"Energy Deposited","Physics","G4BestUnit","G4double");

    G4String Pos("Pos");
    (*store)[Pos] = G4AttDef(Pos, "Position",
		      "Physics","G4BestUnit","G4ThreeVector");

    G4String LVol("LVol");
    (*store)[LVol] = G4AttDef(LVol,"Logical Volume","Physics","","G4String");
  }
  return store;
}

std::vector<G4AttValue>* ScintillatorHit::CreateAttValues() const
{
  std::vector<G4AttValue>* values = new std::vector<G4AttValue>;

  values->push_back(G4AttValue("HitType","ScintillatorHit",""));

  values->push_back
    (G4AttValue("Plane",G4UIcommand::ConvertToString(fPlaneNum),""));

  values->push_back
    (G4AttValue("Strip",G4UIcommand::ConvertToString(fStripNum),""));

  values->push_back
    (G4AttValue("Energy",G4BestUnit(edep,"Energy"),""));

  values->push_back
    (G4AttValue("Pos",G4BestUnit(pos,"Length"),""));

  if (pLogV)
    values->push_back
      (G4AttValue("LVol",pLogV->GetName(),""));
  else
    values->push_back
      (G4AttValue("LVol"," ",""));
  
   return values;
}

void ScintillatorHit::Print()
{
   G4cout << "  Plane[" << fPlaneNum << "] Strip[" <<fStripNum << "] "
	  << edep/MeV << " (MeV)" << G4endl;
}


