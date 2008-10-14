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

#include "G4Event.hh"
#include "G4SingleParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "RunManager.hh"
#include "DataInput.hh"
#include "globals.hh"
#include <stdlib.h>
#include "DetectorDefs.hh"


CosmicRayFluxParticleSource::CosmicRayFluxParticleSource()
  :G4SingleParticleSource()
{
  
  G4SPSPosDistribution *fPosGenerator = this->GetPosDist();
  fPosGenerator->SetPosDisType("Plane");
  fPosGenerator->SetPosDisShape("Square");
  fPosGenerator->SetCentreCoords(G4ThreeVector(0,0,(SIDELENGTH*m + (PLANES_PER_SIDE*GAP_BETWEEN_PLANES_CM*cm))));
  fPosGenerator->SetHalfX((SIDELENGTH*m));
  fPosGenerator->SetHalfY((SIDELENGTH*m));

  G4SPSAngDistribution *fAngGenerator = this->GetAngDist();
  fAngGenerator->SetAngDistType("cos");

  G4SPSEneDistribution *fEneGenerator = this->GetEneDist();
  fEneGenerator->SetEnergyDisType("Pow");
  fEneGenerator->SetEmin(1e2); //100 MeV
  fEneGenerator->SetEmax(1e6); // 1000 GeV
  fEneGenerator->SetAlpha(-2.7);

  //  this->SetVerbosity(2);
  
}

CosmicRayFluxParticleSource::~CosmicRayFluxParticleSource()
{
}



