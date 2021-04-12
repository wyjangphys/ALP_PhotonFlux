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
/// \file ALP_PhotonFlux_RunAction.cc
/// \brief Implementation of the ALP_PhotonFlux_RunAction class

#include "ALP_PhotonFlux_RunAction.hh"
#include "ALP_PhotonFlux_PrimaryGeneratorAction.hh"
#include "ALP_PhotonFlux_DetectorConstruction.hh"
// #include "ALP_PhotonFlux_Run.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ALP_PhotonFlux_RunAction::ALP_PhotonFlux_RunAction()
: G4UserRunAction()
{
  // Create analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetNtupleMerging(true);
  analysisManager->SetVerboseLevel(1);

  // Create ROOT TTree(Ntuple)
  analysisManager->CreateNtuple(
      "ALP_PhotonFlux",     // Name of TTree
      "ALP_PhotonFlux");    // Title of TTree
  analysisManager->CreateNtupleSColumn("proc");
  analysisManager->CreateNtupleDColumn("Egamma");
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("px");
  analysisManager->CreateNtupleDColumn("py");
  analysisManager->CreateNtupleDColumn("pz");
  analysisManager->CreateNtupleDColumn("pdir_x");
  analysisManager->CreateNtupleDColumn("pdir_y");
  analysisManager->CreateNtupleDColumn("pdir_z");
  analysisManager->CreateNtupleSColumn("pid");
  analysisManager->CreateNtupleSColumn("poststep_pid");     // pid of the mother particle
  analysisManager->CreateNtupleDColumn("inTarget");
  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ALP_PhotonFlux_RunAction::~ALP_PhotonFlux_RunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ALP_PhotonFlux_RunAction::BeginOfRunAction(const G4Run*)
{
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

  // Analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Default settings
  analysisManager->SetFileName("/run/media/wyjang/Seagate5TB/data/ALP_PhotonFlux/P_120GeV_100000POT"); // the actual file name will be ALP_PhotonFlux.root
  analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ALP_PhotonFlux_RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // Print
  //
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

