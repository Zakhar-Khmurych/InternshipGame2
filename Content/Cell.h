#pragma once
#include <optional>
#include <functional>

class Creature;

class Cell {
public:
    std::optional<std::reference_wrapper<Creature>> CellTaker;

    Cell() = default;

    bool IsEmpty() const {
        return !CellTaker.has_value();
    }

    void PlaceCreature(Creature& creature) {
        CellTaker = creature;
    }

    void RemoveCreature() {
        CellTaker.reset();
    }
};

