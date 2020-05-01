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
/// \file OpNovice/src/OpNoviceDetectorConstruction.cc
/// \brief Implementation of the OpNoviceDetectorConstruction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//#include "OpNoviceDetectorConstruction.hh"
#include "AROpNovDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AROpNovDetectorConstruction::AROpNovDetectorConstruction()
 : G4VUserDetectorConstruction()
{
//  fExpHall_x = fExpHall_y = fExpHall_z = 25.0*cm;
    fExpHall_x = fExpHall_y = fExpHall_z = 10.0*cm;
//  fTank_x    = fTank_y    = fTank_z    =  5.0*m;
//  fBubble_x  = fBubble_y  = fBubble_z  =  0.5*m;

  fSiOrad_x = 20*mm; fSiOrad_y = 20*mm; fSiOrad_z = 30.0*mm;
}

// Define wavelength limits for materials definition
 G4double lambda_min = 200*nm ; 
 G4double lambda_max = 700*nm ; 
 G4bool checkOverlaps = true;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AROpNovDetectorConstruction::~AROpNovDetectorConstruction(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* AROpNovDetectorConstruction::Construct()
{

// ------------- Materials -------------

  G4double a, z, density;
  G4int nelements;

// Air
//
  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
  G4Element*  Si=new G4Element("Silicon", "Si", z=14.0,a=28.09*g/mole);

  G4Element*  Al=new G4Element("Aluminium", "Al", z = 13.0, a=26.981*g/mole);
  G4Material* air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  air->AddElement(N, 70.*perCent);
  air->AddElement(O, 30.*perCent);


// Quartz
//
  
  G4Material* quartz = new G4Material("Quartz", density= 2.210*g/cm3, nelements=2);
  quartz->AddElement(Si, 1);
  quartz->AddElement(O, 2);

//Silicium
 G4Material* si = new G4Material("Silicium", density = 2.33*g/cm3, nelements=1);
 si->AddElement(Si, 1);

//Aluminium
  G4Material* alum = new G4Material("Aluminium", density= 2.693*g/cm3, nelements=1);
  alum->AddElement(Al, 1);
//
  const G4int NUMENTRIES = 2;
   const G4int nEntries = 2;
  // Energy bins
  G4double X_RINDEX[NUMENTRIES] = {h_Planck*c_light/lambda_max, h_Planck*c_light/lambda_min} ; 


// ------------ Generate & Add Material Properties Table ------------
//
  G4double ephoton[NUMENTRIES] = {2.034*eV, 10.136*eV};

//  G4double photonEnergy[NUMENTRIES] =
//            { 2.034*eV, 10.136*eV};

//  const G4int nEntries = sizeof(ephoton)/sizeof(G4double);

// Alum
  G4MaterialPropertiesTable* myPT1 = new G4MaterialPropertiesTable();

// Air
  G4MaterialPropertiesTable* myPT2 = new G4MaterialPropertiesTable();

//Quartz (13/07/2019)  
   G4MaterialPropertiesTable* myPT3 = new G4MaterialPropertiesTable();

//Cone (13/07/2019)  
   G4MaterialPropertiesTable* myPT4 = new G4MaterialPropertiesTable();

  
  // Refractive index 

  const G4int N_RINDEX_QUARTZ = 2 ;
  G4double X_RINDEX_QUARTZ[N_RINDEX_QUARTZ] = {h_Planck*c_light/lambda_max, h_Planck*c_light/lambda_min} ; 
  G4double RINDEX_QUARTZ[N_RINDEX_QUARTZ] = {1.54, 1.54};
//  G4double refractiveIndex[num] = {1.35, 1.40};

  myPT3->AddProperty("RINDEX", X_RINDEX_QUARTZ, RINDEX_QUARTZ, N_RINDEX_QUARTZ);
  quartz->SetMaterialPropertiesTable(myPT3);
   
  G4double absorptionSi[NUMENTRIES]      = {2.0*m, 2.7*m};  
//  assept(sizeof(absorptionSi) == sizeof(ephoton));

  G4double absorptionAl[NUMENTRIES]      = {0.00001*m, 0.00001*m};  
//  assept(sizeof(absorptionAl) == sizeof(ephoton));
  myPT3->AddProperty("ABSLENGTH", ephoton, absorptionSi, nEntries);

//OpticalQuartzSurface

  G4double reflectivity[NUMENTRIES] = {0.999, 0.999};
  G4double specularLobe[NUMENTRIES]    = {0.3, 0.3};
  G4double specularSpike[NUMENTRIES]   = {0.2, 0.2};
  G4double backScatter[NUMENTRIES]     = {0.2, 0.2};

//  G4double absorption[num]      = {0.001, 0.001};
//  G4double absorptionSi[num]      = {0.999, 0.999};


//  myST3->AddProperty("RINDEX",                ephoton, refractiveIndex,NUMENTRIES );
  myPT3->AddProperty("SPECULARLOBECONSTANT",  ephoton, specularLobe,   NUMENTRIES );
  myPT3->AddProperty("SPECULARSPIKECONSTANT", ephoton, specularSpike,  NUMENTRIES );
  myPT3->AddProperty("BACKSCATTERCONSTANT",   ephoton, backScatter,    NUMENTRIES );
  myPT3->AddProperty("REFLECTIVITY",          ephoton, reflectivity,   NUMENTRIES );
  myPT3->AddProperty("ABSORPTION",            ephoton, absorptionSi, NUMENTRIES );    


  G4cout << "quartz G4MaterialPropertiesTable" << G4endl;
  myPT3->DumpTable();
  quartz->SetMaterialPropertiesTable(myPT3);


//---------------
// Air
//

  G4double refractiveIndex2[] = { 1.00, 1.00};

  myPT2->AddProperty("RINDEX",ephoton, refractiveIndex2, nEntries);

  G4cout << "Air G4MaterialPropertiesTable" << G4endl;
  myPT2->DumpTable();

  air->SetMaterialPropertiesTable(myPT2);


//---------------
// Alum
//

  G4cout << "Aluminium Surface G4MaterialPropertiesTable" << G4endl;
  myPT1->AddProperty("ABSORPTION",  ephoton, absorptionAl,   NUMENTRIES );
  myPT1->DumpTable();
  alum->SetMaterialPropertiesTable(myPT1);

//
// ------------- Volumes --------------

// The experimental Hall
//
G4cout << " World 1  " << G4endl;
  G4Box* expHall_box = new G4Box("World",fExpHall_x,fExpHall_y,fExpHall_z);

  G4LogicalVolume* expHall_log
    = new G4LogicalVolume(expHall_box,air,"World",0,0,0);

  G4VPhysicalVolume* expHall_phys
    = new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);
G4cout << " World 2  " << G4endl;


G4cout << " QRad 1 " << G4endl;

  
        
  // Conical section shape       
  G4double shape1_rminb =  0.*cm, shape1_rmaxb = 1.*cm;
  G4double shape1_rmina =  0.*cm, shape1_rmaxa = 2.*cm;
  G4double shape1_hz = 1*cm;
  G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
  G4ThreeVector pos1 = G4ThreeVector(0, 0, 3*shape1_hz);

  G4Cons* consSolid =    
    new G4Cons("Cons", 
    shape1_rmina, shape1_rmaxa, shape1_rminb, shape1_rmaxb, shape1_hz,
    shape1_phimin, shape1_phimax);
                      
  G4LogicalVolume* consLogical =                         
    new G4LogicalVolume(consSolid,         //its solid
                        quartz,          //its material
                        "Cons");           //its name
               
  G4VPhysicalVolume* consPhys = new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    consLogical,             //its logical volume
                    "Cons",                //its name
                    expHall_log,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  G4double shape1_rminb_w =  1.*cm, shape1_rmaxb_w = 1.1*cm;
  G4double shape1_rmina_w =  2.*cm, shape1_rmaxa_w = 2.1*cm;

  G4Cons* wrapSolid_c =    
    new G4Cons("AlumWrap_c",                      //its name
    shape1_rmina_w, shape1_rmaxa_w, shape1_rminb_w, shape1_rmaxb_w, shape1_hz,
    shape1_phimin, shape1_phimax);        //its size
                
  G4LogicalVolume* wrapLogical_c =                         
    new G4LogicalVolume(wrapSolid_c,         //its solid
                        alum,          //its material
                        "AlumWrap_c");           //its name
               
  G4VPhysicalVolume* wrapPhys_c =  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    wrapLogical_c,             //its logical volume
                    "AlumWrap_c",                //its name
                    expHall_log,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking



  //     
  // Shape 2
  //
  G4ThreeVector pos2 = G4ThreeVector(0*cm, 0*cm, 0*cm);
  
  //Tube shape
  

  G4Tubs* tubeSolid =    
    new G4Tubs("Tube",                      //its name
              0, shape1_rmaxa, 2*shape1_hz, 
               shape1_phimin, shape1_phimax); //its size
                
  G4LogicalVolume* tubeLogical =                         
    new G4LogicalVolume(tubeSolid,         //its solid
                        quartz,          //its material
                        "Tube");           //its name
               
  G4VPhysicalVolume* tubePhys =  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    tubeLogical,             //its logical volume
                    "Tube",                //its name
                    expHall_log,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  G4Tubs* wrapSolid =    
    new G4Tubs("AlumWrap",                      //its name
              shape1_rmaxa+0.005*cm, shape1_rmaxa+0.01*cm, 2*shape1_hz, 
               shape1_phimin, shape1_phimax); //its size
                
  G4LogicalVolume* wrapLogical =                         
    new G4LogicalVolume(wrapSolid,         //its solid
                        alum,          //its material
                        "AlumWrap");           //its name
               
  G4VPhysicalVolume* wrapPhys =  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    wrapLogical,             //its logical volume
                    "AlumWrap",                //its name
                    expHall_log,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

 G4Tubs* SilTube1 = new G4Tubs("Silicate detector 1",
			 0, shape1_rmaxa, 0.02*mm, 
			 shape1_phimin, shape1_phimax);
 G4LogicalVolume* SilTube1Logical =
    new G4LogicalVolume(SilTube1,
			si,
			"First");
G4VPhysicalVolume* Si1TubePhys = new G4PVPlacement(0, 
			G4ThreeVector(0., 0., -45.*mm),
			SilTube1Logical,
			"FirstPhys",
			expHall_log,
			false,
			0,
			checkOverlaps);

//------------------

//---------------


 G4OpticalSurface* opAlumSurface = new G4OpticalSurface("AlumSurface");
 opAlumSurface->SetType(dielectric_metal);
 opAlumSurface->SetFinish(polished);
 opAlumSurface->SetModel(glisur);

  G4LogicalBorderSurface* alumSurface =
          new G4LogicalBorderSurface("AlumSurface",
                            wrapPhys,expHall_phys,opAlumSurface);

  G4OpticalSurface* opticalSurface = dynamic_cast <G4OpticalSurface*>
        (alumSurface->GetSurface(wrapPhys,expHall_phys)->
                                                       GetSurfaceProperty());
  if (opticalSurface) opticalSurface->DumpInfo();


 G4OpticalSurface* opAlumSurface_c = new G4OpticalSurface("AlumSurface_c");
 opAlumSurface_c->SetType(dielectric_metal);
 opAlumSurface_c->SetFinish(polished);
 opAlumSurface_c->SetModel(glisur);

  G4LogicalBorderSurface* alumSurface_c =
          new G4LogicalBorderSurface("AlumSurface_c",
                            wrapPhys_c,expHall_phys,opAlumSurface_c);

  G4OpticalSurface* opticalSurface_c = dynamic_cast <G4OpticalSurface*>
        (alumSurface_c->GetSurface(wrapPhys_c,expHall_phys)->
                                                       GetSurfaceProperty());
  if (opticalSurface) opticalSurface->DumpInfo();




// Si radiator
//
  G4OpticalSurface* opSiSurface = new G4OpticalSurface("SiSurface");
  opSiSurface->SetType(dielectric_metal);
  opSiSurface->SetFinish(polished);
  opSiSurface->SetModel(glisur);

  G4LogicalBorderSurface* SiSurface =
          new G4LogicalBorderSurface("SiSurface",
                             tubePhys,expHall_phys, opSiSurface);

   opticalSurface = dynamic_cast <G4OpticalSurface*>
        (SiSurface->GetSurface(tubePhys,expHall_phys)->
                                                        GetSurfaceProperty());
  if (opticalSurface) opticalSurface->DumpInfo();
// 14/10/2019

G4cout << " QRad 2 " << G4endl;
// ------------- Surfaces --------------



//always return the physical World
  return expHall_phys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
