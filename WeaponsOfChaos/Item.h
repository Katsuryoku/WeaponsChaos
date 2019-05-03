#pragma once
#include <string>
class Item
{
private :
	int price;
	int name;
	std::string description;
	int boost; // b*attribut
	std::string boostedAttribut; // Wich attribut of Character is boosted
public:
	Item();
	~Item();
};

