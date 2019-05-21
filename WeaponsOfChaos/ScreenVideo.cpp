#include "stdafx.h"
#include "ScreenVideo.h"


Mat ScreenVideo::launchVideo()
{
	if (!cap.isOpened())
	{
		return Mat(cv::Size(1,1),1);
	}
	cv::Mat rend;
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
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					rend = Mat(cv::Size(1, 1), 1);
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.draw(sprite);
		window.display();
	}
	return Mat();
}

ScreenVideo::ScreenVideo()
{
	
}




ScreenVideo::~ScreenVideo()
{
}
