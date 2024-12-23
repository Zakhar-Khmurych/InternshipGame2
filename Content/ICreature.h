#pragma once
#include <iostream>
#include "Dice.h"
#include "Player.h"
#include <string>

class Player;
class Creature;

class ICreature {
public:
    virtual ~ICreature() = default;
};



class Creature : public ICreature {
public:
    int HP;
    int CurrentHP;
    int Movement;
    int MovementRemaining;
    int Defence;
    bool StillCanAttack;
    int Attack;
    int Damage;
    int DamageDiceSize;
    int InitiativeModifier;
    int Initiative;
    int RelativeInitiative;
    int Cost;

    Player* Owner;
    std::string TextureAddress;

    void Punch(Creature& target) {
        int attack_value = Attack + Dice(20).Roll(); // фіксоване влучання + к20
        if (attack_value > target.Defence) {
            target.HP -= (Damage + Dice(DamageDiceSize).Roll()); // шкода, фіксована + куб
        }
    }

    void RollInitiative() {
        Initiative = InitiativeModifier + Dice(20).Roll();
    }

    int ResolveInitiative() {
        RelativeInitiative = Dice(100).Roll();
        return RelativeInitiative;
    }
};
