#pragma once
#include <SFML\Graphics.hpp>
class Character
{
private:
	const float moveSpeed = 0.2;
	int level;
	int currentLife;
	int specialEffect;//TODO Enum
	int maxLife;
	int strength;
	sf::Image image;
	sf::Sprite sprite;
	sf::Texture texture;
	void move(sf::Vector2f distance);

	bool isJumping = false;
public:
	void drawTo(sf::RenderWindow &window);
	void setPos(sf::Vector2f newPos);
	sf::Vector2f getPos() { return sprite.getPosition(); };
	int attack();
	void jump();
	void moveLeft();
	void moveRight();
	void jumpRight();
	void jumpLeft();
	void moveGravity(float gravitySpeed);
	bool changeWeapon();
	bool loselife(int life);
	bool getIsJumping() { return isJumping; };
	void setIsJumping(bool jump) { isJumping = jump; };
	int getY();
	Character(sf::Vector2f scale);
	~Character();
};

