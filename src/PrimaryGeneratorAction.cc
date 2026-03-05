#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
	G4int n_particle = 1;
	fParticleGun = new G4ParticleGun(n_particle);

//Particle Definition
G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
G4ParticleDefinition* particle = particleTable->FindParticle("proton");
fParticleGun->SetParticleDefinition(particle);

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
//Beam Energy(150 MeV ±1%)

	G4double energy = G4RandGauss::shoot(150 * MeV, 1.5 * MeV);
	fParticleGun->SetParticleEnergy(energy);

//Beam Spot Size (5 mm)
	G4double beamSigma = 5 * mm;
	G4double x = G4RandGauss::shoot(0., beamSigma);
	G4double y = G4RandGauss::shoot(0., beamSigma);

	fParticleGun->SetParticlePosition(G4ThreeVector(x, y, 0.));

// Beam Divergence (~3 mrad)
	G4double thetaX = G4RandGauss::shoot(0., 0.003);
	G4double thetaY = G4RandGauss::shoot(0., 0.003);

	G4ThreeVector direction(thetaX, thetaY, 1.);
	direction = direction.unit();

	fParticleGun->SetParticleMomentumDirection(direction);

	//Generate event
	fParticleGun->GeneratePrimaryVertex(event);
}