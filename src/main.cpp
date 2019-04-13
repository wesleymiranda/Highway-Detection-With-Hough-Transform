#include "Borrar.h"
#include "Contorno.h"
#include "Hough.h"

const int num = 2; // n�mero de vezes que a imagem ser� borrada
const int Tresh = 6; //Valor para treshold

int main() {
	Mat img = imread("pts.png", IMREAD_GRAYSCALE); 

	img = borrar(img, num); //PAR�METROS DE BORRAR: I-imagem II-quantidade de vezes que a imagem passa pelo processo

	img = contorno(img, Tresh); //PAR�METROS DE CONTORNO: I-imagem II-valor de treshold

	img = Hough(img, 0, 110, 0, 360, 13); 

	imshow("HOUGH", img);

	waitKey(0);
	return 0;
}
