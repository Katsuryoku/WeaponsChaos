#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Level.h"

int dede()
{
	sf::RenderWindow window(sf::VideoMode(900, 900), "SFML works!");

	while (window.isOpen())
	{
		Level* current = new Level;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		current->drawTo(window);
		window.display();
	}

	return 0;
}