#include "PControl.h"
#include "Core/Utils/Math.h"

PControl::PControl(SpellBook *spellBook)
    :   InnerModule(spellBook)
{
    kp = 2.0f/11.0f;
    ka = 345.0f/823.0f;
    kb = -kp;
    Vmax = 0.3f;
}

PControl::~PControl()
{
    
}

void PControl::Tick(float ellapsedTime)
{
    if(spellBook->strategy.WalkForward || spellBook->strategy.WalkAside)
    {
        Xo(0) = spellBook->strategy.TargetX;
        Xo(1) = spellBook->strategy.TargetY;
        Xo(2) = spellBook->strategy.TargetTheta;

        if(spellBook->perception.vision.localization.Enabled)
        {
            Xr(0) = spellBook->perception.vision.localization.X;
            Xr(1) = spellBook->perception.vision.localization.Y;
            Xr(2) = spellBook->perception.vision.localization.Theta;
        }
        else
        {
            Xr(0) = 0;
            Xr(1) = 0;
            Xr(2) = 0;
        }

        float g = FixAngle(atan2(Xo(1), Xo(0)));
        float a = FixAngle(g - Xr(2));
        float b = FixAngle(Xo(1) - g);

        

        F = (Xo - Xr);
        v = min(F.norm()*kp, Vmax);
        w = ka*a + kb*b;

        if(spellBook->strategy.WalkForward)
            spellBook->motion.Vx = v;
        else
            spellBook->motion.Vy = v;
        spellBook->motion.Vth = w;
    }
    else
    {
        spellBook->motion.Vx = 0;
        spellBook->motion.Vy = 0;
        spellBook->motion.Vth = 0;
    }
}