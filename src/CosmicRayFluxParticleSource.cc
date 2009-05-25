//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: CosmicRayFluxParticleSource.cc,v 1.6 2006/06/29 17:47:23 gunter Exp $
// GEANT4 tag $Name: geant4-08-01 $
//

#include "CosmicRayFluxParticleSource.hh"
#include "DetectorConstruction.hh"
#include "G4Event.hh"
#include "G4SingleParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "RunManager.hh"
#include "globals.hh"
#include <stdlib.h>


#ifndef PI
#define PI  3.14159265358979312
#endif

CosmicRayFluxParticleSource::CosmicRayFluxParticleSource(DetectorConstruction *detConPtr)
  :G4SingleParticleSource(),fMyDetCon(detConPtr)
{
  G4double sideLength=fMyDetCon->getScintPlaneLength();
  G4double planeWidth=fMyDetCon->getScintPlaneWidth();
  G4double planeGap=fMyDetCon->getScintPlaneGap();
  G4int numPlanes=fMyDetCon->getNumScintPlanes();
  
  G4SPSPosDistribution *fPosGenerator = this->GetPosDist();
  fPosGenerator->SetPosDisType("Plane");
  fPosGenerator->SetPosDisShape("Square");
  G4double zHeight=(sideLength/2 + (numPlanes-1)*planeGap + numPlanes*planeWidth);
  fPosGenerator->SetCentreCoords(G4ThreeVector(0,0,zHeight));
  fPosGenerator->SetHalfX(sideLength/2);
  fPosGenerator->SetHalfY(sideLength/2);
  
  G4cout << "Generate at z: " << zHeight << "\twhalfwidth" << sideLength/2 << "\n";

  G4SPSAngDistribution *fAngGenerator = this->GetAngDist();
  fAngGenerator->SetAngDistType("user");
  //  for(double theta=0;theta<PI/2;theta+=PI/360) {
  for(double costheta=0;costheta<=1;costheta+=0.001) {
    double theta=acos(sqrt(costheta));
    fAngGenerator->UserDefAngTheta(G4ThreeVector(theta,weirdCosThetaFlux(theta),0));
  }
//   delete eneGenerator;
//   eneGenerator = new CosmicRayEneDistribution();
//   eneGenerator->SetEmin(1e2); //100 MeV
//   eneGenerator->SetEmax(1e6); // 1000 GeV


  G4SPSEneDistribution *fEneGenerator = this->GetEneDist();
//   //  fEneGenerator->SetEnergyDisType("Pow");
//   //  fEneGenerator->SetEmin(1e2); //100 MeV
//   //  fEneGenerator->SetEmax(1e6); // 1000 GeV
//   //  fEneGenerator->SetAlpha(-2.7);
  fEneGenerator->SetEnergyDisType("Arb");
  //  int counter=0;
  for(double energy=0;energy<1e6;energy+=1000) {
    //    double value=10000*simpleMuonFlux(energy/1000); //Just an arbitrary scaling
    double value=10000*moreComplicatedMuonFlux(energy/1000); //Just an arbitrary scaling
      fEneGenerator->ArbEnergyHisto(G4ThreeVector(energy*MeV, value , 0.));
      //      std::cout << (++counter) << "\t" << energy << "\t" << value << "\n";
    }
   fEneGenerator->SetEmin(1e2); //100 MeV
   fEneGenerator->SetEmax(1e6); // 1000 GeV
   fEneGenerator->ArbInterpolate("Lin");
  //  this->SetVerbosity(2);

  
}

CosmicRayFluxParticleSource::~CosmicRayFluxParticleSource()
{
}

double CosmicRayFluxParticleSource::simpleMuonFlux(double energy)
{
  double turningPoint=3; //GeV
  if(energy<turningPoint) {
    return pow(turningPoint,-2.7);
  }
  else {
    return pow(energy,-2.7) ;
  }
}


double CosmicRayFluxParticleSource::weirdCosThetaFlux(double theta)
{
  return pow(cos(theta),2.15);
}

double CosmicRayFluxParticleSource::moreComplicatedMuonFlux(double momentum)
{
  //Momentum in GeV
  if(momentum<1) momentum=1;
  double momThresh[4]={1,9.2765e2,1.5878e3,4.1625e5};
  double C[4]={2.95e-3,1.78e-2,1.435e1,1e3};
  double g0[4]={0.3061,1.791,3.672,4};
  double g1[4]={1.2743,0.3040,0,0};
  double g2[4]={-0.2630,0,0,0};
  double g3[4]={0.0252,0,0,0};
 
  int ind=0;
  for(int i=1;i<4;i++) {
    if(momentum>momThresh[i]) 
      ind=i;
  }
  double logP=log(momentum);

  double val=-1*(g0[ind] +g1[ind]*logP + g2[ind]*logP*logP + g3[ind]*logP*logP*logP);
  double final = C[ind]*pow(momentum,val);
  return final;

}
