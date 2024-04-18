#include "opencv2/opencv.hpp"
#include "opencv2/core/utils/logger.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
    utils::logging::setLogLevel(utils::logging::LogLevel::LOG_LEVEL_ERROR);

    Mat srcimage = imread("img/Paper.bmp");
    Mat dstimage = srcimage.clone();
    GaussianBlur(srcimage, srcimage, Size(3, 3), 0.0);

    Mat hsvimage;
    cvtColor(srcimage, hsvimage, COLOR_BGR2HSV);

    Mat bimage;
    Scalar lowerb(0, 40, 0);
    Scalar upperb(20, 180, 255);
    inRange(hsvimage, lowerb, upperb, bimage);

    erode(bimage, bimage, Mat());
    dilate(bimage, bimage, Mat(), Point(-1, -1), 2);

    vector<vector<Point>> contours;
    findContours(bimage, contours, noArray(), RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    cout << "contours.size() = " << contours.size() << endl;
    
    if (contours.size() < 1)
        return 0;

    int maxK = 0;
    double maxArea = contourArea(contours[0]);

    for (int k = 1; k < contours.size(); k++)
    {
        double area = contourArea(contours[k]);
        if (area > maxArea)
        {
            maxK = k;
            maxArea = area;
        }
    }

    vector<Point> handContour = contours[maxK];
    vector<int> hull;
    convexHull(handContour, hull);
    cout << "hull.size() = " << hull.size() << endl;

    vector<Point> ptsHull;
    for (int k = 0; k < hull.size(); k++)
    {
        int i = hull[k];
        ptsHull.push_back(handContour[i]);
    }

    drawContours(dstimage, vector<vector<Point>>(1, ptsHull), 0, Scalar(255, 0, 0), 2);

    imshow("dstimage-Hull", dstimage);

    vector<Vec4i> defects;
    convexityDefects(handContour, hull, defects);

    for (int k = 0; k < defects.size(); k++)
    {
        Vec4i v = defects[k];
        Point ptStart = handContour[v[0]];
        Point ptEnd = handContour[v[1]];
        Point ptFar = handContour[v[2]];

        circle(dstimage, ptStart, 3, Scalar(0, 0, 255), 2);
        circle(dstimage, ptEnd, 3, Scalar(0, 0, 255), 2);
        circle(dstimage, ptFar, 3, Scalar(0, 0, 255), 2);
    }

    cout << "defects.size() = " << defects.size() << endl;
    imshow("dstimage", dstimage);
    waitKey(0);
    return 0;
}