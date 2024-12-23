#pragma once
#include <vector>
#include <string>
#include "Grid.h" 

class Player {

};

/*
class Player {
public:
    std::string Name;
    int Coins = 0;
    long NecromancerID;
    std::vector<long> ActiveCreaturesByID;

    Player(const std::string& name) : Name(name) {}

    void GiveCoin(int reward) {
        Coins += reward;
    }

    int FibonacciCost() const {
        std::vector<int> fib = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };
        size_t count = ActiveCreaturesByID.size();
        return count < fib.size() ? fib[count] : fib.back();
    }

    template <typename T>
    void SummonCreature(Grid& grid) {
        auto freeCells = grid.DijkstraXY(0, 0, 1);
        if (!freeCells.empty() && Coins >= FibonacciCost()) {
            T* creature = new T();
            Coins -= creature->Cost * FibonacciCost();
            ActiveCreaturesByID.push_back(creature->ID);
            freeCells[0]->CellTaker = creature;
            std::cout << "Summoned creature at (0, 0)\n";
        }
    }
};

*/