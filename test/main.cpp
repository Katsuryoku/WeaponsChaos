#include <iostream>
#include "analyse.h"

using namespace std;

int main()
{
    Analyse b = Analyse();
    Mat m = b.getImage("D:/pro/Weapons chaos/test_knife_1.png");
    Mat mg;
    Mat s;
    Mat s2;
    Mat s3;
    cvtColor(m,mg,CV_RGB2GRAY);
    Canny(mg,s,50,200);
    dilate(s, s, cv::Mat(), cv::Point(-1,-1));
    vector<Vec4i> hierarchy;
    vector<vector<Point> > contours;
    findContours( s, contours,hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    Mat drawing = Mat::zeros( mg.size(), CV_8UC3 );
    int idx = 0;
        for( ; idx >= 0; idx = hierarchy[idx][0] )
        {
            Scalar color( rand()&255, rand()&255, rand()&255 );
            drawContours(drawing, contours, idx, color, CV_FILLED);
        }




    imshow( "Display window", drawing );                   // Show our image inside it.
    waitKey(0);
    return 0;
}
