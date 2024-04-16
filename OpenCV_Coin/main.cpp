<<<<<<< HEAD
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void hough_circles();

int main(void)
{
	hough_circles();
}

void hough_circles()
{
	Mat src = imread("img/coin.jpg", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat blurred;
	blur(src, blurred, Size(3, 3));

	vector<Vec3f> circles;
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 200, 50);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	int total = 0;

	for (Vec3f c : circles)
	{
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);

		if (radius >= 50)
		{
			putText(dst, "500", center + Point(30, 0), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 255, 0));
			total += 500;
		}
		else if (radius >= 36 && radius < 50)
		{
			putText(dst, "100", center + Point(30, 0), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 0, 0));
			total += 100;
		}
		else if (radius > 0 && radius < 36)
		{
			putText(dst, "10", center + Point(30, 0), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255));
			total += 10;
		}

		//String radius_value = format("radius: %d", radius);
		//putText(dst, radius_value, center + Point(30, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255));
	}

	String total_count = format("Total: %d", total);
	putText(dst, total_count, Point(10, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));

	imshow("src", src);
	imshow("dst", dst);


	waitKey(0);
	destroyAllWindows();
}
=======
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void hough_circles();

int main(void)
{
	hough_circles();
}

void hough_circles()
{
	Mat src = imread("img/coin.jpg", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat blurred;
	blur(src, blurred, Size(3, 3));

	vector<Vec3f> circles;
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 200, 50);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	int total = 0;

	for (Vec3f c : circles)
	{
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);

		if (radius >= 50)
		{
			putText(dst, "500", center + Point(30, 0), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 255, 0));
			total += 500;
		}
		else if (radius >= 36 && radius < 50)
		{
			putText(dst, "100", center + Point(30, 0), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 0, 0));
			total += 100;
		}
		else if (radius > 0 && radius < 36)
		{
			putText(dst, "10", center + Point(30, 0), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255));
			total += 10;
		}

		//String radius_value = format("radius: %d", radius);
		//putText(dst, radius_value, center + Point(30, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255));
	}

	String total_count = format("Total: %d", total);
	putText(dst, total_count, Point(10, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));

	imshow("src", src);
	imshow("dst", dst);


	waitKey(0);
	destroyAllWindows();
}
>>>>>>> 9641953 (Re-upload)
