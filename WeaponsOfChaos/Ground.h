#pragma once
#include "Plateform.h"
#include <list>
using namespace std;

class Ground
{
private:
	list<Plateform*> plateforms;
	int totLength_ = 0;
public:
	Ground(int nlevel);
	~Ground();
	void drawTo(sf::RenderWindow &window);
	int getTotLength();
	list<Plateform*> getPlateforms();
};

