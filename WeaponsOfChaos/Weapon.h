#pragma once
#include <string>
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

