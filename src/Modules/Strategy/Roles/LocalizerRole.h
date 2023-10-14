#ifndef _ROLES_LOCALIZER_H_
#define _ROLES_LOCALIZER_H_

#include "Role.h"

using namespace std;

class LocalizerRole : public Role
{
    private:
        bool onStart;
        int wait;
        int searchState;
        bool lookingDown, turningLeft, turningRight, goingForward;
    public:
        LocalizerRole(SpellBook *spellBook);
        void Tick(float ellapsedTime, const SensorValues &sensor);
        virtual ~LocalizerRole();
};

#endif