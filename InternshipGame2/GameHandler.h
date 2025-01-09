#pragma once
#include "../Content/Grid.h"
#include "../Content/Session.h"
#include <memory>

class GameHandler
{
public:
    std::unique_ptr<Grid> _grid;
    std::unique_ptr<Player> p1;
    std::unique_ptr<Player> p2;
    std::unique_ptr<Session> current_session;

    GameHandler() {
        _grid = std::make_unique<Grid>(10, 10);
        p1 = std::make_unique<Player>("player 1");
        p2 = std::make_unique<Player>("player 2");
        current_session = std::make_unique<Session>(*p1, *p2, *_grid);

        std::cout << "Placing necromancers..." << std::endl;
        current_session->StartSession();

        for (int x = 0; x < _grid->Width; ++x) {
            for (int y = 0; y < _grid->Height; ++y) {
                const Cell& cell = _grid->GetCell(x, y);
                if (!cell.IsEmpty()) {
                    Creature& creature = *cell.CellTaker;
                    std::cout << "Necromancer placed at (" << x << ", " << y << ") "
                        << "with texture: " << creature.TextureName << std::endl;
                }
            }
        }
    }

    Grid* GetGrid() {
        return current_session ? &current_session->SessionGrid : nullptr;
    }

    void UpdateGame() {
        if (current_session) {
            current_session->UpdateSession();
        }
    }
};

