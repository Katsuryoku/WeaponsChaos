#pragma once
#include <string>
#include <array> 
#include "Monster.h"
#include "Coin.h"
#include "Ground.h"

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
	list<Coin*> CoinsArray;
	Ground* ground;
public:
	Level();
	~Level();
	void drawTo(sf::RenderWindow &window);
	void generateCoins(int n);
};

