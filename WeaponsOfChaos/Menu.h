#pragma once

#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 5

class Menu
{
public:
	Menu(float width, float height,int maxNumberItems);
	~Menu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }
	bool getInMenu() { return inMenu; }
	void setInMenu(bool menu) { inMenu = menu; }
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	bool inMenu = true;
};

