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
/// \file PhysicsList.cc
/// \brief Implementation of the PhysicsList class
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PhysicsList.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmParameters.hh"
#include "G4DecayPhysics.hh"
#include "G4NuclideTable.hh"
#include "G4RadioactiveDecayPhysics.hh"

//#include "G4HadronElasticPhysicsHP.hh"

#include "HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonPhysicsXS.hh"
#include "G4IonINCLXXPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "GammaNuclearPhysics.hh"

//#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4OpticalPhysics.hh"

// particles

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList()
    : G4VModularPhysicsList()
{
  G4int verb = 1;
  SetVerboseLevel(verb);

  //add new units for radioActive decays
  //
  new G4UnitDefinition("millielectronVolt", "meV", "Energy", 1.e-3 * eV);
  //
  const G4double minute = 60 * second;
  const G4double hour = 60 * minute;
  const G4double day = 24 * hour;
  const G4double year = 365 * day;
  new G4UnitDefinition("minute", "min", "Time", minute);
  new G4UnitDefinition("hour", "h", "Time", hour);
  new G4UnitDefinition("day", "d", "Time", day);
  new G4UnitDefinition("year", "y", "Time", year);

  // Mandatory for G4NuclideTable
  // Half-life threshold must be set small or many short-lived isomers
  // will not be assigned life times (default to 0)
  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(0.1 * picosecond);
  G4NuclideTable::GetInstance()->SetLevelTolerance(1.0 * eV);

  //Modified G4 Hadron Elastic scattering: add thermal scattering
  RegisterPhysics( new HadronElasticPhysicsHP(verb) );
  
  // Hadron Inelastic Physics
  RegisterPhysics( new G4HadronPhysicsFTFP_BERT_HP(verb));
  ////RegisterPhysics( new G4HadronPhysicsQGSP_BIC_HP(verb));
  ////RegisterPhysics( new G4HadronInelasticQBBC(verb));        
  ////RegisterPhysics( new G4HadronPhysicsINCLXX(verb));

  // Ion Elastic scattering
  RegisterPhysics( new G4IonElasticPhysics(verb));

  // Ion Inelastic Physics
  RegisterPhysics( new G4IonPhysicsXS(verb));
  ////RegisterPhysics( new G4IonINCLXXPhysics(verb));
  
  // stopping Particles
  RegisterPhysics( new G4StoppingPhysics(verb));
      
  // Gamma-Nuclear Physics
  RegisterPhysics( new GammaNuclearPhysics("gamma"));

 
  // Decay
  RegisterPhysics(new G4DecayPhysics());

  // Radioactive decay
  RegisterPhysics(new G4RadioactiveDecayPhysics());

  // EM physics
  /*
  emstandard_opt4 new physics constructor was designed for any applications required higher accuracy of electrons, hadrons and ion tracking. Use the most accurate standard and low-energy models. It is used in extended electromagnetic examples and in the QGSP_BIC_EMZ reference Physics List. The corresponding physics constructor includes following modifications with the G4EmStandardPhysics_option3.cc:
  
  G4KleinNishinaModel is used above 20 MeV, G4LowEPComptonModel is used below for the Compton scattering simulation. Both models provide simulation of Doppler broading and atomic deexcitation.
  G4PenelopeGammaConversion model is used for gamma conversion below 1 GeV;
  the parameter RangeFactor for multiple scattering of e+, e- is set to 0.01 (the default 0.04);
  for e+ and e- G4GoudsmithSaundersonModel is used below 100 MeV with step limitation UseSafetyPlus and skin=3 - the most accurate algorithm with single scattering in vicinity of a geometry boundary.
  */
  RegisterPhysics(new G4EmStandardPhysics_option4());


  //Optical photon Physics
  
  RegisterPhysics(new G4OpticalPhysics(verb));

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::~PhysicsList()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructParticle()
{
  G4BosonConstructor pBosonConstructor;
  pBosonConstructor.ConstructParticle();

  G4LeptonConstructor pLeptonConstructor;
  pLeptonConstructor.ConstructParticle();

  G4MesonConstructor pMesonConstructor;
  pMesonConstructor.ConstructParticle();

  G4BaryonConstructor pBaryonConstructor;
  pBaryonConstructor.ConstructParticle();

  G4IonConstructor pIonConstructor;
  pIonConstructor.ConstructParticle();

  G4ShortLivedConstructor pShortLivedConstructor;
  pShortLivedConstructor.ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCuts()
{
  SetCutValue(0 * mm, "proton");
  SetCutValue(10 * km, "e-");
  SetCutValue(10 * km, "e+");
  SetCutValue(10 * km, "gamma");
}
