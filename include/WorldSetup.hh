//
// WorldSetup.hh
//
//  RJN -- April 2009
//------------------
#ifndef WORLDSETUP_HH
#define WORLDSETUP_HH

#include "TROOT.h"          // Top level (or root) structure for all classes
#include "TObject.h"

class WorldSetup : public TObject
{
  
 public:
  // a constructor and a destructor
  WorldSetup();
  virtual ~WorldSetup();

   Int_t minervaStrips; ///< Rectangular or toblerone strips   
  Double_t muonGenerationArea; ///< The area (in m^2) over which the muons were generated
   Double_t worldSize; ///< Size of world in m
   Double_t scintLength; ///< Length of square scintillator planes in m
   Int_t planesPerSide; ///< Number of scintillator planes per side
   Int_t stripsPerPlane; ///< Number of strips per plane
   Double_t planeWidth; ///< Plane width in m
   Double_t gapBetweenPlanes; ///< Gap between planes in m
   Double_t verticalSeparation; ///< Vertical Separation of Z-planes
   Double_t scintTriBase; ///< Base of toblerone triangle
   Double_t scintTriHeight; ///<Height of toblerone triangle
   Double_t scintTriLengthX; ///< The length (y) of the X triangles
   Double_t scintTriLengthY; ///< The length (x) of the Y triangles
   Int_t numScintTriX; ///< The number of X scintillator triangles
   Int_t numScintTriY; ///< The number of Y scintillator triangles
   

  Int_t background; ///< 0 means target present
  Double_t sphereRadius; ///< Radius of sphere in m
  Double_t sphereDensity; ///< Density in kg/m3
  Double_t sphereOriginX;
  Double_t sphereOriginY;
  Double_t sphereOriginZ;
  
  Int_t realOrFakeContainer; ///< GDML model, or 5mm box
  Int_t waterTankFlag;
  Int_t steelBoxFlag;
  Double_t waterBoxHalfSide;
  Double_t waterBoxSteelThickness;
  Double_t steelBoxX;
  Double_t steelBoxY;
  Double_t steelBoxZ;
  Double_t steelBoxHalfSide;
  Double_t steelThickness;
  


 private:
  ClassDef(WorldSetup ,2) // WorldSetup
    
};

#endif 

