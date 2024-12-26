#pragma once

#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputHandler.h"
#include "TextureManager.h"
#include "GameHandler.h"


// to do list
// keys moved away
// green square separated
// frame separated
// time-based loop instead of timeless




class WindowRenderer {

    int window_width;
    int window_height;
    InputHandler* inputHandler;
    GameHandler* gameHandler;
    

public:
    WindowRenderer(int width, int height, InputHandler* input_handler, GameHandler* game_handler)
        : window_width(width), window_height(height), inputHandler(input_handler), gameHandler(game_handler)
    {
       
    
    }


    

    void RunTheGame() {       
        sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Internship game");
        sf::Clock clock;
        sf::Time elapsed = clock.restart();
        Grid currentGrid = gameHandler->GetGrid();
        std::cout << "Grid Width: " << currentGrid.Width << " Grid Height: " << currentGrid.Height << std::endl;
     
        while (window.isOpen()) {

            InputAction action = inputHandler->processInput(window);
            if (action == InputAction::Exit) {
                break;
            }
            sf::Time elapsed = clock.restart();
            float deltaTime = elapsed.asSeconds();
            window.clear();

            currentGrid = gameHandler->GetGrid();
            std::cout << "Grid Width: " << currentGrid.Width << " Grid Height: " << currentGrid.Height << std::endl;
            RenderTheField(window, currentGrid);

            window.display();
        }
    }

    void RenderTheField(sf::RenderWindow& window, const Grid& grid) {
        const int cellGap = 5;  // Статичний проміжок між клітинками
        int cellSize = static_cast<int>(std::min(window.getSize().x / grid.Width, window.getSize().y / grid.Height)) - cellGap;
       
        // Відображення сітки
        for (int x = 0; x < grid.Width; ++x) {
            for (int y = 0; y < grid.Height; ++y) {
                sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
                cellShape.setFillColor(sf::Color(200, 200, 200));  // Світло-сірий колір клітинки

                int posX = x * (cellSize + cellGap);
                int posY = y * (cellSize + cellGap);
                cellShape.setPosition(posX, posY);

                window.draw(cellShape);
            }
        }
    }



};



