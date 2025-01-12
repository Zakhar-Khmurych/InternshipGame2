#pragma once
#include <SFML/Graphics.hpp>
#include "../Content/GameEvents.h"

class InputHandler {
public:
    GameEvent ProcessInput(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return GameEvent::Exit;
            }
        }
        return GameEvent::None;
    }
};
