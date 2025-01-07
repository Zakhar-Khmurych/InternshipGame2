#pragma once
#include "Player.h"
#include "Grid.h"
#include "Creatures.h"


class Session {
public:
    Player& player1;
    Player& player2;
    Grid& SessionGrid;

    Session(Player& p1, Player& p2, Grid& session_grid)
        : player1(p1), player2(p2), SessionGrid(session_grid) {}

    void PlaceNecromancers() {
        auto necromancer1 = std::make_shared<Necromancer>(&player1);
        auto necromancer2 = std::make_shared<Necromancer>(&player2);

        player1.ActiveCreaturesByID.push_back(necromancer1->ID);
        player2.ActiveCreaturesByID.push_back(necromancer2->ID);

        player1.NecromancerID = necromancer1->ID;
        player2.NecromancerID = necromancer2->ID;

        SessionGrid.PlaceCreature(0, 0, necromancer1);
        SessionGrid.PlaceCreature(SessionGrid.Width - 1, SessionGrid.Height - 1, necromancer2);
    }

    void PlayRound() {

    }
};



