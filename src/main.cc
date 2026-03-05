//Main Program of Proton Depth Dose

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "QBBC.hh"

#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4String.hh"

int main(int argc, char** argv)
{
	// Detect interactive mode (if no arguments) and define UI session
	G4UIExecutive* ui = nullptr;
	if (argc == 1) {
	 ui = new G4UIExecutive(argc, argv);
	}

	// Stepping Precision
	G4int precision = 4;
		G4SteppingVerbose::UseBestUnit(precision);

// Run Manager (Core Engine)
		auto runManager =
			G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
	
// Register Mandatory initialization Classes
//Detector Construction
		runManager->SetUserInitialization(new DetectorConstruction());
//Physics List
		auto physicsList = new QBBC;
		physicsList->SetVerboseLevel(1);
		runManager->SetUserInitialization(physicsList);

// User Action Initialization
		runManager->SetUserInitialization(new ActionInitialization());

// Visualization Manager
		auto visManager = new G4VisExecutive();
		visManager->Initialize();

//UI Manager
		auto UImanager = G4UImanager::GetUIpointer();

		// Process macro or start UI session
			// batch mode
		if (!ui) {
			G4String command = "/control/execute ";
			G4String fileName = argv[1];
			UImanager->ApplyCommand(command + fileName);
		}
		else {
			// interactive mode
			UImanager->ApplyCommand("/control/execute init_vis.mac");
			ui->SessionStart();
			delete ui;
		}

		delete visManager;
		delete runManager;
		return 0;
		}



