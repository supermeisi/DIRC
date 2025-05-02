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
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *SiO2 = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");

    const G4int NUMENTRIES = 100;
    G4double photonEnergy[NUMENTRIES];
    G4double refractiveIndex[NUMENTRIES];
    G4double refractiveIndexWorld[NUMENTRIES];
    G4double reflectivity[NUMENTRIES];

    // Photon energy range: 200 nm (6.2 eV) to 900 nm (1.38 eV)
    G4double lambdaMin = 0.8; // microns
    G4double lambdaMax = 0.9; // microns

    for (int i = 0; i < NUMENTRIES; i++)
    {
        // Linearly spaced wavelength in microns
        G4double lambda = lambdaMin + (lambdaMax - lambdaMin) * (NUMENTRIES - i) / (NUMENTRIES - 1);

        // Convert wavelength to energy
        G4double energy = (1.2498 / lambda) * eV; // E[eV] = 1240 / λ[nm]
        photonEnergy[i] = energy;

        G4cout << energy << G4endl;

        // Sellmeier coefficients
        G4double B1 = 0.6961663;
        G4double B2 = 0.4079426;
        G4double B3 = 0.8974794;
        G4double C1 = 0.0684043 * 0.0684043;
        G4double C2 = 0.1162414 * 0.1162414;
        G4double C3 = 9.896161 * 9.896161;

        // Calculate refractive index
        G4double lambda2 = lambda * lambda;
        G4double n2 = 1 + (B1 * lambda2) / (lambda2 - C1) + (B2 * lambda2) / (lambda2 - C2) + (B3 * lambda2) / (lambda2 - C3);
        refractiveIndex[i] = std::sqrt(n2);
        refractiveIndexWorld[i] = 1.0;

        reflectivity[i] = 0.;
    }

    // Add to material properties tables
    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptSiO2 = new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptAbsorber = new G4MaterialPropertiesTable();

    G4OpticalSurface *absorberSurface = new G4OpticalSurface("lg_absorber");

    mptWorld->AddProperty("RINDEX", photonEnergy, refractiveIndexWorld, NUMENTRIES);
    mptSiO2->AddProperty("RINDEX", photonEnergy, refractiveIndex, NUMENTRIES);
    mptAbsorber->AddProperty("REFLECTIVITY", photonEnergy, reflectivity, NUMENTRIES);

    worldMat->SetMaterialPropertiesTable(mptWorld);
    SiO2->SetMaterialPropertiesTable(mptSiO2);

    absorberSurface->SetMaterialPropertiesTable(mptAbsorber);

    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);

    G4Box *solidRad = new G4Box("solidRad", 0.5 * xRad, 0.5 * yRad, 0.5 * zRad);
    logicRad = new G4LogicalVolume(solidRad, SiO2, "logicRad");
    G4VPhysicalVolume *physRad = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicRad, "physRad", logicWorld, false, 0, checkOverlaps);

    // Mirror surface
    G4LogicalBorderSurface *surfaceAbsorber = new G4LogicalBorderSurface("MirrorSurface", physRad, physWorld, absorberSurface);
    G4LogicalBorderSurface *surfaceAbsorber2 = new G4LogicalBorderSurface("MirrorSurface2", physWorld, physRad, absorberSurface);

    return physWorld;
}

void PMDetectorConstruction::ConstructSDandField()
{
    PMSensitiveDetector *sensDet = new PMSensitiveDetector("SensitveDetector");
    logicRad->SetSensitiveDetector(sensDet);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}
