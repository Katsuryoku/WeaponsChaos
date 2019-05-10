#include "stdafx.h"
#include "Shop.h"


void Shop::refresh()
{
}

void Shop::choseItem()
{
}

void Shop::addItem()
{
}

void Shop::unavailableItem(int item)
{
}

void Shop::availableItem(int item)
{
}

void Shop::drawTo(sf::RenderWindow & window)
{
	window.draw(shop);
}

void Shop::setPos(sf::Vector2f newPos)
{
	shop.setPosition(newPos);
}

Shop::Shop(sf::Vector2f size)
{
	shop.setSize(size);
}


Shop::~Shop()
{
}
