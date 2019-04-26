#include "Borrar.h"

#include <iostream>
using namespace std;


uchar Media(Mat A) {
	Mat Mascara = (Mat_<double>(3, 3) << 0.2, 0.5, 0.2, 0.5, 1.0, 0.5, 0.2, 0.5, 0.2);
	//Inicialização com valores separados por vírgula, recomendada para matrizes pequenas.
	 
	A.convertTo(A, CV_64F); 
	//Logo abaixo será realuzada uma multiplicação
	//A converção é necessária para que não multipliquemos uma mat. uchar com uma mat. double

	Mat Aux = Mascara.mul(A);
	//Multiplicação diferente da matricial que conhecemos
	//Neste caso, multiplicam-se as respectivas entradas.

	float sum = 0;
	for (int i = 0; i < Aux.rows; i++){
		for (int j = 0; j < Aux.cols; j++)
			sum += Aux.at<double>(i, j); //Erro mat.inl.hpp: Aux é do tipo double, tentei acessálo usando Aux.at<uchar>
			
	}

	return (uchar)(sum / 3.8);
	return 0;
}
