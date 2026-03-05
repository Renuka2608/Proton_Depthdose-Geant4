#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4AnalysisManager.hh"


SteppingAction::SteppingAction(EventAction* eventAction): fEventAction(eventAction) {}         //SteppingAction can send energy deposition data to EventAction

void SteppingAction::UserSteppingAction(const G4Step* step)
{
	if (!fScoringVolume) {
		const auto detConstruction = static_cast<const DetectorConstruction*>(
			G4RunManager::GetRunManager()->GetUserDetectorConstruction());             //retrieves the phantom volume where dose should be measured
		fScoringVolume = detConstruction->GetScoringVolume();
	}

	// get volume of the current step
	G4LogiclaVolume* colume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();        //checks Where is the particle currently stepping

	//check if we are in scoring volume
	if (volume != fScoringVolume) return;

	//record Energy Deposition
	G4double edepStep = step->GetTotalEnergyDeposit();

	G4double z = step->GetPreStepPoint()->GetPosition().z();     //3Send Data to Histogram

	auto analysisManager = G4AnalysisManager::Instance();
	analysisManager->FillH1(0, z / mm, edepStep / MeV);

	fEventAction->AddEdep(edepStep);                        //send energy to eventAction


}
