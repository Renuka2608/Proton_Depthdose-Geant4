#ifndef DetectorConstruction_h     //Header guards
#define DetectorConstruction_h 1

#include "G4UserDetectorConstruction.hh"
#include "globals.hh"

// Forward Declaration
class G4PhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction : public G4UserDetectorConstruction
{
public:
	DetectorConstruction();
	virtual ~DetectorConstruction();

	virtual G4PhysicalVolume* Construct();

private:
	G4LogicalVolume* fPhantomLogical;   //for later scoring access
};

#endif