#include "RunAction.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4AccumulableManager.hh"
//#include "G4LogicalVolume.hh"
//#include "G4ParticleDefinition.hh"
//#include "G4ParticleGun.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <cmath>

RunAction::RunAction()
{
	//Register accumulables (total energy deposit and variance)
	auto accumulableManager = G4AccumulableManager::Instance();
	accumulableManager->Regiter(fEdep);
	accumulableManager->Regiter(fEdep2);

}
void RunAction::BeginOfRunAction(const G4Run*)
{
	// don't store random seeds
	G4RunManager::GetRunManager()->SetRandomNumberStore(false);

	//Reset accumulables
	auto accumulableManager = G4AccumulableManager::Instance();
	accumulableManager->Reset();                                  //Resets total energy before starting the run

}

void RunAction::EndOfRunAction(const G4Run* run)
{
	G4int nofEvents = run->GetNumberOfEvent();
	if (nofEvents == 0)return;

	//Merge energy from threads
	auto accumulableManager = G4AccumulableManager::Instance();
	accumulableManager->Merge();

	//total deposited energy
	G4double edep = fEdep.GetValue();
	G4double edep2 = fEdep2.GetValue();

	//Compute RMS
	G4double rms = edep2 - edep * edep / nofEvents;
	if (rms > 0.)
		rms = std::sqrt(rms);
	else rms = 0.;

	//Get Phantom mass
	const auto detectorConstruction = static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());

	G4double mass = detectorConstruction->GetScoringVolume()->GetMass();

	//Dose= Energy/Mass
	G4double dose = edep / mass;
	G4double rmsDose = rms / mass;

	//Print results
	G4cout << G4endl;
	G4cout << "================ Run Summary ================" << G4endl;
	G4cout << "Number of events: " << nofEvents << G4endl;
	G4cout << "Dose in phantom: "
		<< G4BestUnit(dose, "Dose")
		<< "   RMS: "
		<< G4BestUnit(rmsDose, "Dose")
		<< G4endl;
	G4cout << "=============================================" << G4endl;

}

void RunAction::AddEdep(G4double edep)
{
	fEdep += edep;       //Adds event energy to total run energy
	fEdep2 += edep* edep;
}