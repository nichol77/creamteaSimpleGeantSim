//
// ScintHitInfo.hh
//
//  RJN September 2008
//------------------
#ifndef SCINTHITINFO_HH
#define SCINTHITINFO_HH

#include "TROOT.h"          // Top level (or root) structure for all classes
#include "TObject.h"

class ScintHitInfo : public TObject
{
  
 public:
  // a constructor and a destructor
  ScintHitInfo();
  ScintHitInfo(Int_t tSide, Int_t tPlane, Int_t tStrip, Double_t tPos[3], Double_t tEnergyDep);
  virtual ~ScintHitInfo();

  Int_t side; // 0 is top, 1 is bottom
  Int_t plane; //Which scintillator plane in stack
  Int_t strip; //Which strip in scintillator plane
  Double_t truePos[3]; //The first position of the largest hit in the strip
  Double_t energyDep; //The total energy deposited

 private:
  ClassDef(ScintHitInfo ,1) // ScintHitInfo
    
};

#endif 

