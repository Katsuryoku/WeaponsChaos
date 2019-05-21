#include "stdafx.h"
#include "Monster.h"
#include <cmath>       /* atan2 */

void Monster::move(sf::Vector2f distance)
{
	sprite.move(distance);
}

void Monster::drawTo(sf::RenderWindow & window)
{
	window.draw(sprite);
}

int Monster::attack()
{
	return strength*level+ rand() % 100;
}

void Monster::jump()
{
	move({ 0, -moveSpeed });
	isJumping = true;
}

void Monster::moveLeft()
{
	move({ -moveSpeed, 0 });
}

void Monster::moveRight()
{

	move({ moveSpeed, 0 });
}

void Monster::jumpRight()
{
	move({ moveSpeed, -moveSpeed });
	isJumping = true;
}

void Monster::jumpLeft()
{
	move({ -moveSpeed, -moveSpeed });
	isJumping = true;
}

void Monster::moveToPlayer(sf::Vector2f playerPosition)
{
	float ay = playerPosition.y - sprite.getPosition().y;
	float ax = playerPosition.x - sprite.getPosition().x;
	// angle (in radians) between monster and player
	float angle = 0;
	if (ay*ax < 0) {
		angle = atan2(ay, ax);
	}
	else {
		angle = atan2(ay,	ax);
	}
	// monster.speed is the amount of pixels to move
	// If this doesn't work, invert cos for x and sin for y
	
	float monsterX = sin(angle) * moveSpeed;
	float monsterY = cos(angle) * moveSpeed;
	move({ -monsterX, -monsterY });
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

Monster::Monster(sf::Vector2f pos, int lvl, Nature nat, int mL, int s)
{
	sprite.setPosition(pos);
	level = lvl;
	currentLife = mL;
	nature = nat;
	maxLife = mL;
	strength = s;
}

Monster::Monster(sf::Vector2f pos, sf::Vector2f scale)
{
	if (!image.loadFromFile("slime_sleep.png"))// Si le chargement du fichier a échoué
	{

	}
	else // Si le chargement de l'image a réussi
	{
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setScale(scale);
	}
	sprite.setPosition(pos);
	level = 1;
	currentLife = 10;
	maxLife = 10;
	strength = 1;
}

Monster::Monster()
{
}


Monster::~Monster()
{
}
