#ifndef MATRIXPROJ_SRC_IMAGE
#define MATRIXPROJ_SRC_IMAGE


#include <stdexcept>

#include "../include/image.h"

//========================================================== CONSTRUCTORS ==========================================================

Image::Image() :							// default constructor
	imgmat(0, 0),
	width(0),
	height(0)
{ }

Image::Image(const Image& img):			// copy constructor
	imgmat(img.imgmat),
	width(img.width),
	height(img.height) 
{ }

Image::Image(Matrix<unsigned char> mat):
	imgmat(mat),
	width(mat.getColCount()),
	height(mat.getRowCount())
{ }

Image::Image(std::string fname) {
	load(fname);
}

////////////////////////////////////////////////////////// CONSTRUCTORS END //////////////////////////////////////////////////////////



//========================================================== OBSERVERS ==========================================================

void Image::save(std::string fname) const {
	
}

Image Image::makeNegative() const {
	Image newimg(-imgmat);
	return newimg;
}

Image Image:: setBrightnessLvl(unsigned char lvl) const {
	
}

Image Image::setThreshold(unsigned char lvl) const {
	
}


unsigned char Image::getPixel(int x, int y) const {
	
}

////////////////////////////////////////////////////////// OBSERVERS END //////////////////////////////////////////////////////////



//========================================================== MUTATORS ==========================================================

void Image::load(std::string fname) {
	std::ifstream file(fname, std::ios::binary);
	if (!file) {
		throw std::invalid_argument("Error: Cannot open file\n");
	}
	
	std::string format;
	int width, height, maxval;
	if (!(file >> format >> width >> height >> maxval)) {
		throw std::invalid_argument("Error: Invalid PGM header\n");
	}
	
	if (format != "P5") {
		throw std::invalid_argument("Error: Only P5 (binary) PGM supported\n");
	}
	
	file.get();			// skips newline
	
	imgmat = Matrix<unsigned char>(height, width);
	file >> imgmat;
	
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			char pixelValue;
			if (!file.read(&pixelValue, sizeof(pixelValue))) {
				throw std::runtime_error("Error: Could not read pixel data at position (" + std::to_string(i) + ", " + std::to_string(j) + ")");
			}
			imgmat(i, j) = static_cast<unsigned char>(pixelValue);
		}
	}
	
	std::cout << "PGM loaded successfully: " << width << "x" << height << "\n";
}

void Image::setPixel(int x, int y, unsigned char p) {
	imgmat(x, y) = p;
}

#endif
////////////////////////////////////////////////////////// MUTATORS END //////////////////////////////////////////////////////////
