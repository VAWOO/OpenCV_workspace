#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void labeling_stats();

int main(void)
{
    labeling_stats();

    return 0;
}

void labeling_stats()
{
    Mat src = imread("img/keyboard.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat bin;
    threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

    Mat labels, stats, centroids;
    int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for (int i = 1; i < cnt; i++)
    {
        int* p = stats.ptr<int>(i);

        if (p[4] < 20) continue;

        rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255), 2);
    }

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}