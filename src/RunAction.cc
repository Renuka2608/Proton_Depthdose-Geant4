#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4AccumulableManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <cmath>
#include "G4AnalysisManager.hh"
#include "G4Accumulable.hh"

RunAction::RunAction()
{
		const G4double milligray = 1.e-3 * gray;
		const G4double microgray = 1.e-6 * gray;
		const G4double nanogray = 1.e-9 * gray;
		const G4double picogray = 1.e-12 * gray;

		new G4UnitDefinition("milligray", "milliGy", "Dose", milligray);
		new G4UnitDefinition("microgray", "microGy", "Dose", microgray);
		new G4UnitDefinition("nanogray", "nanoGy", "Dose", nanogray);
		new G4UnitDefinition("picogray", "picoGy", "Dose", picogray);
	

	//Register accumulables (total energy deposit and variance)
	auto accumulableManager = G4AccumulableManager::Instance();
	accumulableManager->RegisterAccumulable(fEdep);
	accumulableManager->RegisterAccumulable(fEdep2);

	auto analysisManager = G4AnalysisManager::Instance();
	analysisManager->SetVerboseLevel(1);
	analysisManager->SetDefaultFileType("root");
	analysisManager->SetNtupleMerging(true);       // merge threads automatically


	analysisManager->CreateH1(
		"depthDose",
		"Depth Dose Distribution",
		300,                          // bins 
		0., 300.            // z range in mm
	);
	
	// Create Ntuple for raw step data (optional but useful)
	analysisManager->CreateNtuple("StepData", "Step-by-step data");
	analysisManager->CreateNtupleDColumn("z_mm");      // column 0
	analysisManager->CreateNtupleDColumn("edep_MeV");  // column 1
	analysisManager->FinishNtuple();
}


void RunAction::BeginOfRunAction(const G4Run*)
{
	// don't store random seeds
	G4RunManager::GetRunManager()->SetRandomNumberStore(false);

	//Reset accumulables
	auto accumulableManager = G4AccumulableManager::Instance();
	accumulableManager->Reset();                                  //Resets total energy before starting the run

	auto analysisManager = G4AnalysisManager::Instance();
	analysisManager->OpenFile("braggPeak");                     //open root file

	G4cout << "BeginOfRunAction : braggPeak.root opened." << G4endl;
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

	auto analysisManager = G4AnalysisManager::Instance();
	analysisManager->Write();
	analysisManager->CloseFile();              //save root file
	
	G4cout << "braggPeak.root saved." << G4endl;	
}

void RunAction::FillDepthDose(G4double z_mm, G4double edep_MeV)
{
	auto analysisManager = G4AnalysisManager::Instance();
	analysisManager->FillH1(0, z_mm, edep_MeV);      // fill histogram
	analysisManager->FillNtupleDColumn(0, 0, z_mm);   // fill ntuple col 0
	analysisManager->FillNtupleDColumn(0, 1, edep_MeV); // fill ntuple col 1
	analysisManager->AddNtupleRow(0);
}

void RunAction::AddEdep(G4double edep)
{
	fEdep += edep;       //Adds event energy to total run energy
	fEdep2 += edep * edep;
}