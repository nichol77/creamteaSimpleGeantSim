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
// $Id: ScintillatorHit.hh,v 1.5 2006/06/29 16:31:02 gunter Exp $
// --------------------------------------------------------------
//
#ifndef ScintillatorHit_h
#define ScintillatorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class G4AttDef;
class G4AttValue;

class ScintillatorHit : public G4VHit
{
  public:
  
  ScintillatorHit();
  ScintillatorHit(G4int plane, G4int strip);
  virtual ~ScintillatorHit();
  ScintillatorHit(const ScintillatorHit &right);
  const ScintillatorHit& operator=(const ScintillatorHit &right);
  int operator==(const ScintillatorHit &right) const;
  
  inline void *operator new(size_t);
  inline void operator delete(void *aHit);
  
  virtual void Draw();
  virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
  virtual std::vector<G4AttValue>* CreateAttValues() const;
  virtual void Print();
  void zeroCounters() { countHits=0; sumX=0; sumY=0; sumZ=0; edep=0;}
  void weightTruePos(G4ThreeVector xyz, G4double eDep);

  private:
  G4int countHits;
  G4double sumX;
  G4double sumY;
  G4double sumZ;
  G4int fPlaneNum;
  G4int fStripNum;
  G4ThreeVector fTruePos;
  G4double edep;
  G4ThreeVector pos; //For drawing
  G4RotationMatrix rot; //For drawing
  const G4LogicalVolume* pLogV; //For drawing

  public:
      inline void SetPlane(G4int plane) { fPlaneNum=plane; }
      inline G4int GetPlane() const { return fPlaneNum; }
      inline void SetStrip(G4int strip) { fStripNum=strip; }
      inline G4int GetStrip() const { return fStripNum; }
      inline void SetEdep(G4double de) { edep = de; }
      inline void AddEdep(G4double de) { edep += de; }
      inline G4double GetEdep() const { return edep; }
      inline void SetPos(G4ThreeVector xyz) { pos = xyz; }
      inline G4ThreeVector GetPos() const { return pos; }
      inline void SetTruePos(G4ThreeVector xyz) { fTruePos = xyz; }
      inline G4ThreeVector GetTruePos() const { return fTruePos; }
      inline void SetRot(G4RotationMatrix rmat) { rot = rmat; }
      inline G4RotationMatrix GetRot() const { return rot; }
      inline void SetLogV(G4LogicalVolume* val) { pLogV = val; }
      inline const G4LogicalVolume* GetLogV() const { return pLogV; }
};

typedef G4THitsCollection<ScintillatorHit> ScintillatorHitsCollection;

extern G4Allocator<ScintillatorHit> ScintillatorHitAllocator;

inline void* ScintillatorHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*)ScintillatorHitAllocator.MallocSingle();
  return aHit;
}

inline void ScintillatorHit::operator delete(void* aHit)
{
  ScintillatorHitAllocator.FreeSingle((ScintillatorHit*) aHit);
}

#endif


