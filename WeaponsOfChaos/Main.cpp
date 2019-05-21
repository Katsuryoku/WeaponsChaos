
#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Menu.h"
#include "Character.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML WORK!");

	Menu menu(window.getSize().x, window.getSize().y,5);

	Character playr(sf::Vector2f(1.0f, 1.0f));
	bool game = false;
	bool chargeWindow = false;
	bool natureWindow = false;
	bool optionWindow = false;
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if(menu.getInMenu())
						menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					if (menu.getInMenu())
						menu.MoveDown();
					break;

				case sf::Keyboard::Escape:
					if (!menu.getInMenu())
						menu.setInMenu(true);
					break;
				case sf::Keyboard::Return:
					if (menu.getInMenu())
						switch (menu.GetPressedItem())
						{
						case 0:
							std::cout << "Play button has been pressed" << std::endl;
							game = true;
							menu.setInMenu(false);
							break;
						case 1:
							std::cout << "Charge weapon button has been pressed" << std::endl;
							chargeWindow = true;
							menu.setInMenu(false);
							break;
						case 2:
							std::cout << "Change nature button has been pressed" << std::endl;
							natureWindow = true;
							menu.setInMenu(false);
							break;
						case 3:
							std::cout << "Option button has been pressed" << std::endl;
							optionWindow = true;
							menu.setInMenu(false);
							break;
						case 4:
							window.close();
							break;
						}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}

		window.clear();

		if (menu.getInMenu())
			menu.draw(window);

		window.display();
	}
}