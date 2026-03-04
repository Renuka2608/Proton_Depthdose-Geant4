#include "DetectorConstruction.hh"

#include "G4NistMnager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

// Constructor & Destructor
DetectorConstruction::DetectorConstruction(): G4DetectorConstruction();
 fPhantomLogical(nullptr)
{ }

DetectorConstruction::~DetectorConstruction() {}

G4PhysicalVolume* DetectorConstruction::Construct()
{

//NIST material manager
	G4NistManager* nist = G4NistManager::Instance()

		// Materials
	G4Material * worldMaterial = nist->FindOrBuildMaterial("G4_AIR");
	G4Material* phantomMaterial = nist->FindOrBuildMaterial("G4_WATER");


// World Volume
	G4double worldSizeXY = 50*cm;
	G4double worldSizeZ = 50*cm;

	G4Box* solidWorld =
		new G4Box("World",
			worldSizeXY / 2,
			worldSizeXY / 2,
			worldSizeZ / 2);

	G4LogicalVolume* logicWorld =
		new G4LogicalVolume(solidWorld,
							worldMaterial,
							"World");

	G4VPhysicalVolume* physworld =
		new G4PVPlacement(0,
			G4Vector(),
			logicWorld,
			"World",
			0,
			false,
			0,
			true);

//Water Phantom
	G4double worldSizeXY = 10 * cm;
	G4double worldSizeZ = 30 * cm;

	G4Box* solidPhantom =
		new G4Box("Phantom",
			worldSizeXY / 2,
			worldSizeXY / 2,
			worldSizeZ / 2);

	fPhantomLogical =
		new G4LogicalVolume(solidPhantom,
			phantomMaterial,
			"Phantom");

		new G4PVPlacement(0,
						G4Vector(0,0,0),
						fPhantomLogical,
						"Phantom",
						logicWorld,
						false,
						0,
						true);

		return phyWorld;
}