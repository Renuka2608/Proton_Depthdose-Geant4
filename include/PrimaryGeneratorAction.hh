#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
	PrimaryGeneratorAction();                     // constructor
	~PrimaryGeneratorAction() override;         // destructor

	void GeneratePrimaries(G4Event*) override;         //G4 passes a pointer to the event.

	const G4ParticleGun* GetParticleGun() const { return fParticleGun; }     //Here, const means function does not modify class/ any member variables.
	                                                                        //Other classes cannot modify the particle gun using this getter.
private:
	G4ParticleGun* fParticleGun = nullptr;
	G4Box* fEnvelopeBox = nullptr;
};

#endif