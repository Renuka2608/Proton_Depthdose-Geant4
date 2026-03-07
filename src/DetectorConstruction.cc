#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

// Constructor & Destructor
DetectorConstruction::DetectorConstruction()
	:G4VUserDetectorConstruction(),
	fScoringVolume(nullptr)
{ }

DetectorConstruction::~DetectorConstruction() = default;

G4VPhysicalVolume* DetectorConstruction::Construct()
{

//NIST material manager
	G4NistManager* nist = G4NistManager::Instance();

// Materials
	G4Material* worldMaterial = nist->FindOrBuildMaterial("G4_AIR");
	G4Material* phantomMaterial = nist->FindOrBuildMaterial("G4_WATER");


// World Volume
	G4double worldSizeX = 1*m;
	G4double worldSizeY = 1*m;
	G4double worldSizeZ = 1*m;

	// Define Shape 
	G4Box* solidWorld = new G4Box("World",
							worldSizeX / 2,
							worldSizeY / 2,
							worldSizeZ / 2);

	// Define Logical volume 
	G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,
													worldMaterial,
													"World");
		

	// Place it
	G4VPhysicalVolume* physWorld = new G4PVPlacement(0,                      // no rotation
													G4ThreeVector(),         // at (0,0,0)
													logicWorld,
													"World",
													0,                      // it's mother volume
													false,                  // no boolean operation- parameter : G4bool pMany
													0,						// copy number
													true);					// overlaps checking
		

//Water Phantom
	G4double phantomSizeX = 20 * cm;
	G4double phantomSizeY = 20 * cm;
	G4double phantomSizeZ = 30 * cm;

	G4Box* solidPhantom = new G4Box("Phantom",
									worldSizeX / 2,
									worldSizeY / 2,
									worldSizeZ / 2);
		

	fScoringVolume = new G4LogicalVolume(solidPhantom,
										phantomMaterial,
										"Phantom");
		

		new G4PVPlacement(0,
						G4ThreeVector(0,0,15*cm),
						fScoringVolume,
						"Phantom",
						logicWorld,               // it's mother volume. Envelope is inside World.
						false,			   		  // means This is not part of a multiple placement scheme.
						0,					      //G4int copyNo - Copy number is used when you place multiple identical volumes.
						true);

		return physWorld;
}