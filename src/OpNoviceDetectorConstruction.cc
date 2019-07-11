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

#include "OpNoviceDetectorConstruction.hh"
#include "FCALMaterialConsultant.hh" // construct Material
#include "OpticalConsultant.hh" // construct optical propertiesc

//add visualization
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceDetectorConstruction::OpNoviceDetectorConstruction()
 : G4VUserDetectorConstruction()
{
  fExpHall_x = fExpHall_y = fExpHall_z = 50.0*cm;
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceDetectorConstruction::~OpNoviceDetectorConstruction(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



G4VPhysicalVolume* OpNoviceDetectorConstruction::Construct()
{

  FCALMaterialConsultant * FCALMaterials = new FCALMaterialConsultant();
  FCALMaterials->GetInstance();

// ------------- Materials -------------
  
  G4Material* air = FCALMaterials->Material("Air");
  G4Material* quartz = FCALMaterials->Material("Quartz");
  G4Material* iron = FCALMaterials->Material("Iron");
  G4Material* water = FCALMaterials->Material("Water");


 

//
// ------------ Generate & Add Material Properties Table ------------
//
/*

  OpticalConsultant * OpticalProperty = new OpticalConsultant();
  OpticalProperty->GetInstance();  

  air->SetMaterialPropertiesTable(OpticalProperty->myMPT2);

  water->SetMaterialPropertiesTable(OpticalProperty->myMPT1);

  // Set the Birks Constant for the Water scintillator

  water->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
*/


 const G4int nEntries = 32;

  G4double PhotonEnergy[nEntries] =
            { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
              2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
              2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
              2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
              2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
              3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
              3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
              3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };
//
// Water
//	      
  G4double RefractiveIndex1[nEntries] =
            { 1.3435, 1.344,  1.3445, 1.345,  1.3455,
              1.346,  1.3465, 1.347,  1.3475, 1.348,
              1.3485, 1.3492, 1.35,   1.3505, 1.351,
              1.3518, 1.3522, 1.3530, 1.3535, 1.354,
              1.3545, 1.355,  1.3555, 1.356,  1.3568,
              1.3572, 1.358,  1.3585, 1.359,  1.3595,
              1.36,   1.3608};

  G4double Absorption1[nEntries] =
           {3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
           15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
           45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
           52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
           30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
           17.500*m, 14.500*m };

  G4double ScintilFast[nEntries] =
            { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00 };
  G4double ScintilSlow[nEntries] =
            { 0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00,
              7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 4.00,
              3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00,
              4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,
              7.00, 6.00, 5.00, 4.00 };

  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();
  myMPT1->AddProperty("RINDEX",       PhotonEnergy, RefractiveIndex1,nEntries);
  myMPT1->AddProperty("ABSLENGTH",    PhotonEnergy, Absorption1,     nEntries);
  myMPT1->AddProperty("FASTCOMPONENT",PhotonEnergy, ScintilFast,     nEntries);
  myMPT1->AddProperty("SLOWCOMPONENT",PhotonEnergy, ScintilSlow,     nEntries);
  
  myMPT1->AddConstProperty("SCINTILLATIONYIELD",50./MeV);
  myMPT1->AddConstProperty("RESOLUTIONSCALE",1.0);
  myMPT1->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
  myMPT1->AddConstProperty("SLOWTIMECONSTANT",10.*ns);
  myMPT1->AddConstProperty("YIELDRATIO",0.8);
  
  water->SetMaterialPropertiesTable(myMPT1);

//
// Air
//
  G4double RefractiveIndex2[nEntries] =
            { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00 };

  G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
  myMPT2->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex2, nEntries);
  
  air->SetMaterialPropertiesTable(myMPT2);


//
// ------------- Volumes --------------


// The experimental Hall
//
  G4Box* expHall_box = new G4Box("World",fExpHall_x,fExpHall_y,fExpHall_z);

  G4LogicalVolume* expHall_log
    = new G4LogicalVolume(expHall_box,air,"World",0,0,0);

  G4VPhysicalVolume* expHall_phys
    = new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);


// The cladding shell
//

  G4Tubs* cladding = new G4Tubs("aTubeSolid", 0*cm, 2*cm, 45.0*cm, 0*deg, 360*deg);

  G4LogicalVolume* cladding_log
    = new G4LogicalVolume(cladding,iron,"Cladding",0,0,0);

  G4VPhysicalVolume* cladding_phys
    = new G4PVPlacement(0,G4ThreeVector(),cladding_log,"Cladding",
                        expHall_log,false,0);


// The Quartz Rod

  G4Tubs* quartz_rod = new G4Tubs("aTubeSolid", 0*cm, 0.5*cm, 40.0*cm, 0*deg, 360*deg);
  G4LogicalVolume* quartz_rod_log
    = new G4LogicalVolume(quartz_rod,water,"Rod",0,0,0);

  G4VPhysicalVolume* quartz_rod_phys
    = new G4PVPlacement(0,G4ThreeVector(),quartz_rod_log,"QuartzRod",
                        cladding_log,false,0);

//Add visualization color

 
  
  G4VisAttributes * ColorOfCladding = new G4VisAttributes(true,G4Colour(0,0,1.0));
  ColorOfCladding->SetForceSolid(true);
  cladding_log->SetVisAttributes(ColorOfCladding);
  
  G4VisAttributes * ColorOfQuartzRod = new G4VisAttributes(true,G4Colour(1.0,0,0));
  ColorOfQuartzRod->SetForceSolid(true);
  quartz_rod_log->SetVisAttributes(ColorOfQuartzRod);

/*
//  ------------- Surfaces --------------
//
// Water Tank
//
  G4OpticalSurface* OpWaterSurface = new G4OpticalSurface("WaterSurface");
  OpWaterSurface->SetType(dielectric_dielectric);
  OpWaterSurface->SetFinish(ground);
  OpWaterSurface->SetModel(unified);

  G4LogicalBorderSurface* WaterSurface = 
                                 new G4LogicalBorderSurface("WaterSurface",
                                 waterTank_phys,expHall_phys,OpWaterSurface);

  if(WaterSurface->GetVolume1() == waterTank_phys) G4cout << "Equal" << G4endl;
  if(WaterSurface->GetVolume2() == expHall_phys  ) G4cout << "Equal" << G4endl;

// Air Bubble
//
  G4OpticalSurface* OpAirSurface = new G4OpticalSurface("AirSurface");
  OpAirSurface->SetType(dielectric_dielectric);
  OpAirSurface->SetFinish(polished);
  OpAirSurface->SetModel(glisur);

  G4LogicalSkinSurface* AirSurface = 
    new G4LogicalSkinSurface("AirSurface", bubbleAir_log, OpAirSurface);

  if(AirSurface->GetLogicalVolume() == bubbleAir_log) G4cout << "Equal" << G4endl;
  ((G4OpticalSurface*)
  (AirSurface->GetSurface(bubbleAir_log)->GetSurfaceProperty()))->DumpInfo();

//
// Generate & Add Material Properties Table attached to the optical surfaces
//
  const G4int num = 2;
  G4double Ephoton[num] = {2.038*eV, 4.144*eV};

  //OpticalWaterSurface 
  G4double RefractiveIndex[num] = {1.35, 1.40};
  G4double SpecularLobe[num]    = {0.3, 0.3};
  G4double SpecularSpike[num]   = {0.2, 0.2};
  G4double Backscatter[num]     = {0.2, 0.2};

  G4MaterialPropertiesTable* myST1 = new G4MaterialPropertiesTable();
  
  myST1->AddProperty("RINDEX",                Ephoton, RefractiveIndex, num);
  myST1->AddProperty("SPECULARLOBECONSTANT",  Ephoton, SpecularLobe,    num);
  myST1->AddProperty("SPECULARSPIKECONSTANT", Ephoton, SpecularSpike,   num);
  myST1->AddProperty("BACKSCATTERCONSTANT",   Ephoton, Backscatter,     num);

  OpWaterSurface->SetMaterialPropertiesTable(myST1);

  //OpticalAirSurface
  G4double Reflectivity[num] = {0.3, 0.5};
  G4double Efficiency[num]   = {0.8, 1.0};

  G4MaterialPropertiesTable *myST2 = new G4MaterialPropertiesTable();

  myST2->AddProperty("REFLECTIVITY", Ephoton, Reflectivity, num);
  myST2->AddProperty("EFFICIENCY",   Ephoton, Efficiency,   num);

  OpAirSurface->SetMaterialPropertiesTable(myST2);

//always return the physical World
*/
  return expHall_phys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
