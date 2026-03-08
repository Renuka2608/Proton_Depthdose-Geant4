#include "ActionInitialization.hh"

#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"


void ActionInitialization::BuildForMaster() const
{
	auto runAction = new RunAction;
	SetUserAction(runAction);
}

void ActionInitialization::Build() const
{
	SetUserAction(new PrimaryGeneratorAction());

	auto runAction = new RunAction;
	SetUserAction(runAction);

	auto eventAction = new EventAction(runAction);
	SetUserAction(eventAction);

	// Pass BOTH eventAction and runAction
	SetUserAction(new SteppingAction(eventAction , runAction));
}