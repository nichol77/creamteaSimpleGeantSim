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
  G4double abundance;
  G4int iz, n, ncomponents;                       //iz=nb of protons  in an isotope; 
 
  G4String symbol,name;
  G4double density;//, mass_percent;
  G4Element* elFe = new G4Element("Iron", "Fe", 26, 55.85*g/mole);
  A = 14.01*g/mole;
  G4Element* elN = new G4Element(name="Nitrogen", symbol="N", Z=7.,A);
  A = 16.00*g/mole;
  G4Element* elO  = new G4Element(name="Oxygen"  ,symbol="O" , Z= 8, A);
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

  //
  // define an Element from isotopes, by relative abundance 
  //
  
  G4Isotope* U5 = new G4Isotope(name="U235", iz=92, n=235, A=235.01*g/mole);
  G4Isotope* U8 = new G4Isotope(name="U238", iz=92, n=238, A=238.03*g/mole);
  
  G4Element* elU  = new G4Element(name="enriched Uranium", symbol="U", ncomponents=2);
  elU->AddIsotope(U5, abundance= 90.*perCent);
  elU->AddIsotope(U8, abundance= 10.*perCent);
  
  G4Material *uranium = new G4Material("uranium",SPHERE_DENSITY_KG_M3*kg/m3,1);
  uranium->AddElement(elU,100*perCent);
  
  
  std::cout << "Adding sphere of radius " << SPHERE_RADIUS_CM << "cm"
	    << " and density " << SPHERE_DENSITY_KG_M3 << "at\t"
	    << SPHERE_X_M*m << "," << SPHERE_Y_M*m << "," << SPHERE_Z_M*m 
	    << "\n";
  G4VSolid *sSphereU = new G4Sphere ("sphereU", //name
				     0,             // inner radius
				     SPHERE_RADIUS_CM*cm,  // outer radius
				     0,             // start phi
				     360*deg,       // end phi
				     0,             // start theta
				     180*deg);      // end theta
  G4LogicalVolume *lvSphereU = new G4LogicalVolume(sSphereU,uranium,"lvSphereU");
  G4VPhysicalVolume *pvSphereU = new G4PVPlacement (0,G4ThreeVector (SPHERE_X_M*m,SPHERE_Y_M*m,SPHERE_Z_M*m), "pvSphereU",lvSphereU,pvWorld, false,0);        
  
}

