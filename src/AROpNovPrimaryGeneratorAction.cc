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
/// \file OpNovice/src/OpNovicePrimaryGeneratorAction.cc
/// \brief Implementation of the OpNovicePrimaryGeneratorAction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "AROpNovPrimaryGeneratorAction.hh"
#include "OpNovicePrimaryGeneratorMessenger.hh"

#include "Randomize.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#define  _USE_MATH_DEFINES
#include <math.h>

extern FILE *fp2, *fp3;
extern G4double genEkin;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AROpNovPrimaryGeneratorAction::AROpNovPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(), 
   fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  //create a messenger for this class
  fGunMessenger = new OpNovicePrimaryGeneratorMessenger(this);

  //default kinematic
  //
//  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
   particleTable = G4ParticleTable::GetParticleTable();  
//  G4ParticleDefinition* particle = particleTable->FindParticle("e-");
//  G4ParticleDefinition* particle = particleTable->FindParticle("proton");  

//  fParticleGun->SetParticleDefinition(particle);
//  fParticleGun->SetParticleTime(0.0*ns);
//  fParticleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,-5*cm));
//  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
//    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  
//  fParticleGun->SetParticleEnergy(1.0*MeV);
//  fParticleGun->SetParticleEnergy(2.5*MeV);
//  fParticleGun->SetParticleEnergy(6.0*MeV);  
//  fParticleGun->SetParticleEnergy(8.0*MeV);    
//  fParticleGun->SetParticleEnergy(10.0*MeV);      

//  fParticleGun->SetParticleEnergy(15.0*MeV);  
//  fParticleGun->SetParticleEnergy(400.0*MeV);    
//  fParticleGun->SetParticleEnergy(100.0*MeV);      
//  fParticleGun->SetParticleEnergy(200.0*MeV);        
//  fParticleGun->SetParticleEnergy(275.0*MeV);        
// fParticleGun->SetParticleEnergy(300.0*MeV);               
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AROpNovPrimaryGeneratorAction::~AROpNovPrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fGunMessenger;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AROpNovPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4double u1 = G4UniformRand();
  G4double u2 = G4UniformRand();
  G4double u3 = G4UniformRand();

  G4double ptheta = 17.5*M_PI/180*17.5*M_PI/180*u1;
  G4double pphi = 2.0*M_PI*u2;
  G4double Eprim = 1 + 10 * u3;
  genEkin = Eprim;
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("e-");
//  G4ParticleDefinition* particle = particleTable->FindParticle("proton");  

  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleTime(0.0*ns);

  //G4int n_particle = 1;
  // fParticleGun = new G4ParticleGun(n_particle);
  //create a messenger for this class
  fGunMessenger = new OpNovicePrimaryGeneratorMessenger(this);

  G4double px, py, pz;
  
  px = cos(pphi)*sin(ptheta);
  py = sin(pphi)*sin(ptheta);
  pz = cos(ptheta);
  fprintf(fp2, "\n  Eprim= %7.6e ptheta=%7.6e  pphi=%7.6e ", Eprim, ptheta, pphi ); 
  //fprintf(fp2, "  %7.6e  %7.6e  %7.6e ", px, py, pz);  
  //default kinematic
  //

  
  fParticleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,-5*cm));
//  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
//    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px, py, pz));
  
  fParticleGun->SetParticleEnergy(Eprim);
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AROpNovPrimaryGeneratorAction::SetOptPhotonPolar()
{
 G4double angle = G4UniformRand() * 360.0*deg;
 SetOptPhotonPolar(angle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AROpNovPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
 if (fParticleGun->GetParticleDefinition()->GetParticleName()!="opticalphoton")
   {
     G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
               "the particleGun is not an opticalphoton" << G4endl;
     return;
   }

 G4ThreeVector normal (1., 0., 0.);
 G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection();
 G4ThreeVector product = normal.cross(kphoton);
 G4double modul2       = product*product;
 
 G4ThreeVector e_perpend (0., 0., 1.);
 if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product;
 G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
 
 G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
 fParticleGun->SetParticlePolarization(polar);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
