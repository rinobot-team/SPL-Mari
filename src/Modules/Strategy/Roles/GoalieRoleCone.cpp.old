#include "GoalieRole.h"
#include "Core/Utils/Math.h"
#include "Core/Utils/RelativeCoord.h"
#include "Core/Utils/CartesianCoord.h"

// Variavel para armazenar distancia antiga da bola
int PastBallDistance = 0;

GoalieRole::GoalieRole(SpellBook *spellBook)
    : Role(spellBook)
{
    onGoal = false;
}

GoalieRole::~GoalieRole()
{

}

void GoalieRole::Tick(float ellapsedTime, const SensorValues &sensor)
{
    spellBook->strategy.MoveHead = false;
    spellBook->motion.HeadYaw = 0;
    spellBook->motion.HeadSpeedYaw = 0.2f;
    spellBook->motion.HeadSpeedPitch = 0.2f;
    
    if((spellBook->strategy.GameState == STATE_READY || spellBook->strategy.GameState == STATE_PLAYING) &&
        !onGoal)
    {
        if(spellBook->perception.vision.localization.Enabled)
        {
            spellBook->strategy.WalkForward = true;
            spellBook->strategy.TargetX = 0.0f;
            spellBook->strategy.TargetY = 0.0f;
            spellBook->strategy.TargetTheta = 0;

            CartesianCoord current(spellBook->perception.vision.localization.X, spellBook->perception.vision.localization.Y); 
            CartesianCoord desired(spellBook->strategy.TargetX, spellBook->strategy.TargetY); 
            if(current.distance(desired)  < 0.2f)
            {
                spellBook->strategy.WalkForward = false;
                onGoal = true;
            }
        }
        else
        {
            onGoal = true;
        }
    }
    if(spellBook->strategy.GameState == STATE_PLAYING && onGoal)
    {
        //spellBook->motion.HeadPitch = Deg2Rad(12.0f) + Deg2Rad(12.0f) * sin( (spellBook->perception.vision.ball.BallLostCount * 0.05f) * PI );                
        //spellBook->motion.HeadPitch = Deg2Rad(12.0f) + Deg2Rad(12.0f) * PI;                
        if(!Kicking())
        {
            spellBook->motion.Vx = 0;
            if(spellBook->perception.vision.ball.BallLostCount < 5)
            {
                if(spellBook->perception.vision.ball.BallDistance < 0.45f)
                    spellBook->motion.HeadPitch = Deg2Rad(24.0f);
                else if(spellBook->perception.vision.ball.BallDistance > 0.5f)
                    spellBook->motion.HeadPitch = Deg2Rad(0.0f);

                // if(abs(spellBook->perception.vision.ball.BallYaw) > Deg2Rad(5.0f))
                // {
                //     //spellBook->motion.Vy = 0.1f * -SIG(spellBook->perception.vision.ball.BallYaw);
                //     //spellBook->motion.DefenderCentre = false;
                //     CancelKick();
                // }
                // else
                {
                    spellBook->motion.Vy = 0.0f;
                    if(spellBook->perception.vision.ball.BallDistance < 1.0f)
                    {   
                        // Verifica se a velocidade da bola e alta
                        if(((spellBook->perception.vision.ball.BallDistance - PastBallDistance) > 0.1f) && (PastBallDistance != 0))
                        {
                            CancelKick();
                            //spellBook->motion.DefenderCentre = true;
                        }
                        else
                        {       
                            //A partir daqui é a parte original do codigo
                            if(spellBook->perception.vision.ball.BallDistance < 0.4f)
                            {
                                //spellBook->motion.DefenderCentre = false;
                                //PrepareKick(spellBook->perception.vision.ball.BallYaw);
                            }
                            else
                            {
                                CancelKick();
                                //spellBook->motion.DefenderCentre = true;
                            }
                        }
                        
                    }
                    else
                    {
                        //spellBook->motion.DefenderCentre = false;
                        CancelKick();
                    }
                }
            }
            else
            {
                CancelKick();
                if(spellBook->perception.vision.localization.Enabled)
                    spellBook->strategy.WalkAside = false;
                else
                    spellBook->motion.Vy = 0.0f;
                spellBook->motion.DefenderCentre = false;

                spellBook->motion.HeadPitch = Deg2Rad(12.0f) + Deg2Rad(12.0f) * sin( (spellBook->perception.vision.ball.BallLostCount * 0.05f) * PI );                
            }
        }
    }
}
        //PastBallDistance = spellBook->perception.vision.ball.BallDistance;
    
