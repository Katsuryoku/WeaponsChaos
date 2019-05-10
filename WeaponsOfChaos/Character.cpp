#include "stdafx.h"
#include "Character.h"


Character::Character()
{
}


Character::~Character()
{
}

void Character::setPos(sf::Vector2f newPos)
{
}

void Character::drawTo(sf::RenderWindow & window)
{
}

int Character::attack()
{
	return 0;
}

int Character::jump()
{
	return 0;
}

bool Character::moveleft()
{
	return false;
}

bool Character::moveRight()
{
	return false;
}

bool Character::changeWeapon()
{
	return false;
}

bool Character::loselife(int life)
{
	currentLife -= life;
	if (currentLife <= 0) {
		return false;
	}
	else {
		return true;
	}
}
