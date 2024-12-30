#pragma once
#include "../Content/Grid.h"
#include "../Content/Session.h"
#include <memory>


class GameHandler
{
public:
	Grid* _grid;
	Player* p1;
	Player* p2;
	Session* current_session;

	GameHandler() {
		_grid = new Grid(10, 10);
		p1 = new Player("player 1");
		p2 = new Player("player 2");
		current_session = new Session(*p1, *p2, *_grid);
		current_session->PlaceNecromancers();
	}


	void HandleTheGame() {
		


	}

	Grid& GetGrid() {
		//return *_grid;
		return current_session->SessionGrid;
	}

};

