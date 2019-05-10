#pragma once
#include <Vector2.hpp>

#include <SFML\Graphics.hpp>
class Coin
{
private :
	sf::Vector2f position;
	sf::Image image;
	sf::Sprite sprite;
	int value;
public:
	Coin();
	~Coin();
};

