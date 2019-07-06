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
//                       Rachid Mazini    Rachid.Mazini@cern.ch  
//
//   Language:           C++
//   Tested on:          g++
//   Prerequisites:      None
//   Purpose:            Header file for the Material Expert for the Atlas FCAL
//                       See OpticalConsultant for more details.
//   Developped on:      10-March-2000  M.F. R.M.
//   History:
//
//----------------------------------------------------------------------------

#ifndef OpticalConsultant_h
#define OpticalConsultant_h 1

#include "G4Material.hh"
#include "G4Element.hh"
#include "globals.hh"

//#include "FCALParameters.hh"

class OpticalConsultant
{
public:

  ~OpticalConsultant() {;};
  static OpticalConsultant * GetInstance();
  //G4Material * Material(G4String);


public:
  static OpticalConsultant * theOpticalConsultant;
  OpticalConsultant();
  G4MaterialPropertiesTable* myMPT1;
  G4MaterialPropertiesTable* myMPT2;

private:
  static G4double photonEnergy[];
  static G4double refractiveIndex1[];
  static G4double absorption[];
  static G4double scintilFast[];
  static G4double scintilSlow[];
  static G4double energy_water[];
  static G4double mie_water[];
  static G4double mie_water_const[3];
  static G4double refractiveIndex2[];

 
};

#endif   /* OpticalConsultant.hh */




