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
/// \file ALP_PhotonFlux_SteppingAction.cc
/// \brief Implementation of the ALP_PhotonFlux_SteppingAction class

#include "ALP_PhotonFlux_SteppingAction.hh"
#include "ALP_PhotonFlux_EventAction.hh"
#include "ALP_PhotonFlux_DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4ParticleTypes.hh"
#include "g4root.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ALP_PhotonFlux_SteppingAction::ALP_PhotonFlux_SteppingAction(ALP_PhotonFlux_EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fTargetVolume(0),
  fWorldVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ALP_PhotonFlux_SteppingAction::~ALP_PhotonFlux_SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ALP_PhotonFlux_SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fWorldVolume || !fTargetVolume) {
    const ALP_PhotonFlux_DetectorConstruction* detectorConstruction
      = static_cast<const ALP_PhotonFlux_DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fWorldVolume = detectorConstruction->GetWorldVolume();
    fTargetVolume = detectorConstruction->GetWorldVolume();
  }

  // get volume of the current step
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  auto analysisManager = G4AnalysisManager::Instance();
  const std::vector<const G4Track*>* secondary = step->GetSecondaryInCurrentStep();
  for( size_t lp = 0; lp < (*secondary).size(); lp++ )
  {
    analysisManager->FillNtupleSColumn(0, step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());
    analysisManager->FillNtupleDColumn(1, (G4double)(*secondary)[lp]->GetTotalEnergy()/CLHEP::GeV);
    analysisManager->FillNtupleDColumn(2, (G4double)(*secondary)[lp]->GetPosition().getX());
    analysisManager->FillNtupleDColumn(3, (G4double)(*secondary)[lp]->GetPosition().getY());
    analysisManager->FillNtupleDColumn(4, (G4double)(*secondary)[lp]->GetPosition().getZ());
    analysisManager->FillNtupleDColumn(5, (G4double)(*secondary)[lp]->GetMomentum().getX()/CLHEP::GeV);
    analysisManager->FillNtupleDColumn(6, (G4double)(*secondary)[lp]->GetMomentum().getY()/CLHEP::GeV);
    analysisManager->FillNtupleDColumn(7, (G4double)(*secondary)[lp]->GetMomentum().getZ()/CLHEP::GeV);
    analysisManager->FillNtupleDColumn(8, (G4double)(*secondary)[lp]->GetMomentumDirection().getX());
    analysisManager->FillNtupleDColumn(9, (G4double)(*secondary)[lp]->GetMomentumDirection().getY());
    analysisManager->FillNtupleDColumn(10, (G4double)(*secondary)[lp]->GetMomentumDirection().getZ());
    analysisManager->FillNtupleSColumn(11, (*secondary)[lp]->GetDefinition()->GetParticleName() );
    analysisManager->FillNtupleSColumn(12, step->GetTrack()->GetParticleDefinition()->GetParticleName());
    analysisManager->FillNtupleDColumn(13, (volume == fTargetVolume)?1:0);
    analysisManager->FillNtupleDColumn(14, (*secondary)[lp]->GetTrackLength()/CLHEP::nm);
    analysisManager->AddNtupleRow();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

