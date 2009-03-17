//
//----------------------------------------------------------------------
// Author: D. Jason Koskinen
// Date: 5/30/07 
//
// The following code establishes the Detector geometry and location.
// 
// Note: All the dimensions for Geant4 solids are half lengths since 
// everything is determined from the center of the solid.  
// A 1m x 2m x 3m box will have to be declared as having a 0.5m distance 
// from the center of the box in the x direction 1m dist. in Y etc... 
// The principle of center of the solid as being the reference point 
// also holds when placing the solid in the MC. The G4PVPlacement refers 
// to the (x, y, z) location of the center of the solid within its
// associated mother volume. The World volume is the only volume that 
// does not explicitly require a mother volume. 
//----------------------------------------------------------------------
//----------------------------------------------------------------------
#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "ScintillatorSD.hh"

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


DetectorConstruction::DetectorConstruction(){
  Data = DataInput::GetDataInput();
  DefineMaterials();

  fWorldSize=WORLD_SIZE*m;
  fNumScintPlanes=PLANES_PER_SIDE;
  fScintPlaneGap=GAP_BETWEEN_PLANES_CM*cm;
  fScintPlaneLength=SIDELENGTH*m;
  fScintPlaneWidth=PLANE_WIDTH_CM*cm;
  fNumScintStrips=STRIPS_PER_PLANE;
  fRotate90=ROTATE_EVERY_PLANE;
  fTotNumScintStrips=2*fNumScintPlanes*fNumScintStrips;	
  detectorMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction()
{
  delete detectorMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // ---------------------------- Materials to use
  Data->setWorldXYZ(fWorldSize,fWorldSize,fWorldSize);
  G4Element* elFe = new G4Element("Iron", "Fe", 26, 55.85*g/mole);

  // steel
  G4Material* steel = new G4Material ("steel", 7800*kg/m3, 1);
  steel->AddElement (elFe, 100*perCent);

  //aproximatation of steel nails.
  G4Material* steelNails = new G4Material ("steelNails", 7800*kg/m3, 2);
  steelNails->AddMaterial (Air, 22*perCent);
  steelNails->AddElement (elFe, 78*perCent);


  //  float fWorldSize = fWorldSize; //SIDELENGTH; //allows all the scintillator boxed to be scaled from here. 


  G4double scintStripWidth=fScintPlaneLength/fNumScintStrips;
  
  G4cout << "World Size: " << fWorldSize << "\n";
  G4cout << "Plane Length: " << fScintPlaneLength << "\n";
  G4cout << "Plane Width: " << fScintPlaneWidth << "\n";
  G4cout << "Plane Gap: " << fScintPlaneGap << "\n";
  G4cout << "Num planes: " << fNumScintPlanes << "\n";
  G4cout << "Num strips: " << fNumScintStrips << "\n";
  G4cout << "Strip Width: " << scintStripWidth << "\n";
  //  G4cout << fScintPlaneLength << "\t" << fNumScintStrips << "\t" << scintStripWidth << "\n";
  


  //------------------------------ experimental hall (world volume)

  sWorld = new G4Box("sWorld", Data->WorldX/2, Data->WorldY/2, Data->WorldZ/2);

  lvWorld = new G4LogicalVolume(sWorld,	 Air, "lvWorld");

  pvWorld = new G4PVPlacement(0, G4ThreeVector(0.0,0.0,0.0), lvWorld, "pvWorld", 0, false, 0);

  //--------------------------------------------------
  // For now what we'll try and do is just make three scintillator planes at the top, 
  // and three at the bottom. 

  
  //Now lets try and make a scintillator plane stack
  //Define a scintillator strip x is the width, y is the length, z is the thickness
  G4Box *scintStripBox = new G4Box("scintStripBox",scintStripWidth/2.,
				   fScintPlaneLength/2.,fScintPlaneWidth/2.);
  G4LogicalVolume *lvScintStrip 
     = new G4LogicalVolume(scintStripBox,Scintillator,"lvScintStrip",0,0,0);

  //First we'll assemble all the strips in one plane then, we'll try and stack the planes
  G4AssemblyVolume *assemblyDetector = new G4AssemblyVolume();
  
  //These are the roatation and translation of the strip in the plane
  G4RotationMatrix Ra;
  G4ThreeVector Ta;

  Ta.setY(0);
  Ta.setZ(0);
  for(G4int stripNum=0;stripNum<fNumScintStrips;stripNum++) {
     Ta.setX(-fScintPlaneLength/2. + (stripNum+0.5)*scintStripWidth);
     //     G4cout << Ta.getX() << "\n";
     assemblyDetector->AddPlacedVolume(lvScintStrip,Ta,&Ra);
  }
  
  //So now we have hopefully assembled a scintillator plane, now we can to 
  //add it to the world
  //First up is the top side
  for(G4int planeNum=0;planeNum<fNumScintPlanes;planeNum++) {
     G4ThreeVector Tm(0,0,fScintPlaneLength/2. + planeNum*fScintPlaneGap);
     G4RotationMatrix Rm; //Will do this in a second
     if(planeNum%2==1) Rm.rotateZ(90*deg);
     assemblyDetector->MakeImprint(lvWorld,Tm,&Rm);
  }
  //Then we'll do the bottom side
  for(G4int planeNum=0;planeNum<fNumScintPlanes;planeNum++) {
     G4ThreeVector Tm(0,0,-fScintPlaneLength/2. - planeNum*fScintPlaneGap);
     G4RotationMatrix Rm; //Will do this in a second
     if(planeNum%2==1) Rm.rotateZ(90*deg);
     assemblyDetector->MakeImprint(lvWorld,Tm,&Rm);
  }
  

  G4VSolid *sSphereNails = new G4Sphere ("sphereNails", //name
					 0,             // inner radius
					 0.2*m,         // outer radius
					 0,             // start phi
					 360*deg,       // end phi
					 0,             // start theta
					 180*deg);      // end theta
  G4LogicalVolume *lvSphereNails = new G4LogicalVolume(sSphereNails,steelNails, "lvSphereNails");
  G4VPhysicalVolume *pvSphereNails = new G4PVPlacement (0,G4ThreeVector (0,-0.2*m,0), "pvSphereNails",lvSphereNails,pvWorld, false,0);
  
 
      //  }


  //------------------------------------------------------------------
  //  Sensitive Detector
  //  ------------------------------------------------------------------

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4String scintSDName = "/mydet/scint";
  ScintillatorSD  *scintSD = new ScintillatorSD(scintSDName,this);
  SDman->AddNewDetector(scintSD);
  lvScintStrip->SetSensitiveDetector(scintSD);
    

  Analysis::getInstance()->setTotNumScintStrips(fTotNumScintStrips);
  Analysis::getInstance()->setNumScintPlanes(fNumScintPlanes);

  return pvWorld;
}

