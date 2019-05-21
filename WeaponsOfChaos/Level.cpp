#include "stdafx.h"
#include "Level.h"


Level::Level()
{
	this->ground = new Ground(1);
//	this->generateCoins(1);
}


Level::~Level()
{
}

void Level::drawTo(sf::RenderWindow & window)
{
	this->ground->drawTo(window);
//	for (list<Coin*>::iterator it = CoinsArray.begin; it != CoinsArray.end; it++) {
//		(*it)->drawTo(window);
//	}
}

void Level::generateCoins(int n)
{
	for (int i = 0; i < n; i++) {
		Coin* argent = new Coin(this->ground);
		this->CoinsArray.push_back(argent);
	}
}
