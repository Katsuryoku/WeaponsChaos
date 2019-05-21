#include "stdafx.h"
#include "Plateform.h"


Plateform::Plateform(int height, int beginning, int length)
{
	this->height_ = 700 - height;
	this->beginning_ = beginning;
	this->length_ = length;

}


Plateform::~Plateform()
{
}

void Plateform::drawTo(sf::RenderWindow &window)
{
	RectangleShape rectangle(Vector2f(this->length_, 5));
	rectangle.setPosition(Vector2f(this->beginning_, this->height_));
	window.draw(rectangle);

}

int Plateform::getLength()
{
	return this->length_;
}

int Plateform::getBeginning()
{
	return this->beginning_;
}

int Plateform::getHeight()
{
	return this->height_;
}
