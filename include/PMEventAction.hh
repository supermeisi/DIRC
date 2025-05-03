#ifndef EVENT_HH
#define EVENT_HH

#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4UserEventAction.hh"
#include "G4RunManager.hh"

#include "PMRunAction.hh"
#include "PMEventAction.hh"

class PMEventAction : public G4UserEventAction
{
  public:
    PMEventAction(PMRunAction *);
    ~PMEventAction();

    virtual void BeginOfEventAction(const G4Event *);
    virtual void EndOfEventAction(const G4Event *);
};

#endif