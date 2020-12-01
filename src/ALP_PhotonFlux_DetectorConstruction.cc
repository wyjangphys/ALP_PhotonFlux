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
/// \file ALP_PhotonFlux_DetectorConstruction.cc
/// \brief Implementation of the ALP_PhotonFlux_DetectorConstruction class

#include "ALP_PhotonFlux_DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4FieldManager.hh"
#include "G4MagneticField.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4UniformMagField.hh"
#include "G4SDManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ALP_PhotonFlux_DetectorConstruction::ALP_PhotonFlux_DetectorConstruction()
: G4VUserDetectorConstruction(),
  fWorldVolume(0),
  fTargetVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ALP_PhotonFlux_DetectorConstruction::~ALP_PhotonFlux_DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* ALP_PhotonFlux_DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Target parameters
  //
  G4double target_sizeXY = 1 * m, target_sizeZ = 1.5 * m;
  G4Material* target_mat = nist->FindOrBuildMaterial("G4_C");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 1.2 * target_sizeXY;
  G4double world_sizeZ  = 1.2 * target_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY,    //its size in X
       0.5*world_sizeXY,    //its size in Y
       0.5*world_sizeZ);    //its size in Z

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //
  // Graphite target
  //
  G4Tubs* target =
    new G4Tubs("target",
        0,
        0.85*cm,
        0.75*m,
        0,
        2.*3.14159265358979323846);

  G4LogicalVolume* logicTarget =
    new G4LogicalVolume(target,            //its solid
                        target_mat,        //its material
                        "Target");         //its name

  new G4PVPlacement(0,                     //no rotation
                    G4ThreeVector(),       //at (0,0,0)
                    logicTarget,           //its logical volume
                    "Target",              //its name
                    logicWorld,            //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

  // Set iron dump as scoring volume
  //
  fTargetVolume   = logicTarget;

  //
  //always return the physical World
  //
  return physWorld;
}
