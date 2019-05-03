#pragma once
#include <string>
#include <Color.hpp>
class Effect
{
private :
	std::string name;
	std::string description;
	int strength;
	sf::Color color;
public:
	Effect();
	~Effect();
};

