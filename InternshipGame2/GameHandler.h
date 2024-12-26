#pragma once
#include "../Content/Grid.h"
#include <memory>


class GameHandler
{
public:
	Grid* _grid;


	GameHandler() {
		_grid = new Grid(10, 10);
	}

	void HandleTheGame() {
		


	}

	Grid& GetGrid() {
		return *_grid;
	}

};

