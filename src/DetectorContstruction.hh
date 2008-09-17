#ifndef DETECTORCONTSTRUCTION_H
#define DETECTORCONTSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"

class G4Material;
class G4Element;
class G4Box;
class G4Tubs;
class G4LogicalVolume;
class G4ThreeVector;
class G4PVPlacement;


class DetectorContstruction : public G4VUserDetectorConstruction
{
public:
  DetectorContstruction();
  ~DetectorContstruction();

  G4VPhysicalVolume* Construct();
 
private:

}

#endif
