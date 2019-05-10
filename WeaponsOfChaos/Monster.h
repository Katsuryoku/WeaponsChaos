#pragma once
#include <SFML\Graphics.hpp>
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
	sf::Image image;
	sf::Sprite sprite;
public:
	int attack();
	bool moveleft();
	bool moveRight();
	bool generate();
	bool loselife(int life);
	Monster(sf::Vector2f pos, int lvl, Nature nat, int mL, int s);
	Monster();
	~Monster();
};

