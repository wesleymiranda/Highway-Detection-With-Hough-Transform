#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

using std::vector;

typedef vector<Point2i> Pontos;

const float PI = 3.14159;

Mat inverterCoordenadas(Mat I);
Pontos Varrer(Mat M);
float converterAngulo(int T);
int CarteToPolar(Point2i P, int T);
int PolarToCarte(Point2i P, int X);
void Calculos(Mat M, Pontos P, int Ang_i, int Raio_i);
Pontos maiorValor(Mat M, ushort corte);
Mat desenhaRetas(Mat M, Pontos retas);
Mat Hough(Mat H, int Ang_i, int Ang_f, int Raio_i, int Raio_f, ushort corte);