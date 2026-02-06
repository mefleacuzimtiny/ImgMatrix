#include <iostream>

//#include "../include/image.h"
#include "../include/matrix.h"

int main() {
	
	// todo: read matrix from string
	
	std::string mat = R"matrix(
1 2 4 7
12 69 5 80
4 3 1 2
9 8 5 12
)matrix";
	
	std::stringstream matrix(mat);
	
	Matrix <int> matC;
	matrix >> matC;
	
	Matrix<int> matA = {
		{ 1, 2, 5, 12},
		{12, 69, 4, 5},
		{9, 10, 12, 23}
	};
	
	Matrix<int> matB = {
		{4, 12, 18},
		{12, 15, 51}
	};
	
	(matB * matA).print();
	
	std::cout << '\n';
	(3 * matB).print();

	std::cout << '\n';
	(matB * 3).print();
	
	std::cout << '\n';
	matC.print();
	
//	Image img("test_image.pgm");
//
//	Image(img).setNegative().save("neg_test_image.pgm");
//	Image(img).setBrightnessLvl(150).save("neg_test_image.pgm");
//	Image(img).threshold(12).save("neg_test_image.pgm");
	
	return 0;
}
