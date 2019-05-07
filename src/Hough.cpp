#include "Hough.h"

using namespace std;

Mat inverterCoordenadas(Mat I) {
	Mat Aux = Mat::zeros(Size(I.cols, I.rows), CV_8UC1);
	for (int i = 0; i < I.rows; i++) {
		I.row(i).copyTo(Aux.row(Aux.rows - i - 1));
		// A.row(i) = A.row(j); Não funcionaria como o esperado
	}
	return Aux;
}

Pontos Varrer(Mat M) {
	Pontos Temp;
	for (int i = 0; i < M.rows; i++) {
		for (int j = 0; j < M.cols; j++) {
			if (M.at<uchar>(i, j) == 255) { 
				Point2i P(j, i); // X está para colunas como Y está para linhas
				Temp.push_back(P); //Coleto os pontos da imagem
			}
		}
	}
	return Temp;
}
