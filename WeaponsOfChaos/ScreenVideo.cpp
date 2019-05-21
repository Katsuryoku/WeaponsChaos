#include "stdafx.h"
#include "ScreenVideo.h"


ScreenVideo::ScreenVideo()
{
	cv::VideoCapture cap(0); // open the video file for reading
	if (!cap.isOpened())
	{
		return 0;
	}

	sf::RenderWindow window(sf::VideoMode(1200, 900), "RenderWindow");
	cv::Mat frameRGB, frameRGBA;
	sf::Image image;
	sf::Texture texture;
	sf::Event event;
	sf::Sprite sprite;

	while (window.isOpen())
	{
		cap >> frameRGB;

		if (frameRGB.empty())
		{
			break;
		}

		cv::cvtColor(frameRGB, frameRGBA, cv::COLOR_BGR2RGBA);

		image.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr());

		if (!texture.loadFromImage(image))
		{
			break;
		}

		sprite.setTexture(texture);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.draw(sprite);
		window.display();
	}
}


ScreenVideo::~ScreenVideo()
{
}
