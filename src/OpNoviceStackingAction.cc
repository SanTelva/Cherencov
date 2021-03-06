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
/// \file OpNovice/src/OpNoviceStackingAction.cc
/// \brief Implementation of the OpNoviceStackingAction class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "OpNoviceStackingAction.hh"

#include "G4VProcess.hh"
#include "Randomize.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

extern G4double edepSi1, edepSi2, edepSi3, edepSiC, genEkin;
extern FILE *fp2, *fp3;

G4int nRun = 0;
//extern G4double xs, ys, zs;

OpNoviceStackingAction::OpNoviceStackingAction()
  : G4UserStackingAction(),
    fScintillationCounter(0), fCerenkovCounter(0), fExtruderPhotons(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceStackingAction::~OpNoviceStackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
OpNoviceStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
        fScintillationCounter++;
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov")
        fCerenkovCounter++;
      if(aTrack->GetPosition()[2] == 40.0)
        fExtruderPhotons++;
    }
  }
  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceStackingAction::NewStage()
{
  G4cout << "Number of Cerenkov photons produced in this event : "
         << fCerenkovCounter << G4endl;
  G4cout << "Total energy deposit by this event: "
	 << (edepSi1+edepSi2+edepSi3+edepSiC)/MeV << G4endl;
   G4cout << "Generated energy of primary particle: "
	 << genEkin << G4endl;
  fprintf(fp3, "%3d\t%4.3e\t%4.3e\t%4.3e\t%4.3e\t%4.3e\t%4.3e\t%3d\n", nRun, genEkin, 
  edepSi1/MeV, edepSi2/MeV, edepSiC/MeV, edepSi3/MeV,
  (edepSi1+edepSi2+edepSi3+edepSiC)/MeV, fCerenkovCounter);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceStackingAction::PrepareNewEvent()
{
  fprintf(fp2, "\n");
  fScintillationCounter = 0;
  fCerenkovCounter = 0;
  fExtruderPhotons = 0;
  edepSi1 = 0;
  edepSi2 = 0;
  edepSi3 = 0;
  edepSiC = 0;
  nRun++;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
