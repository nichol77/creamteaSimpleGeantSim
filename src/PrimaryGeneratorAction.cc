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
// $Id: PrimaryGeneratorAction.cc,v 1.6 2006/06/29 17:47:23 gunter Exp $
// GEANT4 tag $Name: geant4-08-01 $
//

#include <stdlib.h>

#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "RunManager.hh"
#include "globals.hh"


#include "CosmicRayFluxParticleSource.hh"
#include "DataInput.hh"
#include "DetectorDefs.hh"


#define PI 3.14159265358979312
double cosThetaWeird(double theta);
double getTheta();
double getPhi();
double getMomentum(double pMin, double pMax);
void getPxPyPz(double pVec[3], double pMin=0.1, double pMax=1000);

//#include "cosmicflux.dat"

G4int n_particle;
PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  //the constructor which initialises some variables.
  n_particle = 1;
  fParticleSource = new CosmicRayFluxParticleSource();
  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  fParticleSource->SetParticleDefinition(particleTable->FindParticle(particleName="mu-"));

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleSource;
}



void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
   static G4int n_particle=0;
   G4int i = anEvent->GetEventID() % 3;
   if(n_particle%100==0) G4cout<<" particle number "<<n_particle<<" i "<<i<<G4endl;
   fParticleSource->GeneratePrimaryVertex(anEvent);
   n_particle++;
}

// void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
// {

//   void getPxPyPz(double pVec[3], double pMin=0.1, double pMax=1000);

//   double pflux[3] = {0,0,0};
//   double xmax = (SIDELENGTH*1000) /2;
//   double ymax = (SIDELENGTH*1000) +100;
//   double zmax = (SIDELENGTH*1000) /2;

//   G4int i = anEvent->GetEventID() % 3;
//   if(n_particle%100==0) G4cout<<" particle number "<<n_particle<<" i "<<i<<G4endl;
  
//   getPxPyPz(pflux,1e3,1e6); //These numbers are in MeV

//   //  double pmod=sqrt(pflux[0]*pflux[0]+pflux[1]*pflux[1]+pflux[2]*pflux[2]);

//   G4ThreeVector p(pflux[0],pflux[2],pflux[1]);
//   //  G4ThreeVector p(0.0,-pmod,0.0);

  
//   double xflux = -xmax + drand48()*2.0*xmax;
//   double zflux = -zmax + drand48()*2.0*zmax;
//   G4ThreeVector v(xflux,ymax,zflux);
  
//   //G4ThreeVector v(0.0,3015.0,0.0);

//   //  particleGun->SetParticleEnergy(0);
//   particleGun->SetParticleMomentum(p);
//   particleGun->SetParticlePosition(v);
  
//   particleGun->GeneratePrimaryVertex(anEvent);
//   n_particle++;
// }

// void getPxPyPz(double pVec[3], double pMin, double pMax)
// {
//    //Momentum are in GeV
//   double theta=getTheta();
//   double phi=getPhi();
//   double momentum=getMomentum(pMin,pMax);
//   pVec[2]=-1*momentum*cos(theta); //pz
//   pVec[0]=momentum*cos(phi)*sin(theta);//px
//   pVec[1]=momentum*sin(phi)*sin(theta);//py
  
// }

//Double_t thetaFunc(Double_t *x, Double_t *par) {
//  return TMath::Power(TMath::Cos(x[0]),2.15);
//}


// double cosThetaWeird(double theta)
// {
//   return pow(cos(theta),2.15);
// }

// double getTheta() {
//   //    cout << drand48() << endl;
//     while(1) {
//       double angle=drand48()*PI/2;
//       double value=cosThetaWeird(angle);
//       if(value>drand48())
// 	return angle;      
//     }
// }

// double getPhi() {
//   return PI*2*drand48();
// }


// double getMomentum(double pMin, double pMax) {
//   //  double pMin=1;
//   //  double pMax=1e3;

//   double maxp1=pow(pMax,-1.7);
//   double minp1=pow(pMin,-1.7);
//   double y=drand48();
//   double momentum=pow((maxp1-minp1)*y + minp1,-1./1.7);
//   return momentum;
// }


