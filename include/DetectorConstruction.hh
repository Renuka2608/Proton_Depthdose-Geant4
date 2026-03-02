#ifndef DetectorConstruction_h     //Header guards
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"   //abstract base class
#include "globals.hh"                      //unit systems, G4 types like G4int

// Forward Declaration
class G4PhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	virtual ~DetectorConstruction();

	virtual G4PhysicalVolume* Construct();

protected:
	G4LogicalVolume* fPhantomLogical;   //for later scoring access
};

#endif