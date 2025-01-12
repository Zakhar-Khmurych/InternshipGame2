#pragma once
#include "../Content/Grid.h"
#include "../Content/Session.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <condition_variable>


class GameHandler {
public:
    std::unique_ptr<Grid> _grid;
    std::unique_ptr<Player> p1;
    std::unique_ptr<Player> p2;
    std::unique_ptr<Session> current_session;

    GameHandler()
    {
        _grid = std::make_unique<Grid>(10, 10);
        p1 = std::make_unique<Player>("player 1");
        p2 = std::make_unique<Player>("player 2");
        current_session = std::make_unique<Session>(*p1, *p2, *_grid);

        current_session->StartSession();
        //current_session->PlayRound();
    }
    Grid* GetGrid() const {
        return _grid.get();
    }

};


