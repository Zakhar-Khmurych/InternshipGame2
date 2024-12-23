#pragma once

#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputHandler.h"
#include "TextureManager.h"

// to do list
// keys moved away
// green square separated
// frame separated
// time-based loop instead of timeless




class WindowRenderer {

    int window_width;
    int window_height;
    InputHandler* inputHandler;



public:
    WindowRenderer(int width, int height, InputHandler* handler)
        : window_width(width), window_height(height), inputHandler(handler) 
    {
       
    
    }


    

    void RunTheGame() {       
        sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Internship game");
        sf::Clock clock;
        sf::Time elapsed = clock.restart();

       
     
        while (window.isOpen()) {

            InputAction action = inputHandler->processInput(window);
            if (action == InputAction::Exit) {
                break;
            }
            sf::Time elapsed = clock.restart();
            float deltaTime = elapsed.asSeconds();
            window.clear();


            window.display();
        }
    }
};



