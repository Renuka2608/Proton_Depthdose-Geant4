#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class ActionInitialization: public G4VUserActionInitialization
{
	public:

	ActionInitialization() = default;
	~ActionInitialization() override = default;  //overriding the base destructor

	void BuildForMaster() const override;  //These functions are overriding virtual functions from the base class
	void Build() const override;

};
#endif 
