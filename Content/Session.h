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
        std::cout << "Gave coins to " << player1.Name << " and " << player2.Name << std::endl;

        // Додано цикл для обробки ходів кожного гравця
        for (Player* currentPlayer : { &player1, &player2 }) {
            bool actionCompleted = false;

            while (!actionCompleted) {
                std::cout << currentPlayer->Name << ", it's your turn!" << std::endl;
                std::cout << "Enter 'skip' to skip your turn or 'place_creature' to place a creature." << std::endl;

                std::string action;
                std::cin >> action;

                if (action == "skip") {
                    // Якщо гравець вибрав skip, пропускаємо хід
                    std::cout << currentPlayer->Name << " skipped their turn." << std::endl;
                    actionCompleted = true; // Закінчуємо цикл і переходимо до наступного гравця
                }
                else if (action == "place_creature") {
                    // Якщо гравець вибрав place_creature, запитуємо координати та тип істоти
                    int x, y;
                    std::string creatureType;

                    std::cout << "Enter coordinates (x y): ";
                    std::cin >> x >> y;

                    // Перевірка, чи валідні координати
                    if (!SessionGrid.IsValidPosition(x, y)) {
                        std::cout << "Invalid position!" << std::endl;
                        continue;
                    }

                    std::cout << "Enter creature type (necromancer, skeleton, knight, berserker, assassin, elf, goblin, wall): ";
                    std::cin >> creatureType;

                    // Створення істоти через Factory
                    auto creature = CreatureFactory::CreateCreature(creatureType, currentPlayer);

                    // Якщо створення істоти вдалося, розміщуємо її на полі
                    if (creature) {
                        SessionGrid.PlaceCreature(x, y, creature);
                        currentPlayer->ActiveCreaturesByID.push_back(creature->ID);
                        std::cout << creatureType << " placed at (" << x << ", " << y << ")" << std::endl;
                        actionCompleted = true;
                    }
                    else {
                        std::cout << "Invalid creature type!" << std::endl;
                    }
                }
            }
        }

        // Після того, як обидва гравці зробили свої ходи, ініціалізуємо чергу ініціатив
        InitializeInitiativeQueue();
        while (!InitiativeQueue.empty()) {
            auto currentCreature = InitiativeQueue.top();
            InitiativeQueue.pop();

            // Відправляємо істоту в метод PlayTurn для виконання її ходу
            PlayTurn(currentCreature);
        }
        ++round_number;
    }

    void PlayTurn(std::shared_ptr<Creature> currentCreature) {
        std::cout << currentCreature->Owner->Name << "'s creature "
            << currentCreature->GetTextureName() << " is taking its turn!" << std::endl;

        bool actionCompleted = false;

        // Цикл, поки істота не завершить свій хід
        while (!actionCompleted) {
            std::cout << "Enter 'skip' to skip, 'punch' to attack, or 'move' to move." << std::endl;
            std::string action;
            std::cin >> action;

            if (action == "skip") {
                // Пропуск ходу
                std::cout << currentCreature->GetTextureName() << " skipped their turn." << std::endl;
                actionCompleted = true;
            }
            else if (action == "punch") {
                // Атака
                int targetX, targetY;
                std::cout << "Enter target coordinates (x y) to attack: ";
                std::cin >> targetX >> targetY;

                if (!SessionGrid.IsValidPosition(targetX, targetY)) {
                    std::cout << "Invalid target coordinates!" << std::endl;
                    continue;
                }

                // Знаходимо істоту на вказаних координатах
                auto targetCreature = SessionGrid.GetCell(targetX, targetY).CellTaker;

                if (!targetCreature) {
                    std::cout << "No creature at target coordinates!" << std::endl;
                    continue;
                }

                // Виконуємо атаку
                currentCreature->Punch(*targetCreature);
                std::cout << currentCreature->GetTextureName() << " attacked "
                    << targetCreature->GetTextureName() << "!" << std::endl;
                actionCompleted = true;
            }
            else if (action == "move") {
                // Переміщення
                int moveX, moveY;
                std::cout << "Enter target coordinates (x y) to move: ";
                std::cin >> moveX >> moveY;
                std::cout << moveX << moveY;

                if (!SessionGrid.IsValidPosition(moveX, moveY)) {
                    std::cout << "Invalid target coordinates!" << std::endl;
                    continue;
                }

                std::cout << "Creature current position: ("
                    << currentCreature->CurrentX << ", "
                    << currentCreature->CurrentY << ")" << std::endl;

                // Перевірка, чи є достатньо руху для переміщення
                //if (currentCreature->MovementRemaining <= 0) {
                //    std::cout << currentCreature->GetTextureName() << " cannot move because no movement points are left." << std::endl;
               //     continue;
                //}

                // Видалення істоти зі старої клітинки
                //

                // Розміщуємо істоту на новій клітинці
                //SessionGrid.PlaceCreature(moveX, moveY, currentCreature);
                //SessionGrid.RemoveCreature(currentCreature->CurrentX, currentCreature->CurrentY);
                 SessionGrid.MoveCreature(currentCreature->CurrentX, currentCreature->CurrentY, moveX, moveY, currentCreature);

                // Оновлюємо координати істоти
                //currentCreature->CurrentX = moveX;
                //currentCreature->CurrentY = moveY;
  //              currentCreature->MovementRemaining--; // Витрачаємо один бал руху

                std::cout << currentCreature->GetTextureName() << " moved to ("
                    << moveX << ", " << moveY << ")" << std::endl;
                actionCompleted = true;
            }
            else {
                std::cout << "Invalid action! Please enter 'skip', 'punch', or 'move'." << std::endl;
            }
        }
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

