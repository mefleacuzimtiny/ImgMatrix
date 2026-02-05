#include "../include/image.h"

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

Image::Image(std::string fname) {
	load(fname);
	
}


void Image::load(std::string fname) {
	// read width and read height
	
}

void Image::save(std::string fname) const {
	
}

Image Image::makeNegative() const {
	imgmat = -imgmat;
}

Image Image:: setBrightnessLvl(unsigned char lvl) const {
	
}

Image Image::setThreshold(unsigned char lvl) const {
	
}


unsigned char Image::getPixel(int x, int y) const {
	
}

void Image::setPixel(int x, int y, unsigned char p) {
	
}






