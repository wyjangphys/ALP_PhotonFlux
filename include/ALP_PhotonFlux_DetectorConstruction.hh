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
/// \file ALP_PhotonFlux_DetectorConstruction.hh
/// \brief Definition of the ALP_PhotonFlux_DetectorConstruction class

#ifndef ALP_PhotonFlux_DetectorConstruction_h
#define ALP_PhotonFlux_DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry

class ALP_PhotonFlux_DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    ALP_PhotonFlux_DetectorConstruction();
    virtual ~ALP_PhotonFlux_DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    G4LogicalVolume* GetWorldVolume() const { return fWorldVolume; }
    G4LogicalVolume* GetTargetVolume() const { return fTargetVolume; }

  private:

  protected:
    G4LogicalVolume* fWorldVolume;
    G4LogicalVolume* fTargetVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

