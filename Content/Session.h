#pragma once
#include "Player.h"
#include "Grid.h"

/*
class Session {
public:
    Player Player1;
    Player Player2;
    Grid SessionGrid;

    Session(Player p1, Player p2, int width, int height)
        : Player1(p1), Player2(p2), SessionGrid(width, height) {}

    void PlaceNecromancers() {
        Necromancer* n1 = new Necromancer();
        Necromancer* n2 = new Necromancer();

        Player1.ActiveCreaturesByID.push_back(n1->ID);
        Player2.ActiveCreaturesByID.push_back(n2->ID);

        Player1.NecromancerID = n1->ID;
        Player2.NecromancerID = n2->ID;

        SessionGrid.PlaceCreature(0, 0, n1);
        SessionGrid.PlaceCreature(SessionGrid.Width - 1, SessionGrid.Height - 1, n2);
    }
};

*/

