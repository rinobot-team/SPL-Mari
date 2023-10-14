#ifndef RINO_PLAYER_H
#define RINO_PLAYER_H

#include "Role.h"

using namespace std;

class RinoPlayer: public Role {

private:
    bool onStart;
    int wait;
    int searchState;
    bool lookingDown, turningLeft, turningRight, goingForward;
public:

    RinoPlayer(SpellBook *spellBook);
    ~RinoPlayer();
    void Tick(float ellapsedTime, const SensorValues&);

};
#endif
