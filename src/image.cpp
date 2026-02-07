#ifndef MATRIXPROJ_SRC_IMAGE
#define MATRIXPROJ_SRC_IMAGE


#include <stdexcept>
#include <fstream>

#include "../include/image.h"


class BadPixelException : public std::runtime_error {
	
};


//========================================================== CONSTRUCTORS ==========================================================

Image::Image() :							// default constructor
	imgmat(),
	width(1),
	height(1)
{ }

Image::Image(const Image& img):			// copy constructor
	imgmat(img.imgmat),
	width(img.width),
	height(img.height) 
{ }

Image::Image(const Matrix<unsigned char>& mat):
	imgmat(mat),
	width(mat.getColCount()),
	height(mat.getRowCount())
{ }

Image::Image(const std::string& fname) {
	load(fname);
}

////////////////////////////////////////////////////////// CONSTRUCTORS END //////////////////////////////////////////////////////////



//========================================================== OBSERVERS ==========================================================

void Image::save(const std::string& fpath) const {
	std::cout << "File size is: " << width << " " << height << '\n';
	std::ofstream file(fpath, std::ios::binary);
	if (!file) {
		throw std::invalid_argument("Error: Cannot open file for writing\n");
	}
	
	// Write PGM header
	file << "P5\n";
	file << width << " " << height << "\n";
	file << 255 << "\n";
	
	// Write pixel data
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			unsigned char pixel = imgmat(i, j);
			file.write(reinterpret_cast<char*>(&pixel), sizeof(pixel));
		}
	}
	
	if (!file) {
		throw std::runtime_error("Error: Failed while writing image data\n");
	}
	
	std::cout << "PGM saved successfully: " << width << "x" << height << "\n";
}



void Image::saveP2(const std::string& fpath) const {
	std::cout << "File size is: " << width << " " << height << '\n';
	std::ofstream file(fpath, std::ios::in);
	if (!file) {
		throw std::invalid_argument("Error: Cannot open file for writing\n");
	}
	
	// Write PGM header
	file << "P2\n";
	file << width << " " << height << "\n";
	file << 255 << "\n";
	
	// Write pixel data
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			unsigned int pixel = imgmat(i, j);
//			file.write(reinterpret_cast<char*>(&pixel), sizeof(pixel));
			file << pixel << " ";
		}
		file << '\n';
	}
	
	if (!file) {
		throw std::runtime_error("Error: Failed while writing image data\n");
	}
	
	std::cout << "PGM saved successfully: " << width << "x" << height << "\n";
}


Image Image::makeNegative() const {
	Image newimg(-imgmat);
	return newimg;
}

//Image Image:: setBrightnessLvl(unsigned char lvl) const {
//	
//}
//
//Image Image::setThreshold(unsigned char lvl) const {
//	
//}
//
//
//unsigned char Image::getPixel(int x, int y) const {
//	
//}


void Image::logData() const {
	imgmat.print();
	std::cout << "Image dimensions: " << width << " " << height << '\n';
}


////////////////////////////////////////////////////////// OBSERVERS END //////////////////////////////////////////////////////////



//========================================================== MUTATORS ==========================================================


unsigned char readP5Pixel(std::ifstream& file) {
	char pixelValue;
	
	if (!file.read(&pixelValue, sizeof(pixelValue))) {
		throw std::runtime_error("Error: Could not read pixel data");
	}
	
	std::cout << static_cast<unsigned int>(pixelValue) << " ";
	return static_cast<unsigned char>(pixelValue);
}

unsigned int readP2Pixel(std::ifstream& file) {
	unsigned int pixelValue;
	
	if (!(file >> pixelValue)) {  // read ASCII number
		throw std::runtime_error("Error: Could not read pixel data");
	}
	
	std::cout << pixelValue << " ";
	return pixelValue;
}


void Image::load(const std::string& fpath) {
	std::ifstream file(fpath, std::ios::binary);
	if (!file) {
		throw std::invalid_argument("Error: Cannot open file\n");
	}
	
	std::string format;
	int maxval;
	if (!(file >> format >> width >> height >> maxval)) {
		throw std::invalid_argument("Error: Invalid PGM header\n");
	}
	
//	if (format != "P5") {
//		throw std::invalid_argument("Error: Only P5 (binary) PGM supported\n");
//	}
	
	file.get();			// skips newline
	
	imgmat = Matrix<unsigned char>(height, width);
	
//	todo: in the future, replace this whole chunk with file >> imgmat;
//	for (int i = 0; i < height; ++i) {
//		for (int j = 0; j < width; ++j) {
////			char pixelValue;
////			if (!file.read(&pixelValue, sizeof(pixelValue))) {
////				throw std::runtime_error("Error: Could not read pixel data at position (" + std::to_string(i) + ", " + std::to_string(j) + ")");
////			}
////			std::cout << static_cast<unsigned int>(pixelValue);
////			imgmat(i, j) = static_cast<unsigned char>(pixelValue);
//			try {
//				imgmat(i, j) = readPixelAsByte(file);
//			} catch (std::runtime_error e) {
//				std::cout << e.what() << " at position (" + std::to_string(i) + ", " + std::to_string(j) + ")" << '\n';
//			}
//		}
//	}
	
	if (format == "P2") {
		std::cout << "Format is P2" << '\n';
		
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				try {
					imgmat(i, j) = readP2Pixel(file);
				} catch (std::runtime_error e) {
					std::cout << e.what() << " at position (" + std::to_string(i) + ", " + std::to_string(j) + ")" << '\n';
				}
			}
			std::cout << '\n';
		}
	}
	
	
	std::cout << "\n\nPGM loaded successfully: " << width << "x" << height << "\n";
}

void Image::setPixel(int x, int y, unsigned char p) {
	imgmat(x, y) = p;
}

#endif
////////////////////////////////////////////////////////// MUTATORS END //////////////////////////////////////////////////////////
