#include "analyse.h"
#include <iostream>
#include <fstream>
using namespace std;

Analyse::Analyse()
{

}


Mat Analyse::getImage(string s){

    Mat image;
    image = imread(s, CV_LOAD_IMAGE_COLOR);
    return image;
}

Mat Analyse::extract(Mat m){

    Mat m1;
    Mat m2;
    m.copyTo(m2);
    cvtColor(m2,m1,CV_BGR2GRAY);
    GaussianBlur( m1, m1, Size(7, 7), 2, 2);
    Canny(m1,m1,0,30);

    morphologyEx(m1, m1,MORPH_CLOSE,getStructuringElement(MORPH_ELLIPSE,cv::Size(5,5)), cv::Point(-1,-1),5,BORDER_CONSTANT,0);
    vector<Vec4i> hierarchy;
    vector<vector<Point> > contours;
    findContours( m1, contours,hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    Mat drawing = Mat::zeros( m1.size(), CV_8UC3 );

        for( int idx = 0; idx >= 0; idx = hierarchy[idx][0] )
        {
            Scalar color( rand()&255, rand()&255, rand()&255 );
            drawContours(drawing, contours, idx, color, CV_FILLED);
        }


        int r = drawing.rows;
        int c = drawing.cols;

        for(int i = 0;i<r;i++){
            for(int j = 0;j<c;j++){
                if(drawing.at<Vec3b>(i,j).val[0]==0 && drawing.at<Vec3b>(i,j).val[1]==0 && drawing.at<Vec3b>(i,j).val[2]==0){
                    m2.at<Vec3b>(i,j).val[0]=0;
                    m2.at<Vec3b>(i,j).val[1]=0;
                    m2.at<Vec3b>(i,j).val[2]=0;
                }
            }
        }

        return m2;
}





Mat Analyse::getSkin(Mat m){


    int Y_MIN  = 0;
    int Y_MAX  = 255;
    int Cr_MIN = 133;
    int Cr_MAX = 173;
    int Cb_MIN = 77;
    int Cb_MAX = 127;

    cv::Mat skin;
    //first convert our RGB image to YCrCb
    cv::cvtColor(m,skin,cv::COLOR_BGR2YCrCb);

    //uncomment the following line to see the image in YCrCb Color Space
    //cv::imshow("YCrCb Color Space",skin);

    //filter the image in YCrCb color space
    cv::inRange(skin,cv::Scalar(Y_MIN,Cr_MIN,Cb_MIN),cv::Scalar(Y_MAX,Cr_MAX,Cb_MAX),skin);

    return skin;


}


vector<float> Analyse::hog(Mat m,string s){


    if (s=="hsv"){
        cv::cvtColor(m,m,cv::COLOR_BGR2HSV);
    }
    HOGDescriptor a;
    std::vector< float > v ;

    a.compute(m,v);
    std::vector<float> f = std::vector<float>(9,0);
    for(int i =0 ; i<int((v.size()/9));i++){
        for(int j =0;j<9;j++){
            f[j]=f[j]+v[9*i+j];
        }
    } //somme les HOG de chaque fenêtre étudiée

    for(int j =0;j<9;j++){  //on normalise
        f[j]=f[j]/(v.size()/9);
    }


    if (s=="hsv"){
        cv::cvtColor(m,m,cv::COLOR_HSV2BGR);
    }
    return f;

}

vector<float> Analyse::lbp(Mat m,string s){



        Mat img_gray;
        Mat img_dst(m.rows-2, m.cols-2, CV_8UC1);

        if(s=="hsv"){
            cv::cvtColor(m,m,cv::COLOR_BGR2HSV);
        }
        cvtColor(m, img_gray, CV_BGR2GRAY);
        for(int i=1;i<img_gray.rows-1;i++)
        {
            for(int j=1;j<img_gray.cols-1;j++)
            {
                unsigned char center = img_gray.at<uchar>(i,j);
                unsigned char code = 0;
                code |= (img_gray.at<uchar>(i-1,j-1) > center) << 7;
                code |= (img_gray.at<uchar>(i-1,j) > center) << 6;
                code |= (img_gray.at<uchar>(i-1,j+1) > center) << 5;
                code |= (img_gray.at<uchar>(i,j+1) > center) << 4;
                code |= (img_gray.at<uchar>(i+1,j+1) > center) << 3;
                code |= (img_gray.at<uchar>(i+1,j) > center) << 2;
                code |= (img_gray.at<uchar>(i+1,j-1) > center) << 1;
                code |= (img_gray.at<uchar>(i,j-1) > center) << 0;
                img_dst.at<unsigned char>(i-1,j-1) = code;
            }
        }
        std::vector<float> f = std::vector<float>(256,0);
        int r =img_dst.rows;
        int c =img_dst.cols;
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                f[img_dst.at<uchar>(i,j)-1]++;
            }
        }

        if (s=="hsv"){
            cv::cvtColor(m,m,cv::COLOR_HSV2BGR);
        }

        return f;

}

float Analyse::eccentricity(Mat m){

    Mat m1;
    cvtColor(m,m1,CV_BGR2GRAY);
    vector<Vec4i> hierarchy;
    vector<vector<Point> > contours;
    findContours( m, contours,hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );


    RotatedRect r = fitEllipse(contours);
    float M = r.size.width;
    float M2 = r.size.height;

    float mini = min(M,M2);
    float maxi = max(M,M2);


    return sqrt(1-(mini/maxi)*(mini/maxi));



}

float Analyse::convex(Mat m){

    Mat m1;
    cvtColor(m,m1,CV_BGR2GRAY);
    vector<Vec4i> hierarchy;
    vector<vector<Point> > contours;
    findContours( m, contours,hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

    Mat m2;

    convexHull(contours,m2);
    return float(contourArea(contours))/contourArea(m2);

}


Mat Analyse::train(string s){




    std::string path1 = "D:/pro/Weapon chaos/BDD";
    string png = ".png";
    string p1 = "/apple/apple_";
    string p2 = "/ball/ball_";
    string p3 = "/banana/banana_";
    string p4 = "/bottle/bottle_";
    string p5 = "/broom/broom_";
    string p6 = "/car/car_";
    string p7 = "/cat/cat_";
    string p8 = "/flute/flute_";
    string p9 = "/fork/fork_";
    string p10 = "/glasses/glasses_";
    string p11= "/glue/glue_";
    string p12 = "/hammer/hammer_";
    string p13= "/key/key_";
    string p14 = "/knife/knife_";
    string p15 = "/mouse/mouse_";
    string p16 = "/pillow/pillow_";
    string p17 = "/plate/plate_";
    string p18 = "/potato/potato_";
    string p19 = "/racket/racket_";
    string p20= "/screwdriver/screwdriver_";

    for (int j= 1 ; j<21 ; j++){
        for(int i = 1 ; i <=15; i++){

            string name;
            if(j==1){
                name = path1+p1+std::to_string(i)+png;}
            else if(j==2){
                name = path1+p2+std::to_string(i)+png;
            }
            else if(j==3){
                name = path1+p3+std::to_string(i)+png;
            }
            else if(j==4){
                name = path1+p4+std::to_string(i)+png;
            }
            else if(j==5){
                name = path1+p5+std::to_string(i)+png;
            }
            else if(j==6){
                name = path1+p6+std::to_string(i)+png;
            }
            else if(j==7){
                name = path1+p7+std::to_string(i)+png;
            }
            else if(j==8){
                name = path1+p8+std::to_string(i)+png;
            }
            else if(j==9){
                name = path1+p9+std::to_string(i)+png;
            }
            else if(j==10){
                name = path1+p10+std::to_string(i)+png;
            }
            else if(j==11){
                name = path1+p11+std::to_string(i)+png;
            }
            else if(j==12){
                name = path1+p12+std::to_string(i)+png;
            }
            else if(j==13){
                name = path1+p13+std::to_string(i)+png;
            }
            else if(j==14){
                name = path1+p14+std::to_string(i)+png;
            }
            else if(j==15){
                name = path1+p15+std::to_string(i)+png;
            }
            else if(j==16){
                name = path1+p16+std::to_string(i)+png;
            }
            else if(j==17){
                name = path1+p17+std::to_string(i)+png;
            }
            else if(j==18){
                name = path1+p18+std::to_string(i)+png;
            }
            else if(j==19){
                name = path1+p19+std::to_string(i)+png;
            }
            else {
                name = path1+p20+std::to_string(i)+png;
            }
            cv::Mat m = getImage(name);
            cv::Mat mask;
            mask=extract(m);

            vector<float> v;
            vector<float> v2;
            if(s=="hsv"){
                v = hog(mask,"hsv");
                v2 = lbp(mask,"hsv");
            }
            else{
                v = hog(mask,"bgr");
                v2 = lbp(mask,"bgr");
            }

            float ecce = eccentricity(mask);
            float conv = convex(mask);

            vector<float> data = vector<float>(267,0);
            data[0]=ecce;
            data[1]=conv;
            for(int i = 0;i<9;i++){
                data[2+i]=v[i];
            }
            for(int j = 0;j<256;j++){
                data[11+j]=v2[j];
            }

        }
    }




}
