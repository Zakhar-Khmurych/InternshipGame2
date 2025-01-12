#pragma once
#include "Player.h"
#include "Grid.h"
#include "Creatures.h"
#include <functional>
#include <iostream>

#include <vector>
#include <queue>
#include "GameEvents.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Sleep.hpp>

struct CreatureInitiativeComparator {
    bool operator()(const std::shared_ptr<Creature>& a, const std::shared_ptr<Creature>& b) const {
        if (a->Initiative == b->Initiative) {
            return a->ResolveInitiative() < b->ResolveInitiative(); // tie-breaker
        }
        return a->Initiative < b->Initiative; // descending initiative
    }
};

class Session {
    int round_number;
    bool isSessionActive = true;

public:
    Player& player1;
    Player& player2;
    Grid& SessionGrid;
    std::priority_queue<std::shared_ptr<Creature>,
        std::vector<std::shared_ptr<Creature>>,
        CreatureInitiativeComparator> InitiativeQueue;

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

        round_number = 1;
        isSessionActive = true;
    }
    void PlayRound() {
        player1.GiveCoin(1);
        player2.GiveCoin(1);
        std::cout << "Gave coins to" << player1.Name << " and " << player2.Name << std::endl;
        std::cout << "waiting for action" << std::endl;
        while (true)
        {
            
        }
        //for each player
        //wait for action
        //only when actions receieved, go on
        InitializeInitiativeQueue();

        ++round_number;
    }
    void PlayTurn() {
        //wait for action
        //only when action receieved, go on
    }
    void InitializeInitiativeQueue() {
        InitiativeQueue = {};
        SessionGrid.RollInitiativeForAll();

        auto creatures = SessionGrid.GetAllCreatures();
        for (auto& creature : creatures) {
            InitiativeQueue.push(creature);
        }
    }

    std::vector<Player*> CheckDefeatConditions() {
        bool player1HasNecromancer = false;
        bool player2HasNecromancer = false;

        for (int x = 0; x < SessionGrid.Width; ++x) {
            for (int y = 0; y < SessionGrid.Height; ++y) {
                auto creature = SessionGrid.GetCell(x, y).CellTaker;
                if (creature && creature->HP > 0) {
                    if (creature->Owner == &player1 && creature->ID == player1.NecromancerID) {
                        player1HasNecromancer = true;
                    }
                    if (creature->Owner == &player2 && creature->ID == player2.NecromancerID) {
                        player2HasNecromancer = true;
                    }
                }
            }
        }

        std::vector<Player*> winners;
        if (player1HasNecromancer && !player2HasNecromancer) {
            winners.push_back(&player1);
        }
        if (player2HasNecromancer && !player1HasNecromancer) {
            winners.push_back(&player2);
        }

        return winners;
    }
};

// Implementation details for Session

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

