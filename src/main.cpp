#include <iostream>

#include "../include/image.h"
#include "../include/matrix.h"

int main() {
	
//	Matrix<unsigned char> matA = {
//		{ 1, 2, 5, 12},
//		{12, 69, 4, 5},
//		{9, 10, 12, 23}
//	};
//	
//	Matrix<int> matB = {
//		{4, 12, 18},
//		{12, 15, 51}
//	};
//	
////	(matB * matA).print();
//	(-matA).print();
//	
//	std::cout << '\n';
//	(3 * matB).print();
//
//	std::cout << '\n';
//	(matB * 3).print();
	
	//todo: make the matrix be instantiable from a raw string
	
	std::string assets_path = "../assets/";
	
//	Image img(assets_path + "sample_640_by_426.pgm");
	
//	Duplicating to check if load() and save() work as expected
	Image img(assets_path + "feep_ascii.pgm");
//	std::cout << "----------------------------------------------------------------------------" << '\n';
	img.logData();
	img.saveP2(assets_path + "feep_ascii2.pgm");
	

//	img.makeNegative().save(assets_path + "neg_test_image.pgm");
//	img.setBrightnessLvl(150).save(assets_path + "bright_test_image.pgm");
//	img.setThreshold(12).save( assets_path + "thresh_test_image.pgm");
	
	return 0;
}
