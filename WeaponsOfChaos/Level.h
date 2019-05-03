#pragma once
#include <string>
#include <array> 
#include "Monster.h"
#include "Coin.h"
class Level
{
private:
	std::string name;
	int level;
	int numberOfMonsters =1;
	int numberOfCoins;
	int wave;
	int numberMaxOfChests;
	int numberOfPlatforms;
	int numberOfDoors;
	std::string description;
	Monster MonstersArray[1] = {};
	Coin CoinsArray[1] = {};
public:
	Level();
	~Level();
};

