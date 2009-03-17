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
// $Id: DetectorMessenger.cc,v 1.11 2006/06/29 17:48:02 gunter Exp $
// GEANT4 tag $Name: geant4-09-01-patch-03 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction* myDet)
:myDetector(myDet)
{ 
  creamteaDir = new G4UIdirectory("/creamtea/");
  creamteaDir->SetGuidance("UI commands specific to the CREAM TEA setup.");
  
  detDir = new G4UIdirectory("/creamtea/det/");
  detDir->SetGuidance("detector control.");
  
  NumPlanesCmd = new G4UIcmdWithAnInteger("/creamtea/det/setNumPlanes",this);  
  NumPlanesCmd->SetGuidance("Set Number of Scintillator Planes.");
  NumPlanesCmd->SetParameterName("NumPlanes",false);

  NumStripsCmd = new G4UIcmdWithAnInteger("/creamtea/det/setNumStrips",this);  
  NumStripsCmd->SetGuidance("Set Number of Scintillator Strips.");
  NumStripsCmd->SetParameterName("NumStrips",false);

  PlaneGapCmd = new G4UIcmdWithADoubleAndUnit("/creamtea/det/setPlaneGap",this);  
  PlaneGapCmd->SetGuidance("Set Gap Between Scintillator Planes.");
  PlaneGapCmd->SetParameterName("PlaneGap",false);

  PlaneLengthCmd = new G4UIcmdWithADoubleAndUnit("/creamtea/det/setPlaneLength",this);  
  PlaneLengthCmd->SetGuidance("Set Length of Scintillator Planes.");
  PlaneLengthCmd->SetParameterName("PlaneLength",false);

  PlaneWidthCmd = new G4UIcmdWithADoubleAndUnit("/creamtea/det/setPlaneWidth",this);  
  PlaneWidthCmd->SetGuidance("Set Width Between Scintillator Planes.");
  PlaneWidthCmd->SetParameterName("PlaneWidth",false);

  WorldSizeCmd = new G4UIcmdWithADoubleAndUnit("/creamtea/det/setWorldSize",this);  
  WorldSizeCmd->SetGuidance("Set World Size");
  WorldSizeCmd->SetParameterName("WorldSize",false);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  //  delete TargMatCmd;
  //  delete ChamMatCmd;
  delete NumPlanesCmd;
  delete NumStripsCmd;
  delete PlaneGapCmd;
  delete PlaneLengthCmd;
  delete PlaneWidthCmd;
  delete WorldSizeCmd;
  delete detDir;
  delete creamteaDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
 //  if( command == TargMatCmd )
//    { myDetector->setTargetMaterial(newValue);}
   
  
  if( command == NumPlanesCmd )
   { myDetector->setNumScintPlanes(NumPlanesCmd->GetNewIntValue(newValue));}

  if( command == NumStripsCmd )
   { myDetector->setNumScintStrips(NumStripsCmd->GetNewIntValue(newValue));}

  if( command == PlaneGapCmd )
   { myDetector->setScintPlaneGap(PlaneGapCmd->GetNewDoubleValue(newValue));}

  if( command == PlaneLengthCmd )
   { myDetector->setScintPlaneLength(PlaneLengthCmd->GetNewDoubleValue(newValue));}

  if( command == PlaneWidthCmd )
   { myDetector->setScintPlaneWidth(PlaneWidthCmd->GetNewDoubleValue(newValue));}

  if( command == WorldSizeCmd )
   { myDetector->setWorldSize(WorldSizeCmd->GetNewDoubleValue(newValue));}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
