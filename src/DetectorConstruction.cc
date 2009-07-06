//
//----------------------------------------------------------------------
// Author: rjn@hep.ucl.ac.uk -- based on work by D. Jason Koskinen
// Date: 10/09/08 
//
// 
//----------------------------------------------------------------------
//----------------------------------------------------------------------
#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "ScintillatorSD.hh"
#include "DetectorDefs.hh"
#include "Analysis.hh"
#include "globals.hh"
#include "TargetVolume.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4Trap.hh"
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


DetectorConstruction::DetectorConstruction(){
  Data = DataInput::GetDataInput();
  DefineMaterials();

  fReadFile ="GDML_containerFullRots/containerFullRots.gdml";
  fWorldSize=WORLD_SIZE*m;
  fNumScintPlanes=PLANES_PER_SIDE;
  fScintPlaneGap=GAP_BETWEEN_PLANES_CM*cm;
  fScintPlaneLength=SIDELENGTH*m;
  fScintPlaneWidth=PLANE_WIDTH_CM*cm;
  fVerticalHeight=VERTICAL_SEPARATION*m;
  fNumScintStrips=STRIPS_PER_PLANE;
  fRotate90=ROTATE_EVERY_PLANE;
  fTotNumScintStrips=2*fNumScintPlanes*fNumScintStrips;	
  fTarget=0;
  fScintTriHeight=SCINT_TRIANGLE_HEIGHT_CM*cm;
  fScintTriBase=SCINT_TRIANGLE_BASE_CM*cm;
  fNumScintTriangles=fScintPlaneLength/fScintTriBase;
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
  G4Material* steelNails = new G4Material ("steelNails", SPHERE_DENSITY_KG_M3*kg/m3, 2);
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
  if(CONTAINER) {
    //These are the the lines needed to include the container
    //gpt read in world and target information for gdml file.
    parser.SetOverlapCheck(true);
    parser.Read(fReadFile);
    pvWorld = parser.GetWorldVolume();
    lvWorld = pvWorld->GetLogicalVolume();
  }
  else  { 
    //Only include these lines if we are doing a no-container test
    sWorld = new G4Box("sWorld", Data->WorldX/2, Data->WorldY/2, Data->WorldZ/2);
  
    lvWorld = new G4LogicalVolume(sWorld,	 Air, "lvWorld");
    
    pvWorld = new G4PVPlacement(0, G4ThreeVector(0.0,0.0,0.0), lvWorld, "pvWorld", 0, false, 0);
  }

  G4cout << lvWorld->GetName() << "\n";

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
     G4ThreeVector Tm(0,0,fVerticalHeight/2. + planeNum*fScintPlaneGap);
     G4RotationMatrix Rm; //Will do this in a second
     if(planeNum%2==1) Rm.rotateZ(90*deg);
     assemblyDetector->MakeImprint(lvWorld,Tm,&Rm);
  }
  //Then we'll do the bottom side
  for(G4int planeNum=0;planeNum<fNumScintPlanes;planeNum++) {
     G4ThreeVector Tm(0,0,-fVerticalHeight/2. - planeNum*fScintPlaneGap);
     G4RotationMatrix Rm; //Will do this in a second
     if(planeNum%2==1) Rm.rotateZ(90*deg);
     assemblyDetector->MakeImprint(lvWorld,Tm,&Rm);
  }
  

  //Now lets try and make a scintillator plane stack
  //Define a scintillator strip x is the width, y is the length, z is the thickness

  //This is a toblerone shape with triangle height fScintTriHeight (in Z), triangle base fScintTriBase (in x) and strip length fScintPlaneLength (in y).
//   G4Trap *scintToblerone = new G4Trap("scintToblerone",
// 				      fScintTriBase,0,
// 				      fScintPlaneLength,fScintPlaneLength,
// 				      fScintTriHeight
//   G4LogicalVolume *lvScintTriangle 
//      = new G4LogicalVolume(scintStripBox,Scintillator,"lvScintTriangle",0,0,0);

//   //First we'll assemble all the strips in one plane then, we'll try and stack the planes
//   G4AssemblyVolume *assemblyDetector = new G4AssemblyVolume();
  
//   //These are the roatation and translation of the strip in the plane
//   G4RotationMatrix Ra;
//   G4ThreeVector Ta;

//   Ta.setY(0);
//   Ta.setZ(0);
//   for(G4int stripNum=0;stripNum<fNumScintStrips;stripNum++) {
//      Ta.setX(-fScintPlaneLength/2. + (stripNum+0.5)*scintStripWidth);
//      //     G4cout << Ta.getX() << "\n";
//      assemblyDetector->AddPlacedVolume(lvScintTriangle,Ta,&Ra);
//   }
  
//   //So now we have hopefully assembled a scintillator plane, now we can to 
//   //add it to the world
//   //First up is the top side
//   for(G4int planeNum=0;planeNum<fNumScintPlanes;planeNum++) {
//      G4ThreeVector Tm(0,0,fVerticalHeight/2. + planeNum*fScintPlaneGap);
//      G4RotationMatrix Rm; //Will do this in a second
//      if(planeNum%2==1) Rm.rotateZ(90*deg);
//      assemblyDetector->MakeImprint(lvWorld,Tm,&Rm);
//   }
//   //Then we'll do the bottom side
//   for(G4int planeNum=0;planeNum<fNumScintPlanes;planeNum++) {
//      G4ThreeVector Tm(0,0,-fVerticalHeight/2. - planeNum*fScintPlaneGap);
//      G4RotationMatrix Rm; //Will do this in a second
//      if(planeNum%2==1) Rm.rotateZ(90*deg);
//      assemblyDetector->MakeImprint(lvWorld,Tm,&Rm);
//   }
  

  //--------------------------------------------------------------------
  // Target Addition
  //--------------------------------------------------------------------
  if(fTarget) {
     fTarget->constructTarget(pvWorld);
  }


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

