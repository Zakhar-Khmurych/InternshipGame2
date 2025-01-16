#pragma once
#include <algorithm>
#include "Cell.h"
#include "Creature.h"
#include <vector>
#include <queue>
#include <iostream>

class Grid {
public:
    int Width;
    int Height;
    std::vector<std::vector<Cell>> Cells;

    Grid(int width, int height) : Width(width), Height(height) {
        Cells.resize(width, std::vector<Cell>(height));
    }

    bool IsValidPosition(int x, int y) const {
        return x >= 0 && x < Width&& y >= 0 && y < Height;
    }

    void RemoveCreature(int x, int y) {
        if (IsValidPosition(x, y)) {
            Cells[x][y].RemoveCreature();
        }
    }

    void PlaceCreature(int x, int y, std::shared_ptr<Creature> creature) {
        if (IsValidPosition(x, y)) {
            Cell& cell = GetCell(x, y);
            if (cell.IsEmpty()) {
                cell.CellTaker = creature;
                creature->CurrentX = x;  // Set the creature's x-coordinate
                creature->CurrentY = y;  // Set the creature's y-coordinate
            }
        }
    }


    Cell& GetCell(int x, int y) {
        if (x < 0 || x >= Width || y < 0 || y >= Height) {
            std::cerr << "Error: Invalid cell coordinates (" << x << ", " << y << ")." << std::endl;
            throw std::out_of_range("Invalid grid coordinates");
        }
        return Cells[x][y]; // Accessing the cell
    }

    const Cell& GetCell(int x, int y) const {
        return Cells[x][y];
    }

    std::vector<Cell*> DijkstraXY(int startX, int startY, int steps) {
        std::vector<Cell*> reachableCells;
        std::vector<std::vector<int>> distances(Width, std::vector<int>(Height, INT_MAX));

        std::queue<std::pair<int, int>> queue;
        queue.emplace(startX, startY);
        distances[startX][startY] = 0;

        int dx[4] = { 0, 1, 0, -1 };
        int dy[4] = { -1, 0, 1, 0 };

        while (!queue.empty()) {
            auto [currentX, currentY] = queue.front();
            queue.pop();
            int currentDistance = distances[currentX][currentY];

            for (int i = 0; i < 4; i++) {
                int nextX = currentX + dx[i];
                int nextY = currentY + dy[i];

                if (IsValidPosition(nextX, nextY) && distances[nextX][nextY] == INT_MAX && Cells[nextX][nextY].IsEmpty()) {
                    int newDistance = currentDistance + 1;
                    if (newDistance <= steps) {
                        distances[nextX][nextY] = newDistance;
                        queue.emplace(nextX, nextY);
                        reachableCells.push_back(&Cells[nextX][nextY]);
                    }
                }
            }
        }

        return reachableCells;
    }

    void RemoveDeadCreatures() {
        for (int x = 0; x < Width; ++x) {
            for (int y = 0; y < Height; ++y) {
                if (Cells[x][y].CellTaker) { // Check if shared_ptr is not null
                    auto creature = Cells[x][y].CellTaker; // Copy shared_ptr
                    if (creature->HP < 1) { // Access HP via shared_ptr
                        Cells[x][y].RemoveCreature();
                    }
                }
            }
        }
    }

    void RollInitiativeForAll() {
        for (int x = 0; x < Width; ++x) {
            for (int y = 0; y < Height; ++y) {
                auto creature = Cells[x][y].CellTaker;
                if (creature) {
                    creature->RollInitiative();
                }
            }
        }
    }

    std::vector<std::shared_ptr<Creature>> GetAllCreatures() const {
        std::vector<std::shared_ptr<Creature>> creatures;

        for (int x = 0; x < Width; ++x) {
            for (int y = 0; y < Height; ++y) {
                auto creature = Cells[x][y].CellTaker;
                if (creature) {
                    creatures.push_back(creature);
                }
            }
        }
        return creatures;
    }

    void DrawGridInConsole() const {
        for (int y = 0; y < Height; ++y) {
            for (int x = 0; x < Width; ++x) {
                const Cell& cell = Cells[x][y];

                // Print '.' for empty cells and 'x' for taken cells
                if (cell.IsEmpty()) {
                    std::cout << ". ";  // Empty cell
                }
                else {
                    std::cout << "x ";  // Taken cell
                }
            }
            std::cout << std::endl;  // New line after each row
        }
    }

    void MoveCreature(int startX, int startY, int destX, int destY, std::shared_ptr<Creature> creature) {
        if (!creature) {
            std::cerr << "Error: No creature provided to move." << std::endl;
            return;
        }

        // Ensure the start cell contains the creature
        if (Cells[startX][startY].CellTaker != creature) {
            std::cerr << "Error: Creature is not in the start cell." << std::endl;
            return;
        }

        // Remove the creature from the start cell
        Cells[startX][startY].RemoveCreature();

        // Ensure the destination cell is empty
        if (Cells[destX][destY].IsEmpty()) {
            // Place the creature in the destination cell
            Cells[destX][destY].CellTaker = creature;

            // Update the creature's internal coordinates after the move
            creature->CurrentX = destX;
            creature->CurrentY = destY;
        }
        else {
            std::cerr << "Error: Destination cell is not empty." << std::endl;
            // Optionally, return the creature to the start cell if needed
            Cells[startX][startY].CellTaker = creature;
        }
    }





};

/*
class Grid {
public:
    int Width;
    int Height;
    std::vector<std::vector<Cell>> Cells;

    Grid(int width, int height) : Width(width), Height(height) {
        Cells.resize(width, std::vector<Cell>(height));
    }

    bool IsValidPosition(int x, int y) const {
        return x >= 0 && x < Width&& y >= 0 && y < Height;
    }

    Cell& GetCell(int x, int y) {
        return Cells[x][y];
    }

    void PlaceCreature(int x, int y, ICreature* creature) {
        if (IsValidPosition(x, y)) {
            Cell& cell = GetCell(x, y);
            if (cell.IsEmpty()) {
                cell.CellTaker = creature;
            }
        }
    }

    void RemoveCreature(int x, int y) {
        if (IsValidPosition(x, y)) {
            Cells[x][y].RemoveCreature();
        }
    }
};
*/
 
    /*
    void RemoveCreature(int x, int y) {
        Cells[x][y].RemoveCreature();
    }

    
    void PlaceCreature(int x, int y, ICreature* creature) {
        Cell& cell = GetCell(x, y);
        if (cell.IsEmpty()) {
            cell.CellTaker = creature;
        }
    }

       Cell& GetCell(int x, int y) {
        return Cells[x][y];
    }
    
    std::vector<Cell*> DijkstraXY(int startX, int startY, int steps) {
        std::vector<Cell*> reachableCells;
        std::vector<std::vector<int>> distances(Width, std::vector<int>(Height, INT_MAX));

        std::queue<std::pair<int, int>> queue;
        queue.emplace(startX, startY);
        distances[startX][startY] = 0;

        int dx[4] = { 0, 1, 0, -1 };
        int dy[4] = { -1, 0, 1, 0 };

        while (!queue.empty()) {
            auto [currentX, currentY] = queue.front();
            queue.pop();
            int currentDistance = distances[currentX][currentY];

            for (int i = 0; i < 4; i++) {
                int nextX = currentX + dx[i];
                int nextY = currentY + dy[i];

                if (IsValidPosition(nextX, nextY) && distances[nextX][nextY] == INT_MAX && Cells[nextX][nextY].IsEmpty()) {
                    int newDistance = currentDistance + 1;
                    if (newDistance <= steps) {
                        distances[nextX][nextY] = newDistance;
                        queue.emplace(nextX, nextY);
                        reachableCells.push_back(&Cells[nextX][nextY]);
                    }
                }
            }
        }

        return reachableCells;
    }
    */
    




