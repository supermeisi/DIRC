#ifndef PMDETECTORCONSTRUCTION_HH
#define PMDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

#include "G4Box.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "PMSensitiveDetector.hh"
#include "G4SDManager.hh"

class PMDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    PMDetectorConstruction();
    virtual ~PMDetectorConstruction();

    G4LogicalVolume *logicRad;

    virtual G4VPhysicalVolume *Construct();
    virtual void ConstructSDandField();
};

#endif