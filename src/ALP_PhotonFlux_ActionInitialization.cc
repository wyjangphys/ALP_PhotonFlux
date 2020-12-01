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
/// \file ALP_PhotonFlux_ActionInitialization.cc
/// \brief Implementation of the ALP_PhotonFlux_ActionInitialization class

#include "ALP_PhotonFlux_ActionInitialization.hh"
#include "ALP_PhotonFlux_PrimaryGeneratorAction.hh"
#include "ALP_PhotonFlux_RunAction.hh"
#include "ALP_PhotonFlux_EventAction.hh"
#include "ALP_PhotonFlux_SteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ALP_PhotonFlux_ActionInitialization::ALP_PhotonFlux_ActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ALP_PhotonFlux_ActionInitialization::~ALP_PhotonFlux_ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ALP_PhotonFlux_ActionInitialization::BuildForMaster() const
{
  ALP_PhotonFlux_RunAction* runAction = new ALP_PhotonFlux_RunAction;
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ALP_PhotonFlux_ActionInitialization::Build() const
{
  SetUserAction(new ALP_PhotonFlux_PrimaryGeneratorAction);

  ALP_PhotonFlux_RunAction* runAction = new ALP_PhotonFlux_RunAction;
  SetUserAction(runAction);

  ALP_PhotonFlux_EventAction* eventAction = new ALP_PhotonFlux_EventAction(runAction);
  SetUserAction(eventAction);

  ALP_PhotonFlux_SteppingAction* steppingAction = new ALP_PhotonFlux_SteppingAction(eventAction);
  SetUserAction(steppingAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
