#pragma once
#include "Player.h"
#include "Grid.h"
#include "Creatures.h"


class Session {
public:
    Player& player1;
    Player& player2;
    Grid& SessionGrid;
    std::vector<std::shared_ptr<Creature>> InitiativeQueue;

    Session(Player& p1, Player& p2, Grid& session_grid)
        : player1(p1), player2(p2), SessionGrid(session_grid) {}

    void StartSession() {
        auto necromancer1 = std::make_shared<Necromancer>(&player1);
        auto necromancer2 = std::make_shared<Necromancer>(&player2);

        player1.ActiveCreaturesByID.push_back(necromancer1->ID);
        player2.ActiveCreaturesByID.push_back(necromancer2->ID);

        player1.NecromancerID = necromancer1->ID;
        player2.NecromancerID = necromancer2->ID;

        SessionGrid.PlaceCreature(0, 0, necromancer1);
        SessionGrid.PlaceCreature(SessionGrid.Width - 1, SessionGrid.Height - 1, necromancer2);
        //session was initialized
    }

    void PlayRound() {
        //check win-lose condition (incoming)
        //give coins
        /*
        for each player:
            cout << choose creature
            while no CreatureChosenReceived or SkipEvent:
                do nothing, just wait
        */
        //once all players have placed creatures
        //roll initiative for all creatures
        //resolve initiative
        //add all creatures to queue accordingly to initiative
        //for each creature in queue:
            //run round
    }

    void PlayTurn() {
        //if dead, then skip and remove this creature
        //cout << choose action: skip, move, hit
        //if skip, then skip
        //if hit or move, chose target cell
    }
};

/*
new events I need:
None
AbstractExit
CreatureChosenReceived (which one)
RoundSkipped
TurnSkipped
PlayerMoves (where)
PlayerAttacks (also where)
*/

