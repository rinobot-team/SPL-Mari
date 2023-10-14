#ifndef DEFENDER_ROLE_H
#define DEFENDER_ROLE_H

#include "Role.h"

using namespace std;

class DefenderRole: public Role {

private:
    bool onStart;
    int wait;
    int searchState;
    bool lookingDown, turningLeft, turningRight, goingForward;
public:
    DefenderRole(SpellBook *spellBook);
    ~DefenderRole();
    void Tick(float ellapsedTime, const SensorValues&);
};

#endif
