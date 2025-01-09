#pragma once
#include "Player.h"
#include "Grid.h"
#include "Creatures.h"
#include <functional>
#include <vector>
#include <queue>

struct CreatureInitiativeComparator {
    bool operator()(const std::shared_ptr<Creature>& a, const std::shared_ptr<Creature>& b) const {
        if (a->Initiative == b->Initiative) {
            return a->ResolveInitiative() < b->ResolveInitiative();  // tie-breaker
        }
        return a->Initiative < b->Initiative;  // �������� ����������
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
        //while not lost, playrounds
        round_number = 1;
        isSessionActive = true;

    }

    void UpdateSession() {
        if (!isSessionActive) return;

        //std::cout << "Round " << round_number << std::endl;
        round_number++;
        PlayRound();

        auto winners = CheckDefeatConditions();
        if (!winners.empty()) {
            for (auto* winner : winners) {
                std::cout << winner->Name << " wins the game!" << std::endl;
            }
            isSessionActive = false;  // ��������� ���
        }
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

    void InitializeInitiativeQueue() {
        InitiativeQueue = {};  // ������� �����
        SessionGrid.RollInitiativeForAll();

        auto creatures = SessionGrid.GetAllCreatures();

        // 4. ���������� �� �����������
        std::sort(creatures.begin(), creatures.end(), CreatureInitiativeComparator());

        // ������ ��� �� �����
        for (auto& creature : creatures) {
            InitiativeQueue.push(creature);
        }
    }

    std::vector<Player*> CheckDefeatConditions() {
        bool player1HasNecromancer = false;
        bool player2HasNecromancer = false;

        // �������� ��� ������� �� ��������� ����������
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

        // ������� ��������� �������
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

