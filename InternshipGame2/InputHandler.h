#pragma once
#include <SFML/Graphics.hpp>
#include "../Content/GameEvents.h"

class InputHandler {
public:
    virtual ~InputHandler() = default;

    virtual GameEvent processInput(sf::RenderWindow& window) = 0;
};

class GameInput : public InputHandler {
    GameEventManager& eventManager;

public:
    GameInput(GameEventManager& manager) : eventManager(manager) {}

    GameEvent processInput(sf::RenderWindow& window) override {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                eventManager.AddEvent(GameEvent::Exit);
                return GameEvent::Exit;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            eventManager.AddEvent(GameEvent::DoSomethingOnSpace);
            return GameEvent::DoSomethingOnSpace;
        }

        return GameEvent::None;
    }
};
