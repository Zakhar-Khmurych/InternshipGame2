#include "Player.h"
#include "Grid.h" 

int Player::FibonacciCost() const {
    std::vector<int> fib = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };
    size_t count = ActiveCreaturesByID.size();
    return count < fib.size() ? fib[count] : fib.back();
}

template <typename T>
void Player::SummonCreature(Grid& grid) {
    auto freeCells = grid.DijkstraXY(0, 0, 1);  // Тепер компілятор бачить DijkstraXY
    if (!freeCells.empty() && Coins >= FibonacciCost()) {
        T* creature = new T();
        Coins -= creature->Cost * FibonacciCost();
        ActiveCreaturesByID.push_back(creature->ID);
        freeCells[0]->PlaceCreature(*creature);
        std::cout << "Summoned creature at (0, 0)\n";
    }
}

template void Player::SummonCreature<Creature>(Grid& grid);