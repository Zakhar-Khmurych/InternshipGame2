#pragma once
#include <ctime>
#include <cstdlib>


class Dice {
public:
    Dice(int size) : size(size) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    int Roll() const {
        return (std::rand() % size) + 1;
    }

private:
    int size;
};


