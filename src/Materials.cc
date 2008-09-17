#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "DataInput.hh"

void DetectorConstruction::DefineMaterials(){

  //------------------------------------------------------ materials

  G4double A;  // atomic mass
  G4double Z;  // atomic number
  G4String symbol,name;
  G4double density, mass_percent;

  // Air and Vacuum
  A = 1.01*g/mole;
  G4Element* elH  = new G4Element(name="Hydrogen",symbol="H" , Z= 1, A);

  //A = 4.003*g/mole; 
  //G4Element* elHe  = new G4Element(name="Helium",symbol="He" , Z= 2, A);

  A = 12.01*g/mole;
  G4Element* elC  = new G4Element(name="Carbon"  ,symbol="C" , Z = 6, A);

  A = 14.01*g/mole;
  G4Element* elN = new G4Element(name="Nitrogen", symbol="N", Z=7.,A);

  A = 16.00*g/mole;
  G4Element* elO  = new G4Element(name="Oxygen"  ,symbol="O" , Z= 8, A);

  A = 22.99*g/mole; 
  G4Element* elNa  = new G4Element(name="Natrium"  ,symbol="Na" , Z=11 , A);

  A = 24.305*g/mole;  
  G4Element* elMg  = new G4Element(name="Magnesium"  ,symbol="Mg" , Z=12 , A); 

  A = 26.98*g/mole; 
  G4Element* elAl  = new G4Element(name="Aluminum"  ,symbol="Al" , Z=13, A);

  A = 28.09*g/mole;
  G4Element* elSi  = new G4Element(name="Silicon", symbol="Si", Z=14, A);

  A = 30.974*g/mole; 
  G4Element* elP  = new G4Element(name="Phosphorus"  ,symbol="P" , Z=15 , A);

  A = 32.065*g/mole; 
  G4Element* elS  = new G4Element(name="Sulfur"  ,symbol="S" , Z=16 , A);

  //A = 39.948*g/mole;
  //G4Element* elAr = new G4Element(name="Argon" , symbol="Ar", Z=18, A);

  A = 39.1*g/mole; 
  G4Element* elK  = new G4Element(name="Potassium"  ,symbol="K" , Z=19 , A);

  A = 40.09*g/mole; 
  G4Element* elCa  = new G4Element(name="Calcium"  ,symbol="Ca" , Z=20 , A);

  A = 47.867*g/mole; 
  G4Element* elTi  = new G4Element(name="Titanium"  ,symbol="Ti" , Z=22 , A);

  A = 51.9961*g/mole; 
  G4Element* elCr  = new G4Element(name="Chromium"  ,symbol="Cr" , Z=24 , A);

  A = 54.938*g/mole; 
  G4Element* elMn  = new G4Element(name="Manganese"  ,symbol="Mn" , Z=25 , A);

  A = 55.85*g/mole;
  G4Element* elFe = new G4Element(name="Iron"    ,symbol="Fe", Z=26, A);

  A = 58.6934*g/mole;
  G4Element* elNi = new G4Element(name="Nickel"    ,symbol="Ni", Z=28, A);

  A = 63.546*g/mole;
  G4Element* elCu = new G4Element(name="Copper"    ,symbol="Cu", Z=29, A);

  A = 69.72*g/mole; 
  G4Element* elGa  = new G4Element(name="Gallium"  ,symbol="Ga" , Z=31 , A);

  A = 200.59*g/mole; 
  G4Element* elHg  = new G4Element(name="Mercury"  ,symbol="Hg" , Z=80, A);

  A = 238.0289*g/mole; 
  G4Element* elU  = new G4Element(name="Uranium"  ,symbol="U" , Z=92, A);

  //--------------------------------------------------
  // Molecules and other non-element materials

  G4int natoms;

  density = 1.29*mg/cm3; 
  Air = new G4Material("Air", density, 2); //number of components =2
  Air->AddElement(elN, 70*perCent); //mass fraction =70%
  Air->AddElement(elO, 30*perCent); // 30%

  density = 1.032*g/cm3;
  Scintillator =  new G4Material("Scintillator", density, 2);
  Scintillator->AddElement(elC, natoms=9);
  Scintillator->AddElement(elH, natoms=10);

  density = 1.*g/cm3; 
  Water = new G4Material("Water", density, 2); //number of components =2
  Water->AddElement(elH, natoms=2); 
  Water->AddElement(elO, natoms=1); 

  density = 2.376e-15*g/cm3;
  G4double temperature=300.*kelvin;
  G4double pressure=2.0e-7*bar;
  Vacuum = new G4Material("Vacuum", density, 1, kStateGas,temperature,pressure);
  Vacuum-> AddMaterial(Air, 1.);

  //other materials  
  He = new G4Material("Helium", Z=2., A=4.0026*g/mole, density= 0.1785*kg/m3,kStateGas,300*kelvin,2.55*atmosphere);
  Be = new G4Material("Berillium", Z=4.,A=9.01*g/mole, density=1.848*g/cm3);
  C =  new G4Material("Carbon", Z=6., A=12.01*g/mole, density= 1.83*g/cm3);
  Al = new G4Material("Aluminum", Z= 13., A= 26.98*g/mole, density= 2.7*g/cm3);
  Ar = new G4Material("Argon", Z= 18, A=39.948*g/mole,1.784*kg/m3,kStateGas,300*kelvin,atmosphere);
  Pb = new G4Material("Lead", Z= 82., A= 207.19*g/mole, density= 11.35*g/cm3);
  Fe = new G4Material("Iron", Z= 26., A=55.85*g/mole, density= 7.86999*g/cm3);
  U = new G4Material("Uranium", Z= 92., A=238.0239*g/mole, density= 18.95*g/cm3);

}

G4Material* DetectorConstruction::GetMaterial(G4int matcode)
{
  if (matcode == 1) return Air;
  if (matcode == 2) return Ar;
  if (matcode == 3) return Al;
  if (matcode == 4) return Pb;
  if (matcode == 5) return He;
  if (matcode == 6) return C;
  if (matcode == 7) return Fe;
  if (matcode == 8) return U;

  G4cout << G4endl << " **** Wrong material code **** " << matcode << G4endl << G4endl;
  return Vacuum;
}
