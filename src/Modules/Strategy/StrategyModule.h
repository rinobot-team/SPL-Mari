#ifndef _StrategyModule_H_
#define _StrategyModule_H_

#include "Core/Module.h"
#include <vector>
#include <string>
#include <map>

#include "motion/touch/AgentTouch.hpp"
#include "GameController/GameController.h"
#include "Safety/SafetyMonitor.h"

#include "Control/PControl.h"
#include "Control/PotentialFields.h"
#include "Control/HeadController.h"

#include "Trackers/BallTracker.h"
#include "Trackers/RobotTracker.h"
#include "Trackers/FeatureTracker.h"

#include "Roles/TraineeRole1.h"
#include "Roles/TraineeRole2.h"

using namespace std;

class StrategyModule : public Module
{
    private:
        GameController *gameController;
        SafetyMonitor *safetyMonitor;

        PotentialFields *potentialFields;
        PControl *pControl;

        HeadController *headController;

        BallTracker *ballTracker;
        RobotTracker *robotTracker;
        FeatureTracker *featureTracker;

        // Roles
        TraineeRole1 *trainee1;
        TraineeRole2 *trainee2;


        int squareStep;
        float squareX, squareY;
        float squareL;
        float squareTimer;
        float circleRadius;
    public:
        StrategyModule(SpellBook *spellBook);
        ~StrategyModule();
        void Tick(float ellapsedTime);
        void OnStart();
        void OnStop();
        void Load();
        void Save();
};

#endif