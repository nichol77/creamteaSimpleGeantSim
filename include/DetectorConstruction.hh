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
//
// $Id: DetectorConstruction.hh,v 1.6 2006/06/29 17:47:13 gunter Exp $
// GEANT4 tag $Name: geant4-08-01 $
//

#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "DataInput.hh"

class G4Box;
class G4Material;
class G4LogicalVolume;
class G4VPhysicalVolume;
class DataInput;

class DetectorConstruction : public G4VUserDetectorConstruction
{
 public:
  
  DetectorConstruction();
  ~DetectorConstruction();
  
  G4VPhysicalVolume* Construct();
  
 private:

  G4Box*              sWorld;   // Pointer to the solid world
  G4LogicalVolume*    lvWorld;  // pointer to the logical world
  G4VPhysicalVolume*  pvWorld;  // pointer to the physical world

   G4Box*              sBoxTop; //Pointer to the solid top box
   G4LogicalVolume*   lvBoxTop; //Pointer to the logical top box
   G4VPhysicalVolume* pvBoxTop; //Pointer to the physical top box

#include "DetectorParams.hh"


  DataInput* Data;
  
  void DefineMaterials();

  G4Material* GetMaterial(G4int matcode);

  G4Material *Water;
  G4Material *Ar;
  G4Material *He;
  G4Material *Be;
  G4Material *C;
  G4Material *Fe;
  G4Material *Al;
  G4Material *Pb;
  G4Material *Air;
  G4Material *Vacuum;
  G4Material *Scintillator;
  G4Material *U;

};

#endif

