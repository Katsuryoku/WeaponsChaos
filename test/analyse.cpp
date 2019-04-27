#include "analyse.h"

Analyse::Analyse()
{

}


Mat Analyse::getImage(string s){

    Mat image;
    image = imread(s, CV_LOAD_IMAGE_COLOR);
    return image;
}
