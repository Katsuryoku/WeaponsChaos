#ifndef ANALYSE_H
#define ANALYSE_H

#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

class Analyse
{
public:
    Analyse();
    void apprentissage();
    Mat getImage(string s);
    Mat extract(Mat m);
    void classer();
    void calculCarac();
    void giveClass();
    Mat getSkin(Mat m);
    vector<float> hog(Mat m,string s);
    vector<float> lbp(Mat m,string s);
    float eccentricity(Mat m);
    float convex(Mat m);

};

#endif // ANALYSE_H
