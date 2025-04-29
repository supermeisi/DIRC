#include "PMDetectorConstruction.hh"

PMDetectorConstruction::PMDetectorConstruction()
{
}

PMDetectorConstruction::~PMDetectorConstruction()
{
}

G4VPhysicalVolume *PMDetectorConstruction::Construct()
{
    G4bool checkOverlaps = true;

    G4double xWorld = 1. * m;
    G4double yWorld = 1. * m;
    G4double zWorld = 1. * m;

    G4double xRad = 0.5 * m;
    G4double yRad = 0.5 * m;
    G4double zRad = 0.02 * m;

    // Defining materials
    G4NistManager *nist  = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* SiO2 = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");

    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);

    G4Box *solidRad = new G4Box("solidRad", 0.5 * xRad, 0.5 * yRad, 0.5 * zRad);
    logicRad = new G4LogicalVolume(solidRad, SiO2, "logicRad");
    G4VPhysicalVolume *physRad = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicRad, "physRad", logicWorld, false, 0, checkOverlaps);

    return physWorld;
}

void PMDetectorConstruction::ConstructSDandField()
{
    PMSensitiveDetector *sensDet = new PMSensitiveDetector("SensitveDetector");
    logicRad->SetSensitiveDetector(sensDet);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}