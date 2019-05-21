#pragma once

#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;
class Plateform
{
private:
	// ces coordonn�s sont selon le repre de la fenetre (0 0 en haut � gauche)
	int height_;
	int beginning_;
	int length_;

public:
	Plateform(int height, int begin, int length); // ces coordonn�s sont selon le repere image (0 0 en bas � gauche)
	~Plateform();
	void drawTo(sf::RenderWindow &window);
	int getLength();
	int getBeginning();
	int getHeight();
};

