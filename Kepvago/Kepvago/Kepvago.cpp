// Kepvago.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\core\core.hpp"


using namespace std;
using namespace cv;

int subdivide(int &cntr, cv::Mat& img, const int rowDivisor, const int colDivisor)
{
	for (int y = 0; y < img.cols; y += img.cols / colDivisor)
		{
			for (int x = 0; x < img.rows; x += img.rows / rowDivisor)
			{
				if (0<=x && 0<=(img.cols / colDivisor) && y+(img.cols / colDivisor)<=img.cols && 0<=y && 0<=(img.rows / rowDivisor) && x+(img.rows / rowDivisor)<= img.rows) 
				{
					Mat cutted = img(Rect(y, x, (img.cols / colDivisor), (img.rows / rowDivisor)));

					// saving part:
					string savingName = "image" + std::to_string(++cntr) + ".jpg";
					imwrite(savingName, cutted);
				}
			}
	}
	return EXIT_SUCCESS;
}

int main()
{
	Mat image;

	image = imread("gnocchi.jpg", 1);
	if (!image.data || image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	// get the image data
	int height = image.rows;
	int width = image.cols;

	printf("Processing a %dx%d image\n", height, width);

	int cntr = 0;

	// ciklussal sokfele darabban
	subdivide(cntr,image, 3, 3);
	subdivide(cntr, image, 4, 4);
	subdivide(cntr, image, 4, 5);

	// 4 darabban
	/*Mat top_left = image(Range(0, height / 2 - 1),Range(0, width / 2 - 1));
	Mat top_right = image(Range(0, height / 2 - 1), Range(width / 2, width - 1));
	Mat bottom_left = image(Range(height / 2, height - 1), Range(0, width / 2 - 1));
	Mat bottom_right = image(Range(height / 2, height - 1), Range(width / 2, width - 1));

	imshow("top_left", top_left);
	imshow("top_right", top_right);
	imshow("bottom_left", bottom_left);
	imshow("bottom_right", bottom_right);*/

	waitKey(0);
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
