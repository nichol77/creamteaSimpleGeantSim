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

  Double_t worldSize; ///< Size of world in m
  Double_t scintLength; ///< Length of square scintillator planes in m
  Int_t planesPerSide; ///< Number of scintillator planes per side
  Int_t stripsPerPlane; ///< Number of strips per plane
  Double_t planeWidth; ///< Plane width in m
  Double_t gapBetweenPlanes; ///< Gap between planes in m
  
  Int_t background; ///< 0 means target present
  Double_t sphereRadius; ///< Radius of sphere in m
  Double_t sphereDensity; ///< Density in kg/m3
  Double_t sphereOriginX;
  Double_t sphereOriginY;
  Double_t sphereOriginZ;
  



 private:
  ClassDef(WorldSetup ,1) // WorldSetup
    
};

#endif 

