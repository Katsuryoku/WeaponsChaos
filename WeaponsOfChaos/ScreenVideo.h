#pragma once

#include "opencv2/opencv.hpp"

using namespace cv;

class ScreenVideo
{
private:
	VideoCapture cap= VideoCapture(0);
	bool isScreen = false;
	cv::Mat frameRGB;
	cv::Mat frame;
	sf::Sprite sprite;
	sf::Sprite zoneSprite;
	cv::Mat frameRGBA;
	sf::Image zoneImage;
	sf::Texture zoneTexture;
	sf::Image image;
	sf::Texture texture;
	cv::Mat zoneFrame;
	cv::Mat zoneFrameRGBA;
	bool isZoneRight = false;
	bool zone = false;
public:
	bool getIsScreen() { return isScreen; }
	void setIsScreen(bool menu) { isScreen = menu; }
	bool getZone() { return zone; }
	void setZone(bool menu) { zone = menu; }
	bool getIsZoneRight() { return isZoneRight; }
	void setIsZoneRight(bool menu) { isZoneRight = menu; }
	Mat captureImage();
	void closeCam();
	ScreenVideo();
	bool takeVideo();
	void drawTo(sf::RenderWindow & window);
	~ScreenVideo();
};

