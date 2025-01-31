#pragma once
#include <vector>
#include <string>
#include <iostream>

class Grid;  

class Player {
public:
    std::string Name;
    int Coins = 0;
    long NecromancerID;
   std::vector<long> ActiveCreaturesByID;



    Player(const std::string& name) : Name(name) {}

    void GiveCoin(int reward) {
        Coins += reward;
        std::cout << Name << " coins " << Coins << std::endl;
    }

    int FibonacciCost() const;

   // template <typename T>
   // void SummonCreature(Grid& grid, const std::string& type, int x, int y);
};





