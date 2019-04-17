#include "Contorno.h"
#include <cmath>

uchar Treshold(uchar grad, uchar Tresh) {
	return (grad > Tresh) ? 255 : 0;
}

uchar Grad(double X, double Y) {
	return (uchar) sqrt(X*X + Y*Y);
}

uchar Masc(Mat G, uchar Tresh) {
	Mat MascaraX = (Mat_<double>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
	Mat MascaraY = (Mat_<double>(3, 3) << -1, -1, -1, 0, 0, 0, 1, 1, 1);

	double tempX = 0, tempY = 0;

	G.convertTo(G, CV_64F);

	Mat AuxX = G.mul(MascaraX);
	Mat AuxY = G.mul(MascaraY);

	for (int i = 0; i < AuxX.rows; i++) {
		tempX += abs(AuxX.at<double>(i, 0) + AuxX.at<double>(i, 2));
	}

	for (int j = 0; j < AuxY.cols; j++) {
		tempY += abs(AuxY.at<double>(0, j) + AuxY.at<double>(2, j));
	}

	return Treshold(Grad(tempX / 3, tempY / 3), Tresh);
}

Mat contorno(Mat C, uchar Tresh) {
	Mat Aux = Mat::zeros(Size(C.cols, C.rows), CV_8UC1);

	for (int lin = 1; lin < C.rows - 1; lin++) {
		for (int col = 1; col < C.cols - 1; col++) {
			Mat Temp = C(Range(lin - 1, lin + 2), Range(col - 1, col + 2));
			uchar a = Masc(Temp, Tresh);
			Aux.at<uchar>(lin, col) = a;
		}
	}
	return Aux;
}