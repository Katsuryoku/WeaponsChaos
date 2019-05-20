#pragma once
#include "Plateform.h"
#include <list>
using namespace std;

class Ground
{
private:
	list<Plateform*> plateforms;
public:
	Ground(int nlevel);
	~Ground();
	void drawTo(sf::RenderWindow &window);
};

