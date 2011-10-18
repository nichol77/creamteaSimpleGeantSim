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
  fScintTriHeight=SCINT_TRIANGLE_HEIGHT_MM*mm;
  fScintTriBase=SCINT_TRIANGLE_BASE_MM*mm;
  fScintTriLengthX=SCINT_X_STRIP_LENGTH_M*m;
  fScintTriLengthY=SCINT_Y_STRIP_LENGTH_M*m;  
  fNumScintTrianglesX=SCINT_X_NUM_STRIPS;
  fNumScintTrianglesY=SCINT_Y_NUM_STRIPS;
  if(USE_MINERVA_STRIPS) {
     fScintPlaneWidth=fScintTriHeight;
     fScintPlaneLength=2*getLongestScintHalfLength();
     fTotNumScintStrips=2*fNumScintPlanes*fNumScintTrianglesX;
     if(fNumScintTrianglesY>fNumScintTrianglesX)
	fTotNumScintStrips=2*fNumScintPlanes*fNumScintTrianglesY;
  }
  Data->muonGenerationArea=(fScintPlaneLength*0.001)*(fScintPlaneLength*0.001);
  Data->scintPlaneWidth=fScintPlaneWidth;
  Data->scintSideLength=fScintPlaneLength;
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
  G4VPhysicalVolume *pvInnerMost=0;

  if(0) {
//     //These are the the lines needed to include the container
//     //gpt read in world and target information for gdml file.
//      //    parser.SetOverlapCheck(true);
//     parser.Read(fReadFile);
//     pvWorld = parser.GetWorldVolume();
//     lvWorld = pvWorld->GetLogicalVolume();
//     pvInnerMost=pvWorld;
  }
  else  { 
    //Only include these lines if we are doing a no-container test
    sWorld = new G4Box("sWorld", Data->WorldX/2, Data->WorldY/2, Data->WorldZ/2);
  
    lvWorld = new G4LogicalVolume(sWorld,	 Air, "lvWorld");
    
    pvWorld = new G4PVPlacement(0, G4ThreeVector(0.0,0.0,0.0), lvWorld, "pvWorld", 0, false, 0);
    if(FAKE_CONTAINER) {
       //Add a fake box made of steel
       G4Box *sFakeContainer_outer = new G4Box("sFakeContainer_outer", (2.44/2)*m,(12.15/2)*m,(2.59/2)*m);
       G4LogicalVolume *lvFakeContainer_outer = new G4LogicalVolume(sFakeContainer_outer, Fe, "lvFakeContainer_outer");
       G4VPhysicalVolume *pvFakeContainer_outer = new G4PVPlacement(0, G4ThreeVector(0.0,0.0,0.0), "pvFakeContainer_outer", lvFakeContainer_outer, pvWorld, false, 0);
       
       G4Box *sFakeContainer_inner = new G4Box("sFakeContainer_inner", (2.44/2)*m-5*mm,(12.15/2)*m-5*mm,(2.59/2)*m-5*mm);
       G4LogicalVolume *lvFakeContainer_inner = new G4LogicalVolume(sFakeContainer_inner, Air, "lvFakeContainer_inner");
       G4VPhysicalVolume *pvFakeContainer_inner = new G4PVPlacement(0, G4ThreeVector(0.0,0.0,0.0), "pvFakeContainer_inner", lvFakeContainer_inner, pvFakeContainer_outer, false, 0);
       pvInnerMost=pvFakeContainer_inner;
       
    }
  }

  G4cout << lvWorld->GetName() << "\n";

  //--------------------------------------------------
  // For now what we'll try and do is just make three scintillator planes at the top, 
  // and three at the bottom. 
  G4LogicalVolume *lvScintStrip=0;
  G4LogicalVolume *lvScintTriangleX=0;
  G4LogicalVolume *lvScintTriangleY=0;

  
  if(!USE_MINERVA_STRIPS) {
     //Now lets try and make a scintillator plane stack
     //Define a scintillator strip x is the width, y is the length, z is the thickness
     G4Box *scintStripBox = new G4Box("scintStripBox",scintStripWidth/2.,
				      fScintPlaneLength/2.,fScintPlaneWidth/2.);
     lvScintStrip 
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
  }
  else {     
     //     Now lets try and make a scintillator plane stack
     //  Define a scintillator strip x is the width, y is the length, z is the thickness
     
     //  This is a toblerone shape with triangle height fScintTriHeight (in Z), triangle base fScintTriBase (in x) and strip length fScintPlaneLength (in y).
  G4Trap *scintTobleroneX = new G4Trap("scintTobleroneX",
				       0.5*fScintTriBase,0.001*mm,
				       0.5*fScintTriLengthX,
				       0.5*fScintTriLengthX,
				       0.5*fScintTriHeight);
  lvScintTriangleX 
     = new G4LogicalVolume(scintTobleroneX,Scintillator,"lvScintTriangleX",0,0,0);
  
  //Now for the other orientation of strip
  G4Trap *scintTobleroneY = new G4Trap("scintTobleroneY",
				       0.5*fScintTriLengthY,
				       0.5*fScintTriLengthY,
				       0.5*fScintTriBase,
				       0.001*mm,
				       0.5*fScintTriHeight);
  lvScintTriangleY 
     = new G4LogicalVolume(scintTobleroneY,Scintillator,"lvScintTriangleY",0,0,0);
  

  //First we'll assemble all the strips in one plane then, we'll try and stack the planes
  G4AssemblyVolume *assemblyDetectorX = new G4AssemblyVolume();  
  //These are the roatation and translation of the strip in the plane
  G4ThreeVector Tax;
  Tax.setY(0);
  Tax.setZ(0);
  Double_t stripZeroX=0;  
  stripZeroX=-1*((fNumScintTrianglesX/2)*(fScintTriBase/2.));
  if(fNumScintTrianglesX%2==0) {
     stripZeroX+=fScintTriBase/4.;
  }
  for(G4int stripNum=0;stripNum<fNumScintTrianglesX;stripNum++) {
     Tax.setX(stripZeroX+(stripNum*fScintTriBase/2.));
     G4RotationMatrix Rax;
     if(stripNum%2==1) Rax.rotateY(180*deg);
     //     G4cout << Ta.getX() << "\n";
     assemblyDetectorX->AddPlacedVolume(lvScintTriangleX,Tax,&Rax);
  }


  //First we'll assemble all the strips in one plane then, we'll try and stack the planes
  G4AssemblyVolume *assemblyDetectorY = new G4AssemblyVolume();  
  //These are the roatation and translation of the strip in the plane
  G4ThreeVector Tay;
  Tay.setX(0);
  Tay.setY(0);
  Tay.setZ(0);
  Double_t stripZeroY=0;  
  stripZeroY=-1*((fNumScintTrianglesY/2)*(fScintTriBase/2.));
  if(fNumScintTrianglesY%2==0) {
     stripZeroY+=fScintTriBase/4.;
  }
  for(G4int stripNum=0;stripNum<fNumScintTrianglesY;stripNum++) {
     Tay.setY(stripZeroY+(stripNum*fScintTriBase/2.));
     G4RotationMatrix Ray;
     if(stripNum%2==1) Ray.rotateX(180*deg);
     //     G4cout << Ta.getY() << "\n";
     assemblyDetectorY->AddPlacedVolume(lvScintTriangleY,Tay,&Ray);
  }
  
  

  //So now we have hopefully assembled a scintillator plane, now we can to 
  //add it to the world
  //First up is the top side
  for(G4int planeNum=0;planeNum<fNumScintPlanes;planeNum++) {
     G4ThreeVector Tm(0,0,fVerticalHeight/2. + planeNum*fScintPlaneGap);
     G4RotationMatrix Rm; //Will do this in a second
     if(planeNum %2 == 0)
	assemblyDetectorX->MakeImprint(lvWorld,Tm,&Rm);
     if(planeNum %2 == 1)
	assemblyDetectorY->MakeImprint(lvWorld,Tm,&Rm);
  }
  //Then we'll do the bottom side
  for(G4int planeNum=0;planeNum<fNumScintPlanes;planeNum++) {
     G4ThreeVector Tm(0,0,-fVerticalHeight/2. - planeNum*fScintPlaneGap);
     G4RotationMatrix Rm; //Will do this in a second
     if(planeNum %2 == 0)
	assemblyDetectorX->MakeImprint(lvWorld,Tm,&Rm);
     if(planeNum %2 == 1)
	assemblyDetectorY->MakeImprint(lvWorld,Tm,&Rm);
  }
  }
 

  //--------------------------------------------------------------------
  // Target Addition
  //--------------------------------------------------------------------

    if(STEEL_BOX) {
       //Add a box made of steel
       
       G4Box *sSteelBox_outer = new G4Box("sSteelBox_outer", STEEL_BOX_HALF_SIDE_CM*cm,STEEL_BOX_HALF_SIDE_CM*cm,STEEL_BOX_HALF_SIDE_CM*cm);
       G4LogicalVolume *lvSteelBox_outer = new G4LogicalVolume(sSteelBox_outer, Fe, "lvSteelBox_outer");
       G4VPhysicalVolume *pvSteelBox_outer = new G4PVPlacement(0, G4ThreeVector(STEEL_BOX_X_M*m,STEEL_BOX_Y_M*m,STEEL_BOX_Z_M*m), "pvSteelBox_outer", lvSteelBox_outer, pvInnerMost, false, 0);
       
       G4Box *sSteelBox_inner = new G4Box("sSteelBox_inner", STEEL_BOX_HALF_SIDE_CM*cm-STEEL_THICKNESS_CM*cm,STEEL_BOX_HALF_SIDE_CM*cm-STEEL_THICKNESS_CM*cm,STEEL_BOX_HALF_SIDE_CM*cm-STEEL_THICKNESS_CM*cm);
       G4LogicalVolume *lvSteelBox_inner = new G4LogicalVolume(sSteelBox_inner, Air, "lvSteelBox_inner");
       //Important, the location of the inner box is relative to the centre of the outer box.
       //Little so-and-so's
       G4VPhysicalVolume *pvSteelBox_inner = new G4PVPlacement(0, G4ThreeVector(0,0,0), "pvSteelBox_inner", lvSteelBox_inner, pvSteelBox_outer, false, 0);

       
    }  



    if(WATER_TANK) {
       
       G4Box *sWaterTank_outer = new G4Box("sWaterTank_outer", WATER_BOX_HALF_SIDE_CM*cm,WATER_BOX_HALF_SIDE_CM*cm,WATER_BOX_HALF_SIDE_CM*cm);
       G4LogicalVolume *lvWaterTank_outer = new G4LogicalVolume(sWaterTank_outer, Fe, "lvWaterTank_outer");
       G4VPhysicalVolume *pvWaterTank_outer = new G4PVPlacement(0, G4ThreeVector(SPHERE_X_M*m,SPHERE_Y_M*m,SPHERE_Z_M*m), "pvWaterTank_outer", lvWaterTank_outer, pvInnerMost, false, 0);
       
       
       G4Box *sWaterTank = new G4Box("sWaterTank", WATER_BOX_HALF_SIDE_CM*cm-WATER_BOX_SIDE_THICKNESS_MM*mm,WATER_BOX_HALF_SIDE_CM*cm-WATER_BOX_SIDE_THICKNESS_MM*mm,WATER_BOX_HALF_SIDE_CM*cm-WATER_BOX_SIDE_THICKNESS_MM*mm);
       G4LogicalVolume *lvWaterTank = new G4LogicalVolume(sWaterTank, Water, "lvWaterTank");
       G4VPhysicalVolume *pvWaterTank = new G4PVPlacement(0, G4ThreeVector(0,0,0), "pvWaterTank", lvWaterTank, pvWaterTank_outer, false, 0);
       pvInnerMost=pvWaterTank;
    }
    
    if(fTarget) {
       fTarget->constructTarget(pvInnerMost);
    }


  //------------------------------------------------------------------
  //  Sensitive Detector
  //  ------------------------------------------------------------------
 
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4String scintSDName = "/mydet/scint";
  ScintillatorSD  *scintSD = new ScintillatorSD(scintSDName,this);
  SDman->AddNewDetector(scintSD);
  if(!USE_MINERVA_STRIPS) {
     lvScintStrip->SetSensitiveDetector(scintSD);
  }
  else {
     lvScintTriangleX->SetSensitiveDetector(scintSD);
     lvScintTriangleY->SetSensitiveDetector(scintSD);
  }
    


  Analysis::getInstance()->setTotNumScintStrips(fTotNumScintStrips);
  Analysis::getInstance()->setNumScintPlanes(fNumScintPlanes);

  return pvWorld;
}


G4double DetectorConstruction::getLongestScintHalfLength()
{
   if(USE_MINERVA_STRIPS) {
      Double_t fullLength=SCINT_X_STRIP_LENGTH_M*m;
      if(SCINT_Y_STRIP_LENGTH_M*m>fullLength)
	 fullLength=SCINT_Y_STRIP_LENGTH_M*m;
      Double_t otherLength=((SCINT_X_NUM_STRIPS+1)/2.)*SCINT_TRIANGLE_BASE_MM*mm;
      if(otherLength>fullLength) fullLength=otherLength;
      otherLength=((SCINT_Y_NUM_STRIPS+1)/2.)*SCINT_TRIANGLE_BASE_MM*mm;
      if(otherLength>fullLength) fullLength=otherLength;
      return (fullLength/2.);
   }

   return (this->getScintPlaneLength()/2.);

}
