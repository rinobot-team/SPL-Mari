#ifndef BALL_HOLDER_H
#define BALL_HOLDER_H

#include "Role.h"

using namespace std;

class BallHolder: public Role {

private:
        bool onStart;
        int wait;
        int searchState;
        bool lookingDown, turningLeft, turningRight, goingForward;
public:
    BallHolder(SpellBook *spellBook);
    ~BallHolder();
    void Tick(float ellapsedTime, const SensorValues&);
};
#endif