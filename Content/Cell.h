#pragma once
#include "ICreature.h"

class ICreature;

class Cell {
public:
    ICreature* CellTaker = nullptr;

    Cell() : CellTaker(nullptr) {}

    bool IsEmpty() const {
        return CellTaker == nullptr;
    }

    void RemoveCreature() {
        CellTaker = nullptr;
    }
};