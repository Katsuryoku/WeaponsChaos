#include "analyse.h"

#include "opencv2/opencv.hpp"

#include <string>
#include <fstream>


#include "pch.h"

using namespace std;
using namespace cv;


Analyse::Analyse()
{
	kNearest = ml::KNearest::create();
}


Mat Analyse::getImage(string s) {

	Mat image;
	image = imread(s, IMREAD_COLOR);
	return image;
}

Mat Analyse::extract(Mat m) {

	Mat m1;
	Mat m2;
	m.copyTo(m2);
	cvtColor(m2, m1, COLOR_BGR2GRAY);
	GaussianBlur(m1, m1, Size(7, 7), 2, 2);
	Canny(m1, m1, 0, 30);

	morphologyEx(m1, m1, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, cv::Size(5, 5)), cv::Point(-1, -1), 5, BORDER_CONSTANT, 0);
	vector<Vec4i> hierarchy;
	vector<vector<Point> > contours;
	findContours(m1, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	Mat drawing = Mat::zeros(m1.size(), CV_8UC3);

	for (int idx = 0; idx >= 0; idx = hierarchy[idx][0])
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		drawContours(drawing, contours, idx, color, FILLED);
	}


	int r = drawing.rows;
	int c = drawing.cols;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (drawing.at<Vec3b>(i, j).val[0] == 0 && drawing.at<Vec3b>(i, j).val[1] == 0 && drawing.at<Vec3b>(i, j).val[2] == 0) {
				m2.at<Vec3b>(i, j).val[0] = 0;
				m2.at<Vec3b>(i, j).val[1] = 0;
				m2.at<Vec3b>(i, j).val[2] = 0;
			}
		}
	}

	return m2;
}





Mat Analyse::getSkin(Mat m) {


	int Y_MIN = 0;
	int Y_MAX = 255;
	int Cr_MIN = 133;
	int Cr_MAX = 173;
	int Cb_MIN = 77;
	int Cb_MAX = 127;

	cv::Mat skin;
	//first convert our RGB image to YCrCb
	cv::cvtColor(m, skin, cv::COLOR_BGR2YCrCb);

	//uncomment the following line to see the image in YCrCb Color Space
	//cv::imshow("YCrCb Color Space",skin);

	//filter the image in YCrCb color space
	cv::inRange(skin, cv::Scalar(Y_MIN, Cr_MIN, Cb_MIN), cv::Scalar(Y_MAX, Cr_MAX, Cb_MAX), skin);

	return skin;


}


vector<float> Analyse::hog(Mat m, string s) {


	if (s == "hsv") {
		cv::cvtColor(m, m, cv::COLOR_BGR2HSV);
	}
	HOGDescriptor a;
	std::vector< float > v;

	a.compute(m, v);
	std::vector<float> f = std::vector<float>(9, 0);
	
	for (int i = 0; i<int((v.size() / 9)); i++) {
		for (int j = 0; j < 9; j++) {
			f[j] = f[j] + v[9 * i + j];
		}
	} //somme les HOG de chaque fenêtre étudiée

	for (int j = 0; j < 9; j++) {  //on normalise
		f[j] = f[j] / (v.size() / 9);
	}


	if (s == "hsv") {
		cv::cvtColor(m, m, cv::COLOR_HSV2BGR);
	}
	return f;

}

vector<float> Analyse::lbp(Mat m, string s) {

	int size = m.size().height* m.size().width;

	Mat img_gray;
	Mat img_dst(m.rows - 2, m.cols - 2, CV_8UC1);

	if (s == "hsv") {
		cv::cvtColor(m, img_gray, cv::COLOR_BGR2HSV);
		for (int i = 1; i < img_gray.rows - 1; i++)
		{
			for (int j = 1; j < img_gray.cols - 1; j++)
			{
				unsigned char center = img_gray.at<uchar>(i, j);
				unsigned char code = 0;
				code |= (img_gray.at<Vec3b>(i - 1, j - 1).val[0] > center) << 7;
				code |= (img_gray.at<Vec3b>(i - 1, j).val[0] > center) << 6;
				code |= (img_gray.at<Vec3b>(i - 1, j + 1).val[0] > center) << 5;
				code |= (img_gray.at<Vec3b>(i, j + 1).val[0] > center) << 4;
				code |= (img_gray.at<Vec3b>(i + 1, j + 1).val[0] > center) << 3;
				code |= (img_gray.at<Vec3b>(i + 1, j).val[0] > center) << 2;
				code |= (img_gray.at<Vec3b>(i + 1, j - 1).val[0] > center) << 1;
				code |= (img_gray.at<Vec3b>(i, j - 1).val[0] > center) << 0;
				img_dst.at<uchar>(i - 1, j - 1) = code;
			}
		}
	}
	else {
		cvtColor(m, img_gray, COLOR_BGR2GRAY);
		for (int i = 1; i < img_gray.rows - 1; i++)
		{
			for (int j = 1; j < img_gray.cols - 1; j++)
			{
				unsigned char center = img_gray.at<uchar>(i, j);
				unsigned char code = 0;
				code |= (img_gray.at<uchar>(i - 1, j - 1) > center) << 7;
				code |= (img_gray.at<uchar>(i - 1, j) > center) << 6;
				code |= (img_gray.at<uchar>(i - 1, j + 1) > center) << 5;
				code |= (img_gray.at<uchar>(i, j + 1) > center) << 4;
				code |= (img_gray.at<uchar>(i + 1, j + 1) > center) << 3;
				code |= (img_gray.at<uchar>(i + 1, j) > center) << 2;
				code |= (img_gray.at<uchar>(i + 1, j - 1) > center) << 1;
				code |= (img_gray.at<uchar>(i, j - 1) > center) << 0;
				img_dst.at<uchar>(i - 1, j - 1) = code;
			}
		}

	}
	std::vector<float> f = std::vector<float>(256, 0);
	int r = img_dst.rows;
	int c = img_dst.cols;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			f[(img_dst.at<uchar>(i, j))%256]++;
		}
	}

	for (int i = 0; i < 256; i++) {
		f[i] = f[i] / size;
	}

	

	return f;

}

float Analyse::eccentricity(Mat m) {

	Mat m1;
	Mat m2;
	m.copyTo(m2);
	cvtColor(m2, m1, COLOR_BGR2GRAY);
	GaussianBlur(m1, m1, Size(7, 7), 2, 2);
	Canny(m1, m1, 0, 30);

	morphologyEx(m1, m1, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, cv::Size(5, 5)), cv::Point(-1, -1), 5, BORDER_CONSTANT, 0);
	vector<Vec4i> hierarchy;
	vector<vector<Point> > contours;

	/*Mat m1;
	cvtColor(m, m1, COLOR_BGR2GRAY);
	vector<Vec4i> hierarchy;
	vector<vector<Point> > contours;*/
	findContours(m1, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	int imax = 0;
	int maxi = contours[0].size();
	for (int i = 0; i < contours.size(); i++) {
		if (contours[i].size() > maxi) { imax = i; maxi = contours[i].size(); }
	}

	RotatedRect r = fitEllipse(contours[imax]);
	float M = r.size.width;
	float M2 = r.size.height;

	float minim = min(M, M2);
	float maxim = max(M, M2);


	return sqrt(1 - (minim / maxim)*(minim / maxim));

	return 0;

}

float Analyse::convex(Mat m) {

	Mat m1;
	Mat m2;
	m.copyTo(m2);
	cvtColor(m2, m1, COLOR_BGR2GRAY);
	GaussianBlur(m1, m1, Size(7, 7), 2, 2);
	Canny(m1, m1, 0, 30);

	morphologyEx(m1, m1, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, cv::Size(5, 5)), cv::Point(-1, -1), 5, BORDER_CONSTANT, 0);
	vector<Vec4i> hierarchy;
	vector<vector<Point> > contours;
	
	/*Mat m1;
	cvtColor(m, m1, COLOR_BGR2GRAY);
	vector<Vec4i> hierarchy;
	vector<vector<Point> > contours;*/
	findContours(m1, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	Mat m3;
	int imax = 0;
	int maxi = contours[0].size();
	for (int i = 0; i < contours.size(); i++) {
		if (contours[i].size() > maxi) { imax = i; maxi = contours[i].size(); }
	}

	convexHull(contours[imax], m3);
	return float(contourArea(contours[imax])) / contourArea(m3);

	return 0;

}




vector<int> Analyse::giveClass(string s2,int z, Mat m) {

	
	Mat vect(Mat_<float>(20 * 15, 267));
	
	for (int i = 0; i < 20 * 15; i++) {
		for (int j = 0; j < 267; j++) {
			
			
			if (true) {
				vect.at<float>(i, j) = m.at<float>(i,j);
			}
			else if (i>=5) {
				vect.at<float>(i, j) = m.at<float>(i+2, j);
			}
		}
		

	}

	Mat input(Mat_<float>(20, 267));
	for (int k = 0; k < 20; k++) {
		for (int i = 0; i < 267; i++) {
			input.at<float>(k, i) = vect.at<float>(k*15+z, i);
		}
	}

	Mat soluce(Mat_<float>(20*14,1));
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 14; j++) {
			soluce.at<float>(i*14+j) = i;
		}
	}

	Mat vect2(Mat_<float>(20 * 14, 267));
	int compteur = 14-z;
	for (int i = 0; i < 20 * 14; i++) {
		for (int j = 0; j < 267; j++) {
			
				vect2.at<float>(i, j) = vect.at<float>(i+int(compteur/14), j);
			
		}
		compteur++;

	}

	cv::Ptr<cv::ml::KNearest>  k(cv::ml::KNearest::create());

	k->train(vect2, cv::ml::ROW_SAMPLE,soluce);


	Mat sol;
	k->findNearest(input,5, sol);

	
	
	vector<int> v(sol);

	return v;
}



void Analyse::train(string s, ofstream& fichier) {


	
		

	string path1 = string("D:/pro/Weapons chaos/BDD/");
	string png = string(".png");
	string p1 = string("apple/apple_");
	string p2 = string("ball/ball_");
	string p3 = string("banana/banana_");
	string p4 = string("bottle/bottle_");
	string p5 = string("broom/broom_");
	string p6 = string("car/car_");
	string p7 = string("cat/cat_");
	string p8 = string("flute/flute_");
	string p9 = string("fork/fork_");
	string p10 = string("glasses/glasses_");
	string p11 = string("glue/glue_");
	string p12 = string("hammer/hammer_");
	string p13 = string("key/key_");
	string p14 = string("knife/knife_");
	string p15 = string("mouse/mouse_");
	string p16 = string("pillow/pillow_");
	string p17 = string("plate/plate_");
	string p18 = string("potato/potato_");
	string p19 = string("racket/racket_");
	string p20 = string("screwdriver/screwdriver_");
	
	for (int j = 1; j < 21; j++) {
		for (int i = 1; i <= 15; i++) {

			string name;
			if (j == 1) {
				name = path1 + p1 + std::to_string(i) + png;
			}
			else if (j == 2) {
				name = path1 + p2 + std::to_string(i) + png;
			}
			else if (j == 3) {
				name = path1 + p3 + std::to_string(i) + png;
			}
			else if (j == 4) {
				name = path1 + p4 + std::to_string(i) + png;
			}
			else if (j == 5) {
				name = path1 + p5 + std::to_string(i) + png;
				if(i>8){ name = path1 + p5 + std::to_string(8) + png; }
			}
			else if (j == 6) {
				name = path1 + p6 + std::to_string(i) + png;
			}
			else if (j == 7) {
				name = path1 + p7 + std::to_string(i) + png;
			}
			else if (j == 8) {
				name = path1 + p8 + std::to_string(i) + png;
			}
			else if (j == 9) {
				name = path1 + p9 + std::to_string(i) + png;
			}
			else if (j == 10) {
				name = path1 + p10 + std::to_string(i) + png;
			}
			else if (j == 11) {
				name = path1 + p11 + std::to_string(i) + png;
			}
			else if (j == 12) {
				name = path1 + p12 + std::to_string(i) + png;
			}
			else if (j == 13) {
				name = path1 + p13 + std::to_string(i) + png;
			}
			else if (j == 14) {
				name = path1 + p14 + std::to_string(i) + png;
			}
			else if (j == 15) {
				name = path1 + p15 + std::to_string(i) + png;
			}
			else if (j == 16) {
				name = path1 + p16 + std::to_string(i) + png;
			}
			else if (j == 17) {
				name = path1 + p17 + std::to_string(i) + png;
			}
			else if (j == 18) {
				name = path1 + p18 + std::to_string(i) + png;
			}
			else if (j == 19) {
				name = path1 + p19 + std::to_string(i) + png;
			}
			else {
				name = path1 + p20 + std::to_string(i) + png;
			}

			//name = "D:/pro/Weapons chaos/BDD/broom/broom_9.png";
			cv::Mat m = getImage(name);
			cv::Mat mask;
			mask = extract(m);

			vector<float> v;
			vector<float> v2;
			if (s == "hsv") {
				v = hog(mask, "hsv");
				v2 = lbp(mask, "hsv");
			}
			else {
				v = hog(mask, "bgr");
				v2 = lbp(mask, "bgr");
			}

			float ecce = eccentricity(mask);
			float conv = convex(mask);

			vector<float> data = vector<float>(267, 0);
			data[0] = ecce;
			data[1] = conv;
			for (int i = 0; i < 9; i++) {
				data[2 + i] = v[i];
			}
			for (int j = 0; j < 256; j++) {
				data[11 + j] = v2[j];
			}

			

			if (fichier)
			{
				for (int i = 0; i < 267; i++) {

					fichier << to_string(data[i]) << ";";
					

				}
				fichier << "\n";
			}

			
		}
	}

	

}


Mat Analyse::getData(string s, ifstream& fichier) {

	Mat vect(Mat_<float>(20 * 15, 267));
	string ligne;
	for (int i = 0; i < 20 * 15; i++) {
		for (int j = 0; j < 267; j++) {
			getline(fichier, ligne, ';');
			double a = stod(ligne);
			if (true) {
				vect.at<float>(i, j) = a;
			}
			else if (true) {
				vect.at<float>(i - 10, j) = a;
			}
		}
		getline(fichier, ligne, '\n');

	}

	return vect;

}


int Analyse::giveClass1(string s,string name, Mat m) {


	Mat vect(Mat_<float>(20 * 15, 267));

	for (int i = 0; i < 20 * 15; i++) {
		for (int j = 0; j < 267; j++) {


			if (true) {
				vect.at<float>(i, j) = m.at<float>(i, j);
			}
			else if (i >= 5) {
				vect.at<float>(i, j) = m.at<float>(i + 2, j);
			}
		}


	}



	cv::Mat m1 = getImage(name);
	cv::Mat mask;
	mask = extract(m1);

	vector<float> v;
	vector<float> v2;
	if (s == "hsv") {
		v = hog(mask, "hsv");
		v2 = lbp(mask, "hsv");
	}
	else {
		v = hog(mask, "bgr");
		v2 = lbp(mask, "bgr");
	}

	float ecce = eccentricity(mask);
	float conv = convex(mask);

	vector<float> data = vector<float>(267, 0);
	data[0] = ecce;
	data[1] = conv;
	for (int i = 0; i < 9; i++) {
		data[2 + i] = v[i];
	}
	for (int j = 0; j < 256; j++) {
		data[11 + j] = v2[j];
	}

	Mat input(Mat_<float>(1, 267));
	
		for (int i = 0; i < 267; i++) {
			input.at<float>(0, i) = data[i];
		}
	

	Mat soluce(Mat_<float>(20 * 15, 1));
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 15; j++) {
			soluce.at<float>(i * 15 + j) = i;
		}
	}

	

	cv::Ptr<cv::ml::KNearest>  k(cv::ml::KNearest::create());

	k->train(vect, cv::ml::ROW_SAMPLE, soluce);


	Mat sol;
	k->findNearest(input, 5, sol);



	

	return sol.at<float>(0,0);


}




int Analyse::giveClass2(string s,Mat e, Mat m) {

	Mat vect(Mat_<float>(20 * 15, 267));

	for (int i = 0; i < 20 * 15; i++) {
		for (int j = 0; j < 267; j++) {


			if (true) {
				vect.at<float>(i, j) = m.at<float>(i, j);
			}
			else if (i >= 5) {
				vect.at<float>(i, j) = m.at<float>(i + 2, j);
			}
		}


	}



	
	cv::Mat mask;
	mask = extract(e);

	vector<float> v;
	vector<float> v2;
	if (s == "hsv") {
		v = hog(mask, "hsv");
		v2 = lbp(mask, "hsv");
	}
	else {
		v = hog(mask, "bgr");
		v2 = lbp(mask, "bgr");
	}

	float ecce = eccentricity(mask);
	float conv = convex(mask);

	vector<float> data = vector<float>(267, 0);
	data[0] = ecce;
	data[1] = conv;
	for (int i = 0; i < 9; i++) {
		data[2 + i] = v[i];
	}
	for (int j = 0; j < 256; j++) {
		data[11 + j] = v2[j];
	}

	Mat input(Mat_<float>(1, 267));

	for (int i = 0; i < 267; i++) {
		input.at<float>(0, i) = data[i];
	}


	Mat soluce(Mat_<float>(20 * 15, 1));
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 15; j++) {
			soluce.at<float>(i * 15 + j) = i;
		}
	}



	cv::Ptr<cv::ml::KNearest>  k(cv::ml::KNearest::create());

	k->train(vect, cv::ml::ROW_SAMPLE, soluce);


	Mat sol;
	k->findNearest(input, 5, sol);





	return sol.at<float>(0, 0);


}