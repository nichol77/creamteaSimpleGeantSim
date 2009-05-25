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
// $Id: CosmicRayEneDistribution.cc,v 1.6 2006/06/29 17:47:23 gunter Exp $
// GEANT4 tag $Name: geant4-08-01 $
//

#include "CosmicRayEneDistribution.hh"

#include "G4Event.hh"
#include "G4SingleParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "RunManager.hh"
#include "globals.hh"
#include <stdlib.h>
#include "DetectorDefs.hh"

#ifndef PI
#define PI  3.14159265358979312
#endif

double getMomentum(double pMin, double pMax);

CosmicRayEneDistribution::CosmicRayEneDistribution()
  :G4SPSEneDistribution()
{
  

  
}

CosmicRayEneDistribution::~CosmicRayEneDistribution()
{
}

G4double CosmicRayEneDistribution::GenerateOne(G4ParticleDefinition *a)
{
  //  particle_definition = a;
  double emin=this->GetEmin();
  double emax=this->GetEmax();
  particle_energy = getMomentum(emin,emax);
  return particle_energy;
}


double getMomentum(double pMin, double pMax) {
  pMin/=1000;
  pMax/=1000;
  double pt = 3;
  double y = drand48();
  static double maxp1=pow(pMax,-1.7);
  static double minpt=pow(pt,-1.7);

  double a = 5;

  double threshold = 1./(1 + (a/-1.7) * (maxp1 - minpt));
  
  double momentum1 = ((y*(1+((a/-1.7)*(maxp1-minpt))))*(pt-pMin)) + pMin;
  double momentum2 = pow((((-1.7/a)*(y*(1+(a/-1.7)*(maxp1-minpt))-1)) + minpt),-
1./1.7);

  if(y<threshold) {  
    //std::cout << "Momentum1 = " << momentum1 << "\n";
    return momentum1*1000;
    } else { 
      //std::cout << "Momentum2 = " << momentum2 << "\n";
    return momentum2*1000;
    }
}
