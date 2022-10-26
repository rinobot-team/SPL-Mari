#include "StrategyModule.h"
#include <boost/bind.hpp>
#include "Core/InitManager.h"
#include "Core/Utils/Math.h"

StrategyModule::StrategyModule(SpellBook *spellBook)
    : Module(spellBook, "Strategy", 30)
{
    gameController = new GameController(this->spellBook);
    safetyMonitor = new SafetyMonitor(this->spellBook);

    potentialFields = new PotentialFields(this->spellBook);
    pControl = new PControl(this->spellBook);

    headController = new HeadController(this->spellBook);

    ballTracker = new BallTracker(this->spellBook);
    robotTracker = new RobotTracker(this->spellBook);
    featureTracker = new FeatureTracker(this->spellBook);

    squareStep = 1;
    squareX = squareY = 0;
    squareL = 2.0f;
    squareTimer = 0;
    circleRadius = 2.0f;

    trainee1 = new TraineeRole1(this->spellBook);
    trainee2 = new TraineeRole2(this->spellBook);
}

StrategyModule::~StrategyModule()
{
    delete gameController;
    delete safetyMonitor;

    delete potentialFields;
    delete pControl;

    delete headController;

    delete ballTracker;
    delete robotTracker;
    delete featureTracker;

    delete trainee1;
    delete trainee2;
}

void StrategyModule::OnStart()
{
    gameController->OnStart();
    safetyMonitor->OnStart();

    potentialFields->OnStart();
    pControl->OnStart();

    headController->OnStart();

    ballTracker->OnStart();
    robotTracker->OnStart();
    featureTracker->OnStart();

    trainee1->OnStart();
    trainee2->OnStart();
}

void StrategyModule::OnStop()
{
    gameController->OnStop();
    safetyMonitor->OnStop();

    potentialFields->OnStop();
    pControl->OnStop();

    headController->OnStop();

    ballTracker->OnStop();
    robotTracker->OnStop();
    featureTracker->OnStop();

    trainee1->OnStop();
    trainee2->OnStop();
}

void StrategyModule::Load()
{
    LOAD(motion)
    LOAD(perception)
    LOAD(strategy)
    LOAD(behaviour)
    LOAD(network)
}

void StrategyModule::Save()
{
    SAVE(motion)
    SAVE(perception)
    SAVE(strategy)
    SAVE(behaviour)
}

void StrategyModule::Tick(float ellapsedTime)
{
    Blackboard *blackboard = InitManager::GetBlackboard();
    const SensorValues &sensor = readFrom(motion, sensors);

    safetyMonitor->Tick(ellapsedTime, sensor);
    gameController->Tick(ellapsedTime, sensor);

    spellBook->motion.Dead = spellBook->strategy.Die;
    if (spellBook->strategy.Die)
    {
        return;
    }

    if (spellBook->motion.Calibrate)
    {
        spellBook->motion.Stiff = true;
        spellBook->motion.Stand = true;
        spellBook->motion.Walk = false;
        cout << endl
             << endl
             << "Calibrate" << endl;
        cout << "gyrXOffset=" << spellBook->motion.GyroX << endl;
        cout << "gyrYOffset=" << spellBook->motion.GyroY << endl;
        cout << "angleXOffset=" << spellBook->motion.AngleX << endl;
        cout << "angleYOffset=" << spellBook->motion.AngleY << endl;
        cout << "# Save this to /home/nao/data/configs/robotName.cfg" << endl;
        cout << endl
             << endl;
        return;
    }

    if (!spellBook->strategy.Started)
    {
        spellBook->strategy.TimeSinceStarted = 0;
        spellBook->motion.Stiff = false;
        spellBook->motion.Stand = false;
        spellBook->motion.Walk = false;
        return;
    }
    spellBook->strategy.TimeSinceStarted += ellapsedTime;

    if (spellBook->strategy.Penalized)
    {
        spellBook->strategy.TimeSincePenalized = 0;
        spellBook->motion.Stiff = true;
        spellBook->motion.Stand = false;
        spellBook->motion.Walk = false;
        return;
    }
    spellBook->strategy.TimeSincePenalized += ellapsedTime;

    if (spellBook->strategy.GameState == STATE_READY)
    {
        spellBook->motion.Stiff = true;
        spellBook->motion.Stand = false;
        spellBook->motion.Walk = false;
        return;
    }

    if (spellBook->strategy.GameState == STATE_SET)
    {
        spellBook->strategy.MoveHead = true;
        spellBook->motion.Stiff = true;
        spellBook->motion.Stand = true;
        spellBook->motion.Walk = true;
        spellBook->motion.Vx = 0;
        spellBook->motion.Vy = 0;
        spellBook->motion.Vth = 0;
        headController->Tick(ellapsedTime, sensor);
        return;
    }

    if (spellBook->strategy.GameState == STATE_FINISHED)
    {
        spellBook->motion.Stiff = true;
        spellBook->motion.Stand = false;
        spellBook->motion.Walk = false;
        return;
    }

    spellBook->motion.TipOver = spellBook->strategy.TurnOver;
    if (spellBook->strategy.TurnOver)
    {
        return;
    }
    spellBook->motion.GetupBack = spellBook->strategy.FallenBack;
    if (spellBook->strategy.FallenBack)
    {
        return;
    }
    spellBook->motion.GetupFront = spellBook->strategy.FallenFront;
    if (spellBook->strategy.FallenFront)
    {
        return;
    }

    spellBook->motion.Stiff = true;
    spellBook->motion.Stand = true;
    spellBook->motion.Walk = true;

    // Makes the robot move some predefined paths
    if (spellBook->strategy.WalkInSquare)
    {
        if (squareStep == 0)
        {
            squareX += spellBook->motion.Vx * ellapsedTime;
            spellBook->motion.Vx = 0.3f;
            if (squareX > squareL)
            {
                squareStep = 1;
                spellBook->motion.Vx = 0;
            }
        }
        else if (squareStep == 1)
        {
            squareY += spellBook->motion.Vy * ellapsedTime;
            spellBook->motion.Vy = 0.2f;
            if (squareY > squareL)
            {
                squareStep = 2;
                spellBook->motion.Vy = 0;
            }
        }
        else if (squareStep == 2)
        {
            squareX += spellBook->motion.Vx * ellapsedTime;
            spellBook->motion.Vx = -0.3f;
            if (squareX < 0)
            {
                squareStep = 3;
                spellBook->motion.Vx = 0;
            }
        }
        else if (squareStep == 3)
        {
            squareY += spellBook->motion.Vy * ellapsedTime;
            spellBook->motion.Vy = -0.2f;
            if (squareY < 0)
            {
                squareStep = 4;
                spellBook->motion.Vy = 0;
            }
        }
        else if (squareStep == 4)
        {
            squareTimer += ellapsedTime;
            if (squareTimer > 5.0f)
            {
                squareStep = 0;
                squareTimer = 0;
            }
        }
        return;
    }
    else if (spellBook->strategy.WalkInCircle)
    {
        spellBook->motion.Vx = 0.3f;
        spellBook->motion.Vth = spellBook->motion.Vx / circleRadius;
        return;
    }

    ballTracker->Tick(ellapsedTime, sensor);
    robotTracker->Tick(ellapsedTime);
    featureTracker->Tick(ellapsedTime, sensor);

    if (spellBook->network.gameController.PenaltyPhase)
    {
        if (spellBook->behaviour.Number == 1)
            ;// goalie->Tick(ellapsedTime, sensor);
        else
            ;// kicker->Tick(ellapsedTime, sensor);
    }
    else
    {
        switch (spellBook->behaviour.Number)
        {
        case 1:
            trainee1->Tick(ellapsedTime, sensor);
            break;
        case 2:
            trainee2->Tick(ellapsedTime, sensor);
            break;
        default:
            break;
        }
    }

    //potentialFields->Tick(ellapsedTime);
    //pControl->Tick(ellapsedTime);
    headController->Tick(ellapsedTime, sensor);
}
