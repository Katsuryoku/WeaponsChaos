#include "stdafx.h"
#include "Ground.h"


Ground::Ground(int nlevel)
{

	// rappel : plateform(height, beginning, length) avec (0 0) en bas à droite de l'écran
	if (nlevel == 1) {
		Plateform* plat1 = new Plateform(20, 50, 100);
		this->plateforms.push_back(plat1);
		this->totLength_ += 100;

		Plateform* plat2 = new Plateform(0, 0, 500);
		this->plateforms.push_back(plat2);
		this->totLength_ += 500;

		Plateform* plat3 = new Plateform(200, 500, 200);
		this->plateforms.push_back(plat3);
		this->totLength_ += 200;


	}
}


Ground::~Ground()
{
}

void Ground::drawTo(sf::RenderWindow & window)
{
	list<Plateform*>::iterator it;
	for (it = this->plateforms.begin(); it != this->plateforms.end(); it++) {
		(**it).drawTo(window);
	}
}

int Ground::getTotLength()
{
	return this->totLength_;
}

list<Plateform*> Ground::getPlateforms()
{
	return this->plateforms;
}
