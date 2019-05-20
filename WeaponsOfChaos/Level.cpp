#include "stdafx.h"
#include "Level.h"


Level::Level()
{
	this->ground = new Ground(1);
}


Level::~Level()
{
}

void Level::drawTo(sf::RenderWindow & window)
{
	this->ground->drawTo(window);
}
