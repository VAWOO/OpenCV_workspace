#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void on_mouse_warp(int event, int x, int y, int flags, void* userdata);

Mat src;
vector<Point2f> srcQuad(4);
int cnt = 0;

int main(void)
{
    while (true)
    {
        src = imread("img/card.bmp");

        if (src.empty())
        {
            cerr << "Image load failed!" << endl;
            return -1;
        }

        namedWindow("src");
        setMouseCallback("src", on_mouse_warp);
        imshow("src", src);

        int key = waitKey(0);

        if (key == 'c' || key == 'C')
        {
            destroyAllWindows();

            Mat src_copy_point = src.clone();
            imshow("src", src_copy_point);

            cnt = 0;

            continue;
        }
        else
        {
            break;
        }
    }

    return 0;
}

void on_mouse_warp(int event, int x, int y, int flags, void*)
{
    static Mat src_copy = src.clone();

    if (event == EVENT_LBUTTONDOWN)
    {
        if (cnt == 0)
        {
            src_copy = src.clone();
        }

        if (cnt < 4)
        {
            srcQuad[cnt++] = Point2f(x, y);

            circle(src_copy, Point(x, y), 5, Scalar(0, 0, 255), -1);
            imshow("src", src_copy);

            if (cnt == 4)
            {
                for (int i = 0; i < srcQuad.size(); i++)
                {
                    cout << "Point " << i << ": (" << srcQuad[i].x << ", " << srcQuad[i].y << ")" << endl;
                }

                int w = 200, h = 300;

                vector<Point2f> dstQuad(4);
                dstQuad[0] = Point2f(0, 0);
                dstQuad[1] = Point2f(w - 1, 0);
                dstQuad[2] = Point2f(w - 1, h - 1);
                dstQuad[3] = Point2f(0, h - 1);

                Mat pers = getPerspectiveTransform(srcQuad, dstQuad);

                Mat dst;
                warpPerspective(src, dst, pers, Size(w, h));

                imshow("dst", dst);
            }
        }
    }
}