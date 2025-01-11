#pragma once
#include "../Content/Grid.h"
#include "../Content/Session.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <condition_variable>


class GameHandler
{
    void GameLoop() {
        while (isRunning) {
            std::unique_lock<std::mutex> lock(eventMutex);
            eventCondition.wait(lock, [this]() {
                return event_manager.HasEvents() || !isRunning;
                });

            if (!isRunning) break;

            // Обробка подій
            if (event_manager.HasEvents()) {
                auto event = event_manager.GetNextEvent();
                HandleEvent(event);
            }

            // Виклик логіки гри
            UpdateGame();
        }
    }

    void HandleEvent(GameEvent event) {
        // Обробка події
    }

public:
    std::unique_ptr<Grid> _grid;
    std::unique_ptr<Player> p1;
    std::unique_ptr<Player> p2;
    std::unique_ptr<Session> current_session;
    GameEventManager& event_manager;

    std::thread gameThread;
    std::atomic<bool> isRunning{ true };
    std::mutex eventMutex;
    std::condition_variable eventCondition;
    ~GameHandler() {
        StopGameThread();
    }
    void StartGameThread() {
        gameThread = std::thread([this]() { GameLoop(); });
    }
    void StopGameThread() {
        isRunning = false;
        eventCondition.notify_all();
        if (gameThread.joinable()) {
            gameThread.join();
        }
    }



    GameHandler(GameEventManager& manager)
        : event_manager(manager) {
        _grid = std::make_unique<Grid>(10, 10);
        p1 = std::make_unique<Player>("player 1");
        p2 = std::make_unique<Player>("player 2");
        current_session = std::make_unique<Session>(*p1, *p2, *_grid, event_manager);

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

    GameEvent ProcessInput(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                event_manager.AddEvent(GameEvent::Exit);
                return GameEvent::Exit;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            std::lock_guard<std::mutex> lock(eventMutex);
            event_manager.AddEvent(GameEvent::SelectCell);
            eventCondition.notify_one();
            return GameEvent::SelectCell;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            std::lock_guard<std::mutex> lock(eventMutex);
            event_manager.AddEvent(GameEvent::SkipTurn);
            eventCondition.notify_one();
            return GameEvent::SkipTurn;
        }
        std::lock_guard<std::mutex> lock(eventMutex);
        event_manager.AddEvent(GameEvent::None);
        eventCondition.notify_one();

        return GameEvent::None;
    }

};

