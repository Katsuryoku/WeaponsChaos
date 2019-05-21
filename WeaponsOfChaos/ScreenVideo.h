#pragma once

#include "opencv2/opencv.hpp"

using namespace cv;

class ScreenVideo
{
	VideoCapture cap= VideoCapture(0);
	Mat launchVideo();
public:
	ScreenVideo();
	~ScreenVideo();
};

