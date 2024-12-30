#pragma once
#include "Creature.h"

class Creatures
{
};

class Necromancer : public Creature {
public:
    Necromancer() {
        HP = 10;
        Movement = 6;
        Defence = 14;
        Attack = 4;
        Damage = 2;
        DamageDiceSize = 6;
        InitiativeModifier = 2;
        Cost = 1;
        TextureName = "necromancer";
    }
};

class Skeleton : public Creature {
public:
    Skeleton() {
        HP = 4;
        Movement = 4;
        Defence = 8;
        Attack = 0;
        Damage = 0;
        DamageDiceSize = 6;
        InitiativeModifier = 0;
        Cost = 0;
        TextureName = "skeleton";
    }
};

class Knight : public Creature {
public:
    Knight() {
        HP = 12;
        Movement = 4;
        Defence = 16;
        Attack = 6;
        Damage = 3;
        DamageDiceSize = 8;
        InitiativeModifier = 0;
        Cost = 1;
        TextureName = "knight";
    }
};

class Berserker : public Creature {
public:
    Berserker() {
        HP = 16;
        Movement = 6;
        Defence = 12;
        Attack = 7;
        Damage = 4;
        DamageDiceSize = 12;
        InitiativeModifier = 2;
        Cost = 1;
        TextureName = "berserker";
    }
};

class Assassin : public Creature {
public:
    Assassin() {
        HP = 8;
        Movement = 6;
        Defence = 8;
        Attack = 2;
        Damage = 2;
        DamageDiceSize = 24;
        InitiativeModifier = 4;
        Cost = 1;
        TextureName = "assassin";
    }
};

class Elf : public Creature {
public:
    Elf() {
        HP = 8;
        Movement = 8;
        Defence = 12;
        Attack = 4;
        Damage = 2;
        DamageDiceSize = 8;
        InitiativeModifier = 4;
        Cost = 1;
        TextureName = "elf";
    }
};

class Goblin : public Creature {
public:
    Goblin() {
        HP = 4;
        Movement = 6;
        Defence = 12;
        Attack = 3;
        Damage = 1;
        DamageDiceSize = 4;
        InitiativeModifier = 8;
        Cost = 1;
        TextureName = "goblin";
    }
};

class Wall : public Creature {
public:
    Wall() {
        HP = 1;
        Movement = 0;
        Defence = 40;
        Attack = 0;
        Damage = 0;
        DamageDiceSize = 1;
        InitiativeModifier = 0;
        Cost = 0;
        TextureName = "wall";
    }
};
