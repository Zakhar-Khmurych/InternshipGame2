#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "Player.h"
#include "Creature.h"
#include "Creatures.h"

class Cell {
public:
    std::shared_ptr<Creature> CellTaker;

    Cell() = default;

    bool IsEmpty() const {
        return !CellTaker;
    }

    void PlaceCreature(const std::string& type, Player* owner) {
        CellTaker = CreatureFactory::CreateCreature(type, owner);  // Виклик фабричного методу
    }

    void RemoveCreature() {
        CellTaker.reset();
    }

    void PrintCellTaker() const {
        if (CellTaker) {
            std::cout << CellTaker->GetTextureName() << "\n";
        }
        else {
            std::cout << "empty\n";
        }
    }
};
