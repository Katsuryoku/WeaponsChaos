#include "analyse.h"

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
