#include "stdafx.h"
#include "ScreenVideo.h"
#include <iostream>

bool ScreenVideo::takeVideo()
{

	if (!cap.isOpened())
	{
		cap= VideoCapture(0);
	}
	cap >> frameRGB;
	if (frameRGB.empty())
		{
			std::cout << "cap empty";
			return false;
		}
	if (zone) {
		int W, H;
		Point p1, p2;
		if (frameRGB.cols < 3 * frameRGB.rows) {
			W = frameRGB.cols / 3;
			H = frameRGB.cols / 3;
		}
		if (isZoneRight) {
			p1 = Point(frameRGB.cols - W - 10, 10);
			p2 = Point(frameRGB.cols - 10, 10 + H);
		}
		else {
			p1 = Point(10, 10);
			p2 = Point(10 + W, 10 + H);
		}

		zoneFrame = frameRGB(Range(p1.y, p2.y), Range(p1.x, p2.x));
		cv::cvtColor(zoneFrame, zoneFrameRGBA, cv::COLOR_BGR2RGBA);
		zoneImage.create(zoneFrameRGBA.cols, zoneFrameRGBA.rows, zoneFrameRGBA.ptr());
		if (!zoneTexture.loadFromImage(zoneImage))
		{
			std::cout << "image crash";
			return false;
		}

		zoneSprite.setTexture(zoneTexture);
	}
	else {
		frame = frameRGB;
		cv::cvtColor(frame, frameRGBA, cv::COLOR_BGR2RGBA);
		image.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr()); 
		if (!texture.loadFromImage(image))
		{
			std::cout << "image crash";
			return false;
		}

		sprite.setTexture(texture);
	}
	
	}
void ScreenVideo::drawTo(sf::RenderWindow & window)
{
	if (zone) {
		window.draw(zoneSprite);
	}
	else {
		window.draw(sprite);
	}
}
Mat ScreenVideo::captureImage() {
	if (zone) {
		return zoneFrame;
	}
	else {
		return frame;
	}
}
void ScreenVideo::closeCam() {
	cap.release();
	zone = false;
	isZoneRight = false;
}
ScreenVideo::ScreenVideo()
{
	
}




ScreenVideo::~ScreenVideo()
{
}
