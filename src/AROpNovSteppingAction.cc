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
/// \file OpNoviceSteppingAction.cc
/// \brief Implementation of the OpNoviceSteppingAction class

#include "AROpNovSteppingAction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

extern G4int fExtruderPhotons;
extern G4double edepSi1, edepSi2, edepSi3, edepSiC;
extern FILE *fp2, *fp3;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AROpNovSteppingAction::AROpNovSteppingAction()
: G4UserSteppingAction()
{ 
  fScintillationCounter = 0;
  fCerenkovCounter      = 0;
  fEventNumber = -1;
  //fprintf(fp2, "who ","x","y","z","MyKinEnPre/MeV","xx","yy","zz","MyKinEnPost/MeV","MyTrackID");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AROpNovSteppingAction::~AROpNovSteppingAction()
{ ; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AROpNovSteppingAction::UserSteppingAction(const G4Step* step)
{
  G4int eventNumber = G4RunManager::GetRunManager()->
                                              GetCurrentEvent()->GetEventID();

  if (eventNumber != fEventNumber) {
     fEventNumber = eventNumber;
     fScintillationCounter = 0;
     fCerenkovCounter = 0;
  }

    G4double x,y, z;
    G4double xx, yy, zz;
// fprintf(fp2," SteppingAction 1 \n");
 
  G4Track* track = step->GetTrack();
  G4int MyTrackID= track->GetTrackID();


  G4String ParticleName = track->GetDynamicParticle()->
                                 GetParticleDefinition()->GetParticleName();

//   if (ParticleName == "opticalphoton") return;
  
  
//   fprintf(fp2," SteppingAction 2 \n");
  
    G4StepPoint* MyPreStepPoint=step->GetPreStepPoint();
    G4StepPoint* MyPostStepPoint=step->GetPostStepPoint();

    G4double MyKinEnPre = MyPreStepPoint->GetKineticEnergy();
    G4double MyKinEnPost = MyPostStepPoint->GetKineticEnergy();    

    G4double MyEnPre = MyPreStepPoint->GetTotalEnergy();
    G4double MyEnPost = MyPostStepPoint->GetTotalEnergy();    

  
	    x= MyPreStepPoint->GetPosition()[0];
	    y= MyPreStepPoint->GetPosition()[1];
	    z= MyPreStepPoint->GetPosition()[2];
	    xx= MyPostStepPoint->GetPosition()[0];
	    yy= MyPostStepPoint->GetPosition()[1];
	    zz= MyPostStepPoint->GetPosition()[2];

 
  G4double edepStep = step -> GetTotalEnergyDeposit();
/*  if (zz >= -20.0 && zz <= 40.0 && (xx*xx + yy*yy <= 4.0)) {
     edepSiC += edepStep;
//    fprintf(fp3, "  %d  %7.6e  %7.6e\n",eventNumber, edepStep, edepSi);
    }*/
if ((MyPreStepPoint->GetStepStatus() == fGeomBoundary || z>=-45.02)
                                && zz > -45.02 && zz <= -44.98){
               edepSi1+=edepStep;
//    fprintf(fp2," ST_AC Si1: ##### nev=  %d edepStep=%7.6e summa: endepSi1=%7.6e \n", nev, edepStep, endepSi1 );
//        fprintf(fp2,"Si1: ###*** nev=  %d EnDepSi1[nev]=%7.6e endepSi1=%7.6e\n", nev, EnDepSi1[nev], endepSi1);
}
if ((MyPreStepPoint->GetStepStatus() == fGeomBoundary || z>=-21.25)
                                && zz > -21.25 && zz <= -20.75){
               edepSi2+=edepStep;
//    fprintf(fp2," ST_AC Si1: ##### nev=  %d edepStep=%7.6e summa: endepSi1=%7.6e \n", nev, edepStep, endepSi1 );
//        fprintf(fp2,"Si1: ###*** nev=  %d EnDepSi1[nev]=%7.6e endepSi1=%7.6e\n", nev, EnDepSi1[nev], endepSi1);
}
if ((MyPreStepPoint->GetStepStatus() == fGeomBoundary || z>=-20.0)
                                && zz > -20.0 && zz <= 40.0){
               edepSiC+=edepStep;
//    fprintf(fp2," ST_AC Si1: ##### nev=  %d edepStep=%7.6e summa: endepSi1=%7.6e \n", nev, edepStep, endepSi1 );
//        fprintf(fp2,"Si1: ###*** nev=  %d EnDepSi1[nev]=%7.6e endepSi1=%7.6e\n", nev, EnDepSi1[nev], endepSi1);
}
if ((MyPreStepPoint->GetStepStatus() == fGeomBoundary || z>=40.75)
                                && zz > 40.75 && zz <= 41.25){
               edepSi3+=edepStep;
//    fprintf(fp2," ST_AC Si1: ##### nev=  %d edepStep=%7.6e summa: endepSi1=%7.6e \n", nev, edepStep, endepSi1 );
//        fprintf(fp2,"Si1: ###*** nev=  %d EnDepSi1[nev]=%7.6e endepSi1=%7.6e\n", nev, EnDepSi1[nev], endepSi1);
}
 if (ParticleName != "opticalphoton" && zz >= -20.0){
    fprintf(fp2,"particle\t%7.6e\t%7.6e\t%7.6e\t%7.6e\t%7.6e\t%7.6e\t%7.6e\t%7.6e\t%d\n",x,y,z,MyKinEnPre/MeV,xx,yy,zz,MyKinEnPost/MeV,MyTrackID);
    //if (MyKinEnPre == 0.0 && MyKinEnPost == 0.0) {
//	fprintf(fp2, "\nSTOP");
	//fprintf(fp3, "(%4.3e %4.3e %4.3e)\t", xx, yy, zz);
	//}
    //fprintf(fp2, "\n");
 }

  if (ParticleName == "opticalphoton" && zz == 40.0) {  
  fprintf(fp2,"opticalphoton\t%7.6e\t%7.6e\t%7.6e\t%7.6e\t%7.6e\t%7.6e\t%7.6e\t%7.6e\t%d\n",x,y,z,MyEnPre/eV,xx,yy,zz,MyEnPost/eV,MyTrackID);
  //if (zz == 40.0){fprintf(fp2, "photon%7.6dabandoned detector\n", MyTrackID); fExtruderPhotons++;}  
  return;
                                       }


  const std::vector<const G4Track*>* secondaries =
                                            step->GetSecondaryInCurrentStep();

  if (secondaries->size()>0) {
     for(unsigned int i=0; i<secondaries->size(); ++i) {
        if (secondaries->at(i)->GetParentID()>0) {
           if(secondaries->at(i)->GetDynamicParticle()->GetParticleDefinition()
               == G4OpticalPhoton::OpticalPhotonDefinition()){
              if (secondaries->at(i)->GetCreatorProcess()->GetProcessName()
               == "Scintillation")fScintillationCounter++;
              if (secondaries->at(i)->GetCreatorProcess()->GetProcessName()
               == "Cerenkov")fCerenkovCounter++;
           }
        }
     }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
