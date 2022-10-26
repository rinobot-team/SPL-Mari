#ifndef RINO_PLAYER_H
#define RINO_PLAYER_H

#include "Role.h"

using namespace std;

class TraineeRole1: public Role {

private:
    bool onStart;
    int variavelQualquer;
public:

    TraineeRole1(SpellBook *spellBook);
    ~TraineeRole1();
    void Tick(float ellapsedTime, const SensorValues&);

};
#endif
