#pragma once
#include <SFML/Graphics.hpp>

enum class InputAction {
	None,
	Exit,
    SelectCell,
    RequestCellSelection,
    StartTurn,
    EndTurn,
    SkipTurn,
    StartRound,
    EndRound,
    ChooseCreature,
    StartSession,
    EndSession,
    DoSomethingOnSpace
};


class InputHandler {
public:
	virtual ~InputHandler() = default;

	virtual InputAction processInput(sf::RenderWindow& window) = 0;
};

class GameInput : public InputHandler {
    InputAction processInput(sf::RenderWindow& window) override {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return InputAction::Exit;
            }
            
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            return InputAction::DoSomethingOnSpace;
        }
 

        return InputAction::None;
    }
};