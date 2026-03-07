#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
#include <fstream>

class G4Run;

class RunAction : public G4UserRunAction
{
	std::ofstream outFile;

public:
	RunAction();
	~RunAction() override = default;
	
	void BeginOfRunAction(const G4Run*) override;
	void EndOfRunAction(const G4Run*) override;

	void AddEdep(G4double edep);
	
private:
	G4Accumulable<G4double> fEdep = 0.;     //fEdep = total deposited energy      
	G4Accumulable<G4double> fEdep2 = 0.;   //fEdep2 = used to calculate RMS / statistical error
};
#endif 
