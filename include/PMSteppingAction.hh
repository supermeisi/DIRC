#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4ThreeVector.hh"
#include "G4AnalysisManager.hh"

#include "PMEventAction.hh"

class PMSteppingAction : public G4UserSteppingAction
{
public:
    PMSteppingAction(PMEventAction* ) : G4UserSteppingAction(), outputFile("CherenkovAngles.txt")
    {
    }

    virtual ~PMSteppingAction()
    {
    }

    virtual void UserSteppingAction(const G4Step *step) override;

private:
    std::ofstream outputFile;
};
