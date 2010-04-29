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
//

#ifndef CosmicRayFluxParticleSource_h
#define CosmicRayFluxParticleSource_h 1


#include "G4SingleParticleSource.hh"

#include "G4VPrimaryGenerator.hh"
#include "G4ParticleMomentum.hh"
#include "G4ParticleDefinition.hh"
 //
#include "G4SPSPosDistribution.hh"
#include "G4SPSAngDistribution.hh"
#include "G4SPSEneDistribution.hh"
#include "G4SPSRandomGenerator.hh"
class DetectorConstruction;
class G4Event;

class CosmicRayFluxParticleSource : public G4SingleParticleSource
{
  public:
   CosmicRayFluxParticleSource(DetectorConstruction *detConPtr);
   ~CosmicRayFluxParticleSource(); 
  void GeneratePrimaryVertex(G4Event *evt);

  G4SPSPosDistribution* GetPosDist() {return posGenerator;};
  G4SPSAngDistribution* GetAngDist() {return angGenerator;};
  G4SPSEneDistribution* GetEneDist() {return eneGenerator;};
  G4SPSRandomGenerator* GetBiasRndm() {return biasRndm;};


  // Set the verbosity level.
  void SetVerbosity(G4int);

  // Set the particle species
  void SetParticleDefinition (G4ParticleDefinition * aParticleDefinition);
  inline G4ParticleDefinition * GetParticleDefinition () { return particle_definition;} ;

  inline void SetParticleCharge(G4double aCharge) { particle_charge = aCharge; } ;

  // Set polarization
  inline void SetParticlePolarization (G4ThreeVector aVal) {particle_polarization = aVal;};
  inline G4ThreeVector GetParticlePolarization ()  {return particle_polarization;};

  // Set Time.
  inline void SetParticleTime(G4double aTime)  { particle_time = aTime; };
  inline G4double GetParticleTime()  { return particle_time; };

  inline void SetNumberOfParticles(G4int i)  { NumberOfParticlesToBeGenerated = i; };
  //
  inline G4int GetNumberOfParticles() { return NumberOfParticlesToBeGenerated; };
  inline G4ThreeVector GetParticlePosition()  { return particle_position;};
  inline G4ThreeVector GetParticleMomentumDirection()  { return particle_momentum_direction;};
  inline G4double GetParticleEnergy()  {return particle_energy;};

private:
  //  G4SPSEneDistribution* eneGenerator;
  double simpleMuonFlux(double energy);
  double weirdCosThetaFlux(double theta);
  double moreComplicatedMuonFlux(double momentum);
  DetectorConstruction *fMyDetCon;

  G4SPSPosDistribution* posGenerator;
  G4SPSAngDistribution* angGenerator;
  G4SPSEneDistribution* eneGenerator;
  G4SPSRandomGenerator* biasRndm;
  //
  // Other particle properties
  G4int                  NumberOfParticlesToBeGenerated;
  G4ParticleDefinition * particle_definition;
  G4ParticleMomentum     particle_momentum_direction;
  G4double               particle_energy;
  G4double               particle_charge;
  G4ThreeVector          particle_position;
  G4double               particle_time;
  G4ThreeVector          particle_polarization;
  G4double               particle_weight;

  // Verbosity
  G4int verbosityLevel;

};

#endif


