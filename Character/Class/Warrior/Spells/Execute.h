#ifndef EXECUTE_H
#define EXECUTE_H

#include "Spell.h"

class Execute: public Spell {
public:
    Execute(Engine* engine, Character* pchar, CombatRoll* roll) :
        Spell("Execute", engine, pchar, roll, 0, 10) {}

    int spell_effect(const int) const override;
protected:
private:
};

#endif // EXECUTE_H