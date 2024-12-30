#pragma once
#include <iostream>
#include "Dice.h"
#include "Player.h"
#include <string>

class Player;
class Creature;



class Creature {
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
    int ID;

    Player* Owner;
    std::string TextureName;

    virtual ~Creature() = default;

     virtual void Punch(Creature& target) {
        int attack_value = Attack + Dice(20).Roll(); // ��������� �������� + �20
        if (attack_value > target.Defence) {
            target.HP -= (Damage + Dice(DamageDiceSize).Roll()); // �����, ��������� + ���
        }
    }

     virtual void RollInitiative() {
        Initiative = InitiativeModifier + Dice(20).Roll();
    }

     virtual  int ResolveInitiative() {
        RelativeInitiative = Dice(100).Roll();
        return RelativeInitiative;
    }
};
