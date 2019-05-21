#pragma once
#include <string>
#include <SFML\Graphics.hpp>
class Weapon
{
private :
	int strength;
	std::string name;
	int range;
	float attackAngle;
public:
	bool attack();
	Weapon();
	~Weapon();
};

