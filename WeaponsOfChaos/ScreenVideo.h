#pragma once

#include "opencv2/opencv.hpp"

using namespace cv;

class ScreenVideo
{
	VideoCapture cap(0);
	Mat launchVideo();
public:
	ScreenVideo();
	~ScreenVideo();
};

