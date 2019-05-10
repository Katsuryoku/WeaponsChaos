#pragma once
#include "Monster.h"
#include <SFML\Graphics.hpp>
class Slime :
	public Monster
{
private :
	sf::Image slimeImage;
public:
	Slime();
	~Slime();
};

