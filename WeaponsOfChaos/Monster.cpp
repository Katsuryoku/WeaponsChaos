#include "stdafx.h"
#include "Monster.h"


int Monster::attack()
{
	return strength*level+ rand() % 100;
}

bool Monster::moveleft()
{
	return false;
}

bool Monster::moveRight()
{
	return false;
}

bool Monster::generate()
{
	return false;
}
// if monster die return true, else return false
bool Monster::loselife(int life)
{
	currentLife = currentLife - life;
	if (currentLife < 0) {
		return true;
	}
	else {
		return false;
	}
}

Monster::Monster(sf::Vector2f pos, int lvl, int sE, int mL, int s)
{
	position = pos;
	level = lvl;
	currentLife = mL;
	specialEffect = sE;
	maxLife = mL;
	strength = s;
}

Monster::Monster()
{
	position = sf::Vector2f(0,0);
	level = 1;
	currentLife = 10;
	specialEffect = 0;
	maxLife = 10;
	strength = 1;
}


Monster::~Monster()
{
}
