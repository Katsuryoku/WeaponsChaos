#pragma once
#include <SFML\Graphics.hpp>
class Shop
{
private :
	sf::Image image;
	sf::Sprite shop;
public:
	void refresh();
	void choseItem();
	void addItem();
	void unavailableItem(int item); // When player had already buy a item or don't have money to buy it.
	void availableItem(int item); // When player can buy a item.
	void drawTo(sf::RenderWindow &window);
	void setPos(sf::Vector2f newPos);
	Shop(sf::Vector2f size);
	~Shop();
};

