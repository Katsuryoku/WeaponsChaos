// OpenCV.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"

#include "Analyse.h"

#include <opencv2/opencv.hpp>

#include <string>
#include <iostream>
#include <fstream>

#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/ml/ml.hpp"
#include <limits.h>
#include <map>
#include <string>
#include <iostream>

using namespace std;
using namespace cv;




int main(int argc, char** argv)
{
	


	Analyse b = Analyse();

	/*ofstream fichier;
	fichier.open("test2.txt", ios::out | ios::trunc);
	b.train("hsv",fichier);
	fichier.close();*/
	
	
	ifstream fichier;
	fichier.open("test.txt", ios::in);
	Mat data = b.getData("", fichier);
	
	fichier.close();
	
	vector<int> sol1 = b.giveClass("", 0,data);
	vector<int> sol2 = b.giveClass("", 1, data);
	vector<int> sol3 = b.giveClass("", 2, data);
	vector<int> sol4 = b.giveClass("", 3, data);
	vector<int> sol5 = b.giveClass("", 4, data);
	vector<int> sol6 = b.giveClass("", 5, data);
	vector<int> sol7 = b.giveClass("", 6, data);
	vector<int> sol8 = b.giveClass("", 7, data);
	vector<int> sol9 = b.giveClass("", 8, data);
	vector<int> sol10 = b.giveClass("", 9, data);
	vector<int> sol11 = b.giveClass("", 10, data);
	vector<int> sol12 = b.giveClass("", 11, data);
	vector<int> sol13 = b.giveClass("", 12, data);
	vector<int> sol14 = b.giveClass("", 13, data);
	vector<int> sol15 = b.giveClass("", 14, data);


	float add = 0;
	
		for (int j = 0; j < 20; j++) {
			add = add + (sol1[j]-j!=0);
			add = add + (sol2[j] - j!=0);
			add = add + (sol3[j] - j!=0);
			add = add + (sol4[j] - j!=0);
			add = add + (sol5[j] - j!=0);
			add = add + (sol6[j] - j!=0);
			add = add + (sol7[j] - j!=0);
			add = add + (sol8[j] - j!=0);
			add = add + (sol9[j] - j!=0);
			add = add + (sol10[j] - j!=0);
			add = add + (sol11[j] - j!=0);
			add = add + (sol12[j] - j!=0);
			add = add + (sol13[j] - j!=0);
			add = add + (sol14[j] - j!=0);
			add = add + (sol15[j] - j!=0);
		}
	
	
		add = add/(20*15) ;


	vector<vector<int>> confusion(20, vector<int>(20, 1));
	


	string name = "D:/pro/Weapons chaos/test_screwdriver_2.png";
	cv::Mat m1 = b.getImage(name);
	int sol = b.giveClass1("",name, data);
	int solbis = b.giveClass2("",m1,data);

	cv::Mat m2 = b.getImage("D:/pro/Weapons chaos/BDD/screwdriver/screwdriver_2.png");
	//Canny(m,m,0,80);
	cv::Mat mask2;
	mask2 = b.extract(m2);

	/*ofstream fichier;
	fichier.open("test.txt", ios::out | ios::trunc);
	b.train("",fichier);
	fichier.close();*/

	

	/*vector<float> v = b.hog(mask, "hsv");
	vector<float> v2 = b.hog(mask, "bgr");

	vector<float> v3 = b.lbp(mask, "hsv");
	vector<float> v4 = b.lbp(mask, "bgr");*/

	imshow("Display window", mask2);                   // Show our image inside it.
	waitKey(0);
	return 0;
	
}