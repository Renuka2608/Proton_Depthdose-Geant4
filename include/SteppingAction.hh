#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"


class G4LogicalVolume;       //Forward Declaration
class G4Step;
class EventAction;
class RunAction;

class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(EventAction* eventAction , RunAction* runAction);  //SteppingAction receives a pointer to EventAction. Because SteppingAction must send energy deposition to EventAction.
	~SteppingAction() override = default;

	void UserSteppingAction(const G4Step*) override;

private:
	EventAction* fEventAction = nullptr;
	RunAction* fRunAction = nullptr;
	G4LogicalVolume* fScoringVolume = nullptr;
};
#endif
