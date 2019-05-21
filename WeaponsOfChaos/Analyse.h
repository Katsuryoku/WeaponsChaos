#pragma once


#ifndef ANALYSE_H
#define ANALYSE_H

#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>


#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/ml/ml.hpp"
#include <limits.h>
#include <map>
#include <string>
#include <iostream>


using namespace cv;
using namespace std;
using namespace ml;

class Analyse
{
public:
	
	cv::ml::KNearest*  kNearest;

	Analyse();
	//void apprentissage();
	Mat getImage(string s);
	Mat extract(Mat m);
	//void classer();
	//void calculCarac();
	String getColorType(Mat image);
	int giveClass2(string s,Mat e, Mat m);
	int giveClass1(string s,string name,Mat m);
	vector<int> giveClass(string s2,int z,Mat m);
	Mat getData(string s, ifstream& fichier);
	Mat getSkin(Mat m);
	vector<float> hog(Mat m, string s);
	vector<float> lbp(Mat m, string s);
	float eccentricity(Mat m);
	float convex(Mat m);
	void train(string s, ofstream& fichier);


};

#endif // ANALYSE_H
