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
  G4Material* aluminium = FCALMaterials->Material("Aluminium");
  
  G4Material* air = FCALMaterials->Material("Air");
  G4Material* quartz = FCALMaterials->Material("Quartz");
  G4Material* iron = FCALMaterials->Material("Iron");
  G4Material* water = FCALMaterials->Material("Water");
  G4Material* copper = FCALMaterials->Material("Copper");
  G4Material* Cd = FCALMaterials->Material("Cd");
  G4Material* silicon = FCALMaterials->Material("Silicon");





 

//
// ------------ Generate & Add Material Properties Table ------------
//
  const G4int NUMENTRIES = 2;
  
  G4double ephoton         [NUMENTRIES] = {2.00*eV,4.80*eV};

  G4double rindexQuartz    [NUMENTRIES] = {1.46,1.46};
  G4double absorptionQuartz[NUMENTRIES] = {46*m,46*m};

  //Fill in the Marterial properties table for quartz.
  //Guide for undestanding Optical processes at http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/ch05s02.html#sect.PhysProc.Photo
  G4MaterialPropertiesTable *quartzMPT = new G4MaterialPropertiesTable();
  quartzMPT->AddProperty("RINDEX",ephoton,rindexQuartz,NUMENTRIES);
  quartzMPT->AddProperty("ABSLENGTH",ephoton,absorptionQuartz,NUMENTRIES);   
  
  quartz->SetMaterialPropertiesTable(quartzMPT);

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

  G4Tubs* cladding = new G4Tubs("aTubeSolid", 0*cm, 2*cm, 45.0*cm, 0*deg, 360*deg);

  G4LogicalVolume* cladding_log
    = new G4LogicalVolume(cladding,quartz,"Cladding",0,0,0);

  G4VPhysicalVolume* cladding_phys
    = new G4PVPlacement(0,G4ThreeVector(),cladding_log,"Cladding",
                        expHall_log,false,0);


// The Quartz Rod

  G4Tubs* quartz_rod = new G4Tubs("aTubeSolid", 0*cm, 0.5*cm, 40.0*cm, 0*deg, 360*deg);
  G4LogicalVolume* quartz_rod_log
    = new G4LogicalVolume(quartz_rod,silicon,"Rod",0,0,0);

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
