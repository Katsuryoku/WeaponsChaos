#include "stdafx.h"
#include "Coin.h"
#include <iostream>



Coin::Coin(Ground* ground)
{
	int place = rand() % (ground->getTotLength() - 1);
	list<Plateform*>::iterator it = ground->getPlateforms().begin();
	while (place > 0){
		cout << place;
		if ((place - (*it)->getLength()) <= 0) {
			int x = (*it)->getBeginning() + place;
			int y = (*it)->getHeight() - 10;
			position = Vector2f(x, y);
		}
	place -= (*it)->getLength();
	it--;
	}
}


Coin::~Coin()
{
}

void Coin::drawTo(sf::RenderWindow & window)
{
	RectangleShape rectangle(Vector2f(5, 5));
	rectangle.setPosition(this->position);
	rectangle.setFillColor(Color::Yellow);
	window.draw(rectangle);
}
