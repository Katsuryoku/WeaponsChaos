
#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Menu.h"
#include "Character.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(900, 900), "SFML WORK!");

	Menu menu(window.getSize().x, window.getSize().y,5);

	Character playr(sf::Vector2f(1.0f, 1.0f));
	const int groundHeight = 700;
	const float gravitySpeed = 0.3;
	bool game = false;
	bool chargeWindow = false;
	bool natureWindow = false;
	bool optionWindow = false;
	while (window.isOpen())
	{
		sf::Event event;
		if (game) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				playr.jumpRight();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				playr.jumpLeft();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				playr.jump();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				playr.moveRight();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				playr.moveLeft();
			}
		}
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::N:
					if(game)
						
				case sf::Keyboard::Up:
					if(menu.getInMenu())
						menu.MoveUp();
					break;
				case sf::Event::KeyReleased:
					if (game)
						playr.setIsJumping(false);
					break;
				case sf::Keyboard::Down:
					if (menu.getInMenu())
						menu.MoveDown();
					break;
				case sf::Keyboard::Escape:
					if (!menu.getInMenu())
					{
						menu.setInMenu(true);
						game = false;
					};
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
		if (game)
		{
			if (playr.getY() < groundHeight && playr.getIsJumping() == false) {
				playr.moveGravity(gravitySpeed);
			}
			playr.drawTo(window);
		}
		window.display();
	}
}