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
/// \file OpNovice/src/OpNoviceRunAction.cc
/// \brief Implementation of the OpNoviceRunAction class
//
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Make this appear first!
#include "G4Timer.hh"

#include "OpNoviceRunAction.hh"
#include "G4AccumulableManager.hh"
#include "G4Run.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

extern FILE *fp2;
extern G4double edepSi1, edepSi2, edepSi3, edepSiC;
OpNoviceRunAction::OpNoviceRunAction()
 : G4UserRunAction(),
   fTimer(0)
{
  fTimer = new G4Timer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceRunAction::~OpNoviceRunAction()
{
  delete fTimer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceRunAction::BeginOfRunAction(const G4Run* aRun)
{
  edepSi1 = 0;
  edepSi2 = 0;
  edepSi3 = 0;
  edepSiC = 0;
  G4AccumulableManager* accManager = G4AccumulableManager::Instance();
  accManager -> Reset();
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  fTimer->Start();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceRunAction::EndOfRunAction(const G4Run* aRun)
{
    G4AccumulableManager* accManager = G4AccumulableManager::Instance();
    accManager -> Merge();
    if (IsMaster())
  {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------"
     << G4endl;
  }
    fTimer->Stop();
//fprintf(fp2, "Total energy deposit from this run is %7.6e", edepSi/MeV);
//  G4cout << "number of event = " << aRun->GetNumberOfEvent()
//         << " " << *fTimer << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
