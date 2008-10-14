//
// ScintHitInfo.cc
//
// rjn@hep.ucl.ac.uk -- September 2008
//  This is a class that defines the ScintHitInfo object that 
//  is used to store the Scintillator Hit Information in a root tree.
//------------------

#include "ScintHitInfo.hh"
ClassImp(ScintHitInfo)
  
ScintHitInfo::ScintHitInfo()
{
  //Default Constructor
}

ScintHitInfo::ScintHitInfo(Int_t tSide, Int_t tPlane, Int_t tStrip, Double_t tPos[3], Double_t tEnergyDep)
{
  side=tSide;
  plane=tPlane;
  strip=tStrip;
  truePos[0]=tPos[0];
  truePos[1]=tPos[1];
  truePos[2]=tPos[2];
  energyDep=tEnergyDep;
}


//----------------------------------------------------------------------
ScintHitInfo::~ScintHitInfo()
{
  // ScintHitInfo destructor
}

