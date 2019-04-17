#pragma once

#include <opencv2/opencv.hpp>
using namespace cv;

Mat contorno(Mat C, uchar Tresh);
uchar Treshold(uchar grad, uchar Tresh);
uchar Grad(double X, double Y);
uchar Masc(Mat G, uchar Tresh);