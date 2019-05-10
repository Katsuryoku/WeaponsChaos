#pragma once
#include <string>
#include <SFML\Graphics.hpp>
class Item
{
private :
	sf::Image image;
	sf::Sprite sprite;
	int price;
	int name;
	std::string description;
	int boost; // b*attribut
	std::string boostedAttribut; // Wich attribut of Character is boosted
public:
	Item();
	~Item();
};

