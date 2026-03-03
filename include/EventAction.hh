#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class G4Event;
class RunACtion;

class EventAction : public G4UserEventAction
{
public:
	EventAction(RunAction* runAction);           //EventAction receives a pointer to RunAction.
	~EventAction() override = default;

	void BeginOfEventAction(c  G4LogicalVolume* fScoringVolume = nullptr;onst G4Event* event) override;
	void EndOfEventAction(const G4Event* event) override;

	void  AddEdep(G4double edep) { fEdep += edep; }

private:
	RunAction* fRunAction = nullptr;
	G4double fEdep = 0.;
};

#endif 
