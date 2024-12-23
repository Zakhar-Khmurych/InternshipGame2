#pragma once
#include "ICreature.h"
#include "Cell.h"
#include <vector>
#include <queue>

/*

class Cell;
class Creature;


class Grid {
public:
    int Width;
    int Height;
    std::vector<std::vector<Cell>> Cells;

    Grid(int width, int height) : Width(width), Height(height) {
        Cells.resize(width, std::vector<Cell>(height));
    }

    Cell& GetCell(int x, int y) {
        return Cells[x][y];
    }

    void PlaceCreature(int x, int y, Creature* creature) {
        Cell& cell = GetCell(x, y);
        if (cell.IsEmpty()) {
            cell.CellTaker = creature;
        }
    }

    void RemoveCreature(int x, int y) {
        Cells[x][y].RemoveCreature();
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

    bool IsValidPosition(int x, int y) const {
        return x >= 0 && x < Width&& y >= 0 && y < Height;
    }
};



*/