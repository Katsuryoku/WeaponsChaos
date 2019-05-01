#include <iostream>
#include "analyse.h"


using namespace std;

int main()
{
    Analyse b = Analyse();
    cv::Mat m = b.getImage("D:/pro/Weapons chaos/test_screwdriver_2.png");
    //Canny(m,m,0,80);
    cv::Mat mask;
    mask=b.extract(m);





    vector<float> v = b.hog(m,"hsv");
    vector<float> v2 = b.hog(m,"bgr");

    vector<float> v3 = b.lbp(m,"hsv");
    vector<float> v4 = b.lbp(m,"bgr");

    imshow( "Display window", mask );                   // Show our image inside it.
    waitKey(0);
    return 0;
}
