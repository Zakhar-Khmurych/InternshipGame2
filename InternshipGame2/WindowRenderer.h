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
    TextureManager textureManager;


public:
    WindowRenderer(int width, int height, InputHandler* input_handler, GameHandler* game_handler)
        : window_width(width), window_height(height), inputHandler(input_handler), gameHandler(game_handler)
    {
        
  
    }

    void LoadAllCreatureTextures(TextureManager& textureManager) {
        textureManager.loadTexture("necromancer", "assets/necromancer.png");
        textureManager.loadTexture("skeleton", "assets/skeleton.png");
        textureManager.loadTexture("knight", "assets/knight.png");
        textureManager.loadTexture("berserker", "assets/berserker.png");
        textureManager.loadTexture("assassin", "assets/assassin.png");
        textureManager.loadTexture("elf", "assets/elf.png");
        textureManager.loadTexture("goblin", "assets/goblin.png");
        textureManager.loadTexture("wall", "assets/wall.png");
    }
    

    void RunTheGame() {       
        sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Internship game");
        sf::Clock clock;
        sf::Time elapsed = clock.restart();
        Grid currentGrid = gameHandler->GetGrid();
        std::cout << "Grid Width: " << currentGrid.Width << " Grid Height: " << currentGrid.Height << std::endl;
        
        textureManager.initializeInvalidTexture();
        LoadAllCreatureTextures(textureManager);

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
            HighlightPlayerCreatures(window, currentGrid);


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
                cellShape.setFillColor(sf::Color(200, 200, 200, 100));  // Світло-сірий колір клітинки

                int posX = x * (cellSize + cellGap);
                int posY = y * (cellSize + cellGap);
                cellShape.setPosition(posX, posY);

                window.draw(cellShape);
            }
        }
    }

    void HighlightPlayerCreatures(sf::RenderWindow& window, const Grid& grid) {
        const int cellGap = 5;
        int cellSize = static_cast<int>(std::min(window.getSize().x / grid.Width, window.getSize().y / grid.Height)) - cellGap;

        for (int x = 0; x < grid.Width; ++x) {
            for (int y = 0; y < grid.Height; ++y) {
                const Cell& cell = grid.GetCell(x, y);

                if (!cell.IsEmpty()) {
                    Creature& creature = cell.CellTaker->get();

                    sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
                    cellShape.setPosition(x * (cellSize + cellGap), y * (cellSize + cellGap));

                    // Застосування текстури
                    cellShape.setTexture(&textureManager.getTexture(creature.TextureName));

                    // Накладання кольору
                    if (creature.Owner == gameHandler->p1) {
                        cellShape.setFillColor(sf::Color(255, 0, 0, 250));  // Напівпрозорий червоний
                    }
                    else if (creature.Owner == gameHandler->p2) 
                    {
                        cellShape.setFillColor(sf::Color(0, 0, 255, 250));  // Напівпрозорий синій
                    }
                    window.draw(cellShape);
                }
            }
        }
    }


};



