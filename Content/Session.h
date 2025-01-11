#pragma once
#include "Player.h"
#include "Grid.h"
#include "Creatures.h"
#include <functional>
#include <vector>
#include <queue>
#include "GameEvents.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Sleep.hpp>

struct CreatureInitiativeComparator {
    bool operator()(const std::shared_ptr<Creature>& a, const std::shared_ptr<Creature>& b) const {
        if (a->Initiative == b->Initiative) {
            return a->ResolveInitiative() < b->ResolveInitiative();  // tie-breaker
        }
        return a->Initiative < b->Initiative;  // спадаюча ініціатива
    }
};

class Session {
    int round_number;
    bool isSessionActive = true;
    GameEventManager& eventManager;
public:
    Player& player1;
    Player& player2;
    Grid& SessionGrid;
    std::priority_queue<std::shared_ptr<Creature>,
        std::vector<std::shared_ptr<Creature>>,
        CreatureInitiativeComparator> InitiativeQueue;

    Session(Player& p1, Player& p2, Grid& session_grid, GameEventManager& event_manager)
        : player1(p1), player2(p2), SessionGrid(session_grid), eventManager(event_manager){}

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
        //PlayRound();

        auto winners = CheckDefeatConditions();
        if (!winners.empty()) {
            for (auto* winner : winners) {
                std::cout << winner->Name << " wins the game!" << std::endl;
            }
            isSessionActive = false;  // Зупиняємо гру
        }
    }

    void PlayRound() {

        std::cout << "Starting round" << round_number << "...\n";
        //check win-lose condition (incoming)
        //give coins
        player1.GiveCoin(1);
        player2.GiveCoin(1);

        for (Player* player : { &player1, &player2 }) {
            std::cout << player->Name << ", choose a creature to summon or skip:\n";

            //а може не 
            bool turnFinished = false;
            while (!turnFinished) {
                if (eventManager.HasEvents()) {
                    GameEvent event = eventManager.GetNextEvent();
                    std::cout << "Processing event: " << static_cast<int>(event) << std::endl;
                    switch (event) {
                    case GameEvent::SelectCell:
                        std::cout << player->Name << " selected a cell.\n";
                        turnFinished = true;
                        break;
                    case GameEvent::SkipTurn:
                        std::cout << player->Name << " skipped the turn.\n";
                        turnFinished = true;
                        break;
                    default:
                        std::cout << "Unknown event.\n";
                        break;
                    }
                }
                else {
                    std::cout << "sleep";
                    sf::sleep(sf::milliseconds(500));  // Затримка на 100 мс
                }
            }
        }

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
        InitializeInitiativeQueue();
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
        InitiativeQueue = {};  // очищаємо чергу
        SessionGrid.RollInitiativeForAll();

        auto creatures = SessionGrid.GetAllCreatures();

        // 4. Сортування за ініціативою
        std::sort(creatures.begin(), creatures.end(), CreatureInitiativeComparator());

        // Додаємо всіх до черги
        for (auto& creature : creatures) {
            InitiativeQueue.push(creature);
        }
    }

    std::vector<Player*> CheckDefeatConditions() {
        bool player1HasNecromancer = false;
        bool player2HasNecromancer = false;

        // Перевірка всіх клітинок на наявність некромантів
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

        // Формуємо результат поразки
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

