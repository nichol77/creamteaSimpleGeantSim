//
//----------------------------------------------------------------------
// Author: rjn@hep.ucl.ac.uk -- based on work by D. Jason Koskinen
// Date: 10/09/08 
//
// 
//----------------------------------------------------------------------
//----------------------------------------------------------------------
#include "TargetVolume.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Para.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4AssemblyVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4PVDivision.hh"
#include "G4SDManager.hh"
#include "DetectorDefs.hh"
#include "Analysis.hh"
#include "globals.hh"

TargetVolume::TargetVolume() {
  //Default Constructor
}

TargetVolume::~TargetVolume() {
  //Default Destructor
}

void TargetVolume::constructTarget(G4VPhysicalVolume *pvWorld)
{
  //This is just going to construct a simple sphere of steel and air
  
  //Define the materials
  G4double A;  // atomic mass
  G4double Z;  // atomic number
  G4String symbol,name;
  G4double density;//, mass_percent;
  G4Element* elFe = new G4Element("Iron", "Fe", 26, 55.85*g/mole);
  A = 14.01*g/mole;
  G4Element* elN = new G4Element(name="Nitrogen", symbol="N", Z=7.,A);
  A = 16.00*g/mole;
  G4Element* elO  = new G4Element(name="Oxygen"  ,symbol="O" , Z= 8, A);
  // steel
  G4Material* steel = new G4Material ("steel", 7800*kg/m3, 1);
  steel->AddElement (elFe, 100*perCent);
  //aproximatation of steel nails.
  density = 1.29*mg/cm3; 
  G4Material *Air = new G4Material("Air", density, 2); //number of components =2
  Air->AddElement(elN, 70*perCent); //mass fraction =70%
  Air->AddElement(elO, 30*perCent); // 30%
  G4Material* steelNails = new G4Material ("steelNails", SPHERE_DENSITY_KG_M3*kg/m3, 2);
  steelNails->AddMaterial (Air, 22*perCent);
  steelNails->AddElement (elFe, 78*perCent);


  
  
  std::cout << "Adding sphere of radius " << SPHERE_RADIUS_CM << "cm"
	    << " and density " << SPHERE_DENSITY_KG_M3 << "\n";
  G4VSolid *sSphereNails = new G4Sphere ("sphereNails", //name
					 0,             // inner radius
					   SPHERE_RADIUS_CM*cm,  // outer radius
					   0,             // start phi
					   360*deg,       // end phi
					 0,             // start theta
					 180*deg);      // end theta
  G4LogicalVolume *lvSphereNails = new G4LogicalVolume(sSphereNails,steelNails, "lvSphereNails");
  G4VPhysicalVolume *pvSphereNails = new G4PVPlacement (0,G4ThreeVector (0,0,0), "pvSphereNails",lvSphereNails,pvWorld, false,0);        

}

