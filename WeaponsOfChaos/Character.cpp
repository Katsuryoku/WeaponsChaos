#include "stdafx.h"
#include "Character.h"


int Character::getY()
{
		return sprite.getPosition().y;

}

Character::Character(sf::Vector2f scale)
{
	if (!image.loadFromFile("D:/Cworkspace/WeaponsOfChaos/WeaponsOfChaos/test.png") )// Si le chargement du fichier a échoué
	{

	}
	else // Si le chargement de l'image a réussi
	{
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setScale(scale);
	}

}


Character::~Character()
{
}

void Character::setPos(sf::Vector2f newPos)
{
	sprite.setPosition(newPos);
}

void Character::move(sf::Vector2f distance)
{
	sprite.move(distance);
}

void Character::drawTo(sf::RenderWindow & window)
{
	window.draw(sprite);
}

int Character::attack()
{
	return 0;
}

void Character::jump()
{
	move({ 0, -moveSpeed });
	isJumping = true;
}

void Character::moveLeft()
{
	move({ -moveSpeed, 0 });
}

void Character::moveRight()
{
	move({ moveSpeed, 0 });
}

void Character::jumpLeft()
{
	move({ -moveSpeed, -moveSpeed });
	isJumping = true;
}

void Character::jumpRight()
{
	move({ moveSpeed, -moveSpeed });
	isJumping = true;
}

void Character::moveGravity(float gravitySpeed)
{
	move({ 0,gravitySpeed });
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
