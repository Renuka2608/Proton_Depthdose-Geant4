#include "SteppingAction.hh"
#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>


// Update constructor to also take RunAction*
SteppingAction::SteppingAction(EventAction* eventAction, RunAction* runAction)
    : fEventAction(eventAction), fRunAction(runAction) {

}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    // DEBUG: confirm stepping action is being called at ALL
   // G4cout << "[SteppingAction] UserSteppingAction called." << G4endl;

    if (!fScoringVolume) {
        const auto detConstruction = static_cast<const DetectorConstruction*>(
            G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        fScoringVolume = detConstruction->GetScoringVolume();


        // DEBUG: check if scoring volume was found
        if (!fScoringVolume) {
            G4cout << "[SteppingAction] ERROR: fScoringVolume is NULL!" << G4endl;
            return;
        }
        G4cout << "[SteppingAction] Scoring volume: "
            << fScoringVolume->GetName() << G4endl;
    }


    // get volume of the current step
    G4LogicalVolume* volume =
        step->GetPreStepPoint()->GetTouchableHandle()
        ->GetVolume()->GetLogicalVolume();

    // DEBUG: print what volume each step is in
   // G4cout << "[SteppingAction] Current volume: " << volume->GetName() << G4endl;

    // check if we are in scoring volume
    if (volume != fScoringVolume) return;

    // record Energy Deposition
    G4double edepStep = step->GetTotalEnergyDeposit();
    G4double z = step->GetPreStepPoint()->GetPosition().z();

   /* G4cout << "[SteppingAction] HIT! z=" << z / mm << " mm, edep="
        << edepStep / MeV << " MeV" << G4endl; */


    // Writing via RunAction's open file handle (no double-open conflict)
    fRunAction->FillDepthDose(z / mm, edepStep / MeV);


    // Send energy to EventAction 
    fEventAction->AddEdep(edepStep);
}                                                    // <-- closing brace for UserSteppingAction