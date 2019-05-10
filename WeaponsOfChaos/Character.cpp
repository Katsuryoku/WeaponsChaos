#include "stdafx.h"
#include "Character.h"


Character::Character()
{
	if (!image.loadFromFile("D:/Cworkspace/WeaponsOfChaos/WeaponsOfChaos/test.png") )// Si le chargement du fichier a échoué
	{

	}
	else // Si le chargement de l'image a réussi
	{
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}

}


Character::~Character()
{
}

void Character::setPos(sf::Vector2f newPos)
{
	sprite.setPosition(newPos);
}

void Character::drawTo(sf::RenderWindow & window)
{
	window.draw(sprite);
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
