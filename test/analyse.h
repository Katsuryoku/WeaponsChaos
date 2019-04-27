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
    void extract();
    void classer();
    void calculCarac();
    void giveClass();
};

#endif // ANALYSE_H
