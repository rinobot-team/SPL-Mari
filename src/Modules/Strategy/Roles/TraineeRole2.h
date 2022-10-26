#ifndef RINO_PLAYER2_H
#define RINO_PLAYER2_H

#include "Role.h"

using namespace std;

class TraineeRole2: public Role {

private:
    bool onStart;
    int variavelQualquer;
public:

    TraineeRole2(SpellBook *spellBook);
    ~TraineeRole2();
    void Tick(float ellapsedTime, const SensorValues&);

};
#endif
