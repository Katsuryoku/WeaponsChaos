#pragma once
#include <string>
#include "Effect.h"
class Nature
{
private :
	std::string name;
	std::string bonus;
	Effect effect;
public:
	Nature();
	~Nature();
};

