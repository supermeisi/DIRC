#include "PMSteppingAction.hh"

void PMSteppingAction::UserSteppingAction(const G4Step *step)
{
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

    if(track->GetParentID() != 1)
        return;

    if(theta == 0)
        return;

    // G4cout << theta << G4endl;

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
        man->FillH1(0, theta);
    else
        man->FillH1(1, theta);
}