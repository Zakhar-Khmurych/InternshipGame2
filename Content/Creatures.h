#pragma once
#include "Creature.h"

class Creatures
{
};

class Necromancer : public Creature {
public:
    Necromancer(Player* owner) : Creature("necromancer", owner)
    {
        HP = 10;
        Movement = 6;
        Defence = 14;
        Attack = 4;
        Damage = 2;
        DamageDiceSize = 6;
        InitiativeModifier = 2;
        Cost = 1;
        TextureName = TypeName;
    }

    static inline const std::string TypeName = "necromancer";
};

class Skeleton : public Creature {
public:
    Skeleton(Player* owner) : Creature("skeleton", owner)
    {
        HP = 4;
        Movement = 4;
        Defence = 8;
        Attack = 0;
        Damage = 0;
        DamageDiceSize = 6;
        InitiativeModifier = 0;
        Cost = 0;
        TextureName = TypeName;
    }

    static inline const std::string TypeName = "skeleton";
};

class Knight : public Creature {
public:
    Knight(Player* owner) : Creature("knight", owner)
    {
        HP = 12;
        Movement = 4;
        Defence = 16;
        Attack = 6;
        Damage = 3;
        DamageDiceSize = 8;
        InitiativeModifier = 0;
        Cost = 1;
        TextureName = TypeName;
    }
    static inline const std::string TypeName = "knight";
};

class Berserker : public Creature {
public:
    Berserker(Player* owner)
        : Creature("berserker", owner)
    {
        HP = 16;
        Movement = 6;
        Defence = 12;
        Attack = 7;
        Damage = 4;
        DamageDiceSize = 12;
        InitiativeModifier = 2;
        Cost = 1;
        TextureName = TypeName;
    }
    static inline const std::string TypeName = "berserker";
};

class Assassin : public Creature {
public:
    Assassin(Player* owner)
        : Creature("assassin", owner)
    {
        HP = 8;
        Movement = 6;
        Defence = 8;
        Attack = 2;
        Damage = 2;
        DamageDiceSize = 24;
        InitiativeModifier = 4;
        Cost = 1;
        TextureName = TypeName;
    }
    static inline const std::string TypeName = "assassin";
};

class Elf : public Creature {
public:
    Elf(Player* owner)
        : Creature("elf", owner)
    {
        HP = 8;
        Movement = 8;
        Defence = 12;
        Attack = 4;
        Damage = 2;
        DamageDiceSize = 8;
        InitiativeModifier = 4;
        Cost = 1;
        TextureName = TypeName;
    }
    static inline const std::string TypeName = "elf";
};

class Goblin : public Creature {
public:
    Goblin(Player* owner)
        : Creature("goblin", owner)
    {
        HP = 4;
        Movement = 6;
        Defence = 12;
        Attack = 3;
        Damage = 1;
        DamageDiceSize = 4;
        InitiativeModifier = 8;
        Cost = 1;
        TextureName = TypeName;
    }
    static inline const std::string TypeName = "goblin";
};

class Wall : public Creature {
public:
    Wall(Player* owner)
        : Creature("wall", owner)
    {
        HP = 1;
        Movement = 0;
        Defence = 40;
        Attack = 0;
        Damage = 0;
        DamageDiceSize = 1;
        InitiativeModifier = 0;
        Cost = 0;
        TextureName = TypeName;
    }
    static inline const std::string TypeName = "wall";
};


class CreatureFactory {
public:


    static std::shared_ptr<Creature> CreateCreature(const std::string& type, Player* owner) {
        if (type == "necromancer") {
            return std::make_shared<Necromancer>(owner);
        }
        if (type == "skeleton") {
            return std::make_shared<Skeleton>(owner);
        }
        if (type == "knight") {
            return std::make_shared<Knight>(owner);
        }
        if (type == "berserker") {
            return std::make_shared<Berserker>(owner);
        }
        if (type == "assassin") {
            return std::make_shared<Assassin>(owner);
        }
        if (type == "elf") {
            return std::make_shared<Elf>(owner);
        }
        if (type == "goblin") {
            return std::make_shared<Goblin>(owner);
        }
        if (type == "wall") {
            return std::make_shared<Wall>(owner);
        }
        return nullptr;
    }
};