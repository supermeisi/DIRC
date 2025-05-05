#include "PMSteppingAction.hh"

void PMSteppingAction::UserSteppingAction(const G4Step *step)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4Track *track = step->GetTrack();

    // G4cout << "Photon" << G4endl;

    // Ensure this is the first step
    // if (track->GetCurrentStepNumber() == 1)
    // Get the direction of the photon
    G4ThreeVector photonDirection = track->GetMomentumDirection();

    // Calculate the angle between the photon and the primary particle
    G4double theta = photonDirection.getTheta();
    G4double phi = photonDirection.getPhi();

    G4double thetaDeg = theta * 180.0 / CLHEP::pi;
    G4double phiDeg = phi * 180.0 / CLHEP::pi;

    if (theta == 0)
        return;

    if (track->GetTrackID() == 1)
        man->FillH1(1, theta);

    if (track->GetParentID() != 1)
        return;

    // G4cout << theta << G4endl;

    if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
        man->FillH1(0, theta);
}