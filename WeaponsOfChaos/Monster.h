#pragma once
#include <Vector2.hpp>
#include "Nature.h"
#include "State.h"
class Monster
{
private :
	sf::Vector2f position;
	int level;
	int currentLife;
	State state;
	int maxLife;
	int strength;
	Nature nature;
public:
	int attack();
	bool moveleft();
	bool moveRight();
	bool generate();
	bool loselife(int life);
	Monster(sf::Vector2f pos, int lvl, int sE, int mL, int s);
	Monster();
	~Monster();
};

