#include <iostream>

#include "../include/image.h"
#include "../include/matrix.h"

const int ROW = -1;
const int COL = -1;

void testingMatrixOperations() {
	
	Matrix<int> matA = {
		{ 1, 2, 5, 12},
		{12, 69, 4, 5},
		{9, 10, 12, 23}
	};
	
	// todo: add the ability to access a specific row or column for iteration like so
//	matA(2, ROW);	// selects the whole 2nd row
//	matA(COL, 2);	// selects the whole 2nd column
	
	Matrix<int> matB = {
		{4, 12, 18},
		{12, 15, 51}
	};
	
	Matrix<int> matC(-matA);
	
	
	(matB * matA).print();
	std::cout << '\n';
	
	(3 * -matB).print();
	std::cout << '\n';
	
	(matB * 3).print();
	std::cout << '\n';
	
	matC.print();
	std::cout << '\n';
	
	//hypothesis: does the matrix copy constructor end up modifying the original?
	(-matA).print();
	std::cout << '\n';
	
	matB.printAs<unsigned int>();
	std::cout << '\n';	
	
	(matA.transpose() + 2).print();
	std::cout << '\n';
}


std::string assets_path = "../assets/";
std::string generated_assets_path = assets_path + "generated/";


void testingP2ImageOperations() {
	Image img(assets_path + "feep_ascii.pgm");
	std::cout << "----------------------------------------------------------------------------" << '\n';
	img.logData();
	img.makeNegative().saveP2(generated_assets_path + "neg_test_image.pgm");
	img.setThreshold(12).saveP2( generated_assets_path + "thresh_test_image.pgm");
	img.saveP2(generated_assets_path + "feep_ascii2.pgm");
	img.setBrightnessLvl(80).saveP2(generated_assets_path + "bright_test_image.pgm");
}

void testingP5ImageOperations() {
	Image img(assets_path + "sample_640_by_426.pgm");
	std::cout << "----------------------------------------------------------------------------" << '\n';
//	img.logData();
	img.save(generated_assets_path + "second_sample_640_by_426.pgm");
	img.makeNegative().save(generated_assets_path + "neg_test_image.pgm");
	img.setBrightnessLvl(80).save(generated_assets_path + "bright_test_image.pgm");
	img.setThreshold(12).save( generated_assets_path + "thresh_test_image.pgm");
}


int main() {
	// todo: implement matrix via vectors. simply change the access technique in the operator () overload
	// you'll also have to change all the constructors and desctructors
	
	
//	testingMatrixOperations();
//	testingP2ImageOperations();
	testingP5ImageOperations();
	
	return 0;
}
