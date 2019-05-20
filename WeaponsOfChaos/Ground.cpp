#include "stdafx.h"
#include "Ground.h"


Ground::Ground(int nlevel)
{

	// rappel : plateform(height, beginning, length) avec (0 0) en bas à droite de l'écran
	if (nlevel == 1) {
		Plateform* plat1 = new Plateform(20, 50, 100);
		this->plateforms.push_back(plat1);
		Plateform* plat2 = new Plateform(0, 0, 100000);
		this->plateforms.push_back(plat2);
		Plateform* plat3 = new Plateform(200, 500, 1000);
		this->plateforms.push_back(plat3);

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
