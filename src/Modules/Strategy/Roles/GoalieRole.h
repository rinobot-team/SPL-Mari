#ifndef _ROLES_GOALIE_H_
#define _ROLES_GOALIE_H_

#include "Role.h"

using namespace std;

class GoalieRole : public Role
{
    private:
        bool onGoal;
    public:
        GoalieRole(SpellBook *spellBook);
        void Tick(float ellapsedTime, const SensorValues &sensor);
        ~GoalieRole();
};

#endif