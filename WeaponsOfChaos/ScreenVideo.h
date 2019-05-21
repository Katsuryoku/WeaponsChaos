#pragma once

#include "opencv2/opencv.hpp"

using namespace cv;

class ScreenVideo
{
	VideoCapture cap;
public:
	Mat launchVideo();
	ScreenVideo();
	~ScreenVideo();
};

