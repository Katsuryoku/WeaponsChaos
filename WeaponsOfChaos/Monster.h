#pragma once
#include <SFML\Graphics.hpp>
#include "Nature.h"
#include "State.h"
#include <math.h>       /* atan2 */
class Monster
{
private :
	float moveSpeed = 0.2;
	int level;
	int currentLife;
	State state;
	int maxLife;
	int strength;
	Nature nature;
	sf::Image image;
	sf::Sprite sprite;
	sf::Texture texture;
	void move(sf::Vector2f distance);
	bool isJumping = false;
public:
	void drawTo(sf::RenderWindow &window);
	int attack();
	void jump();
	void moveLeft();
	void moveRight();
	void jumpRight();
	void jumpLeft();
	void moveToPlayer(sf::Vector2f playerPosition);
	void moveToPlayerX(sf::Vector2f playerPosition);
	bool generate();
	void setMoveSpeed(float mSpeed) { moveSpeed = mSpeed; };
	sf::Vector2f getPosition() { return sprite.getPosition(); };
	void setPosition(sf::Vector2f pos) { sprite.setPosition(pos); };
	bool loselife(int life);
	Monster(sf::Vector2f pos, int lvl, Nature nat, int mL, int s);
	Monster(sf::Vector2f pos, sf::Vector2f scale);
	Monster();
	~Monster();
};

