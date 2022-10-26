#include "TraineeRole2.h"
#include "Core/Utils/Math.h"
#include "Core/Utils/RelativeCoord.h"
#include "Core/Utils/RobotDefs.h"
#include "Core/Utils/CartesianCoord.h"

TraineeRole2::TraineeRole2(SpellBook *spellBook) : Role(spellBook)
{
    onStart = false;
}
TraineeRole2::~TraineeRole2()
{
}
void TraineeRole2::Tick(float ellapsedTime, const SensorValues &sensor)
{
    spellBook->strategy.MoveHead = false;
    spellBook->motion.HeadYaw = 0;
    spellBook->motion.HeadSpeedYaw = 0.2f;
    spellBook->motion.HeadSpeedPitch = 0.2f;

    if ((spellBook->strategy.GameState == STATE_READY || spellBook->strategy.GameState == STATE_PLAYING) && !onStart)
    {
        if (spellBook->perception.vision.localization.Enabled)
        {
            spellBook->strategy.WalkForward = true;
            spellBook->strategy.TargetX = -1.0f;
            spellBook->strategy.TargetY = 0.0f;
            spellBook->strategy.TargetTheta = 0;

            CartesianCoord current(spellBook->perception.vision.localization.X, spellBook->perception.vision.localization.Y);
            CartesianCoord desired(spellBook->strategy.TargetX, spellBook->strategy.TargetY);
            if (current.distance(desired) < 0.2f)
            {
                spellBook->strategy.WalkForward = false;
                onStart = true;
            }
        }
        else
        {
            onStart = true;
        }
    }
    if (spellBook->strategy.GameState == STATE_PLAYING && onStart)
    {
        cout << "na role trainee2, " << endl;
        spellBook->motion.Vth = Deg2Rad(0); // SETA A VELOCIDADE ANGULAR PARA 0 GRAUS
        spellBook->motion.Vx = 0; // SETA A VELOCIDADE LINEAR PARA 0 m/s (NAO COLOQUE MAIS QUE 0.2m/s!!!)
        spellBook->motion.HeadPitch = Deg2Rad(0.0f); // ANGULACAO DA CABECA DO ROBO, POSITIVO O ROBO OLHA PRA BAIXO, NEGATIVO PRA CIMA

        // informacoes disponiveis:
            // spellBook->perception.vision.ball.BallDetected // SE ESTA VENDO A BOLA
            // spellBook->perception.vision.ball.BallDistance // DISTANCIA ATE A BOLA em metros
            // spellBook->perception.vision.ball.BallYaw > Deg2Rad(10.0f) // ANGULACAO DA BOLA EM X
            // spellBook->motion.HeadPitch = Deg2Rad(24.0f); // OLHA PRA BAIXO
    }
}
