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

float converterAngulo(int T) {
	return (float)(T * PI / 180);
}

int CarteToPolar(Point2i P, int T) {
	float Theta = converterAngulo(T);
	return (int)(P.x * cos(Theta) + P.y * sin(Theta));
}

int PolarToCarte(Point2i P, int X) {
	//considere P.x para raio e P.y para angulo
	float Theta = converterAngulo(P.y);
	return (int)(P.x / sin(Theta) - X / tan(Theta));
}

void Calculos(Mat M, Pontos P, int Ang_i, int Raio_i) {
	for (int i = 0; i < P.size(); i++) { //Acessando os pixels da imagem
		for (int Ang = 0; Ang < M.rows; Ang++) { //Valores limitados para Theta
			int R =CarteToPolar(P[i], Ang + Ang_i); //Resultados para Rho
			if ((Raio_i < R)&&(R < (M.cols + Raio_i)))
				M.at<ushort>(Ang,R - Raio_i)++;
		}
	}
}

Pontos maiorValor(Mat M, ushort corte) {
	Pontos Temp;
	Temp.clear();

	for (int Ang = 0; Ang < M.rows; Ang++) {
		for (int R = 0; R < M.cols; R++) {
			if (M.at<ushort>(Ang, R) > corte)
			{
				Point2i P(R, Ang);
				Temp.push_back(P);
				cout << "R= " << P.x << " A= " << P.y<<endl;
			}
		}
	}
	return Temp;
}

Mat desenhaRetas(Mat M, Pontos P) {
	int x1 = 0;
	int x2 = M.cols;
	
	for (int i = 0; i < P.size(); i++) {
		int y1 = PolarToCarte(P[i], x1 );
		int y2 = PolarToCarte(P[i], x2);
		line(M, Point(x1, y1), Point(x2, y2), Scalar(255, 255, 255));
	}
	return M;
}

Mat Hough(Mat H, int Ang_i, int Ang_f, int Raio_i, int Raio_f, ushort corte) {

	Pontos Pixels;
	Mat Tabela = Mat::zeros(Size(Raio_f - Raio_i, Ang_f - Ang_i), CV_16U);
	
	H = inverterCoordenadas(H); //Passa o sistema para as coordenadas cartesianas
	
	Pixels = Varrer(H);         //Identificar todos os pixels da imagem
	Calculos(Tabela, Pixels, Ang_i, Raio_i);
	Pontos PontoPolar = maiorValor(Tabela, corte);
	H = desenhaRetas(H, PontoPolar);

	H = inverterCoordenadas(H); //Passa para a coordenada padrão do OpenCV
	
	return H;
}