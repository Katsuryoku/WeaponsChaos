#pragma once
#include <SFML\Graphics.hpp>
class Character
{
private:
	sf::Vector2f position;
	int level;
	int currentLife;
	int specialEffect;//TODO Enum
	int maxLife;
	int strength;
	sf::Image image;
	sf::Sprite sprite;
	sf::Texture texture;
public:
	void drawTo(sf::RenderWindow &window);
	void setPos(sf::Vector2f newPos);
	int attack();
	int jump();
	bool moveleft();
	bool moveRight();
	bool changeWeapon();
	bool loselife(int life);
	Character();
	~Character();
};

