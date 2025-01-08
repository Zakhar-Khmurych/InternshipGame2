#include "Player.h"
#include "Grid.h" 
#include "Creatures.h" 


int Player::FibonacciCost() const {
    std::vector<int> fib = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };
    size_t count = ActiveCreaturesByID.size();
    return count < fib.size() ? fib[count] : fib.back();
}
/*
std::unique_ptr<Creature> CreateCreature(const std::string& type, Player* owner) {
    if (type == "necromancer") return std::make_unique<Necromancer>(owner);
    if (type == "skeleton") return std::make_unique<Skeleton>(owner);
    if (type == "knight") return std::make_unique<Knight>(owner);
    if (type == "berserker") return std::make_unique<Berserker>(owner);
    if (type == "assassin") return std::make_unique<Assassin>(owner);
    if (type == "elf") return std::make_unique<Elf>(owner);
    if (type == "goblin") return std::make_unique<Goblin>(owner);
    if (type == "wall") return std::make_unique<Wall>(owner);
    return std::make_unique<Creature>("unnamed", owner);
}
*/

/*
template <typename T>
void Player::SummonCreature(Grid& grid, const std::string& type, int x, int y) {
    auto freeCells = grid.DijkstraXY(0, 0, 1);
    if (!freeCells.empty() && Coins >= FibonacciCost()) {
        auto creature = CreateCreature(T::TypeName, this);
        Coins -= creature->Cost * FibonacciCost();
        ActiveCreaturesByID.push_back(creature->ID);
        freeCells[0]->PlaceCreature(*creature);
       // std::cout << "Summoned creature " << creature.TextureName << " at (0, 0)\n";
        std::cout << "Summoned " << creature->GetTextureName() << " at (0, 0)\n";
    }
}
*/

//template void Player::SummonCreature<Creature>(Grid& grid, const std::string& type, int x, int y);