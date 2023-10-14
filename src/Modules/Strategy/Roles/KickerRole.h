#ifndef _ROLES_KICKER_H_
#define _ROLES_KICKER_H_

#include "Role.h"

using namespace std;

class KickerRole : public Role
{
private:
    bool onStart;
    int wait;
    int searchState;
    bool lookingDown, turningLeft, turningRight, goingForward;
public:
    KickerRole(SpellBook *spellBook);
    void Tick(float ellapsedTime, const SensorValues &sensor);
    virtual ~KickerRole();
};

#endif