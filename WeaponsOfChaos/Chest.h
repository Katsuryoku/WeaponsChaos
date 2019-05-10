#pragma once

#include <SFML\Graphics.hpp>
class Chest
{
private:
	sf::Image image;
	sf::Sprite sprite;
	int value;
public:
	Chest();
	~Chest();
};

