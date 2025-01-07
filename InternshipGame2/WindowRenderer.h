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

    void RunTheGame() {
        sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Internship game");
        sf::Clock clock;
        Grid* currentGrid = gameHandler->GetGrid();

        if (!currentGrid) {
            std::cerr << "Error: currentGrid is nullptr!" << std::endl;
            return;
        }
        if (currentGrid->Width == 0 || currentGrid->Height == 0) {
            std::cerr << "Error: Grid size is invalid (0)!" << std::endl;
            return;
        }

        std::cout << "Grid Width: " << currentGrid->Width << " Grid Height: " << currentGrid->Height << std::endl;

        textureManager.initializeInvalidTexture();
        textureManager.initializeAll();

        while (window.isOpen()) {

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            InputAction action = inputHandler->processInput(window);
            if (action == InputAction::Exit) {
                window.close();
                break;
            }

            sf::Time elapsed = clock.restart();
            float deltaTime = elapsed.asSeconds();
            window.clear();

            currentGrid = gameHandler->GetGrid();
            if (!currentGrid) {
                std::cerr << "Error: currentGrid is nullptr during game loop!" << std::endl;
                break;
            }

            std::cout << "Grid Width: " << currentGrid->Width << " Grid Height: " << currentGrid->Height << std::endl;

            RenderTheField(window, *currentGrid);
            HighlightPlayerCreatures(window, *currentGrid);

            window.display();
        }
    }

    void RenderTheField(sf::RenderWindow& window, const Grid& grid) {
        const float cellGap = 5.0f;
        float cellSize = static_cast<float>(std::min(window.getSize().x / grid.Width, window.getSize().y / grid.Height)) - cellGap;

        for (int x = 0; x < grid.Width; ++x) {
            for (int y = 0; y < grid.Height; ++y) {
                sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
                cellShape.setFillColor(sf::Color(200, 200, 200, 100));

                float posX = static_cast<float>(x) * (cellSize + cellGap);
                float posY = static_cast<float>(y) * (cellSize + cellGap);

                cellShape.setPosition(posX, posY);

                window.draw(cellShape);
            }
        }
    }

    void HighlightPlayerCreatures(sf::RenderWindow& window, const Grid& grid) {
        const float cellGap = 5.0f;
        float cellSize = static_cast<float>(std::min(window.getSize().x / grid.Width, window.getSize().y / grid.Height)) - cellGap;

        for (int x = 0; x < grid.Width; ++x) {
            for (int y = 0; y < grid.Height; ++y) {
                const Cell& cell = grid.GetCell(x, y);

                if (!cell.IsEmpty() && cell.CellTaker) {
                    std::shared_ptr<Creature> creaturePtr = cell.CellTaker;
                    Creature& creature = *creaturePtr;

                    sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
                    cellShape.setPosition(static_cast<float>(x) * (cellSize + cellGap),
                        static_cast<float>(y) * (cellSize + cellGap));

                    if (creature.TextureName.empty()) {
                        std::cerr << "Creature texture name is empty!" << std::endl;
                        cellShape.setTexture(&textureManager.getTexture("invalid"));
                    }
                    else {
                        cellShape.setTexture(&textureManager.getTexture(creature.TextureName));
                    }

                    if (creature.Owner == gameHandler->p1.get()) {
                        cellShape.setFillColor(sf::Color(255, 0, 0, 255));
                    }
                    else if (creature.Owner == gameHandler->p2.get()) {
                        cellShape.setFillColor(sf::Color(0, 0, 255, 255));
                    }
                    window.draw(cellShape);
                }
            }
        }
    }
};