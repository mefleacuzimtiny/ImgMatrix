#ifndef MATRIXPROJ_HEADER_IMAGE
#define MATRIXPROJ_HEADER_IMAGE

#include <iostream>
//#include "../include/pixel.h"
#include "../include/matrix.h"


// Hypothesis: instead of having a base class image, which then splits into child classes ImagePGMP2, ImagePGMP5, and ImagePNG,
// what if we had three small base classes ImagePGMP2, ImagePGMP5, and ImagePNG, which were combined into an Imageclass using multiple inheritance

/*Advice from a friend on ways to handle the different image formats:
" not very familiar with C++ patterns, so might be better to ask there but, I would either:
Have an image class, internally it figures out types with a strategy pattern
Have an abstract image class, the other types make classes out of it, users interface with the Image class, but underneath it's actually a concrete type "
*/


class Image{
private:
	
	std::string format;
	int width, height;
	int maxval;
	Matrix<unsigned char> imgmat;
	
public:
	Image();							// default constructor
	Image(const Image& img);			// copy constructor
	Image(const Matrix<unsigned char> mat);		// generate image directly from matrix of pixels or unsigned chars
	Image(const std::string& fpath);				// generate image object from pgm file path
	
	void save(const std::string& fpath) const;
	void saveP2(const std::string& fpath) const;
	Image makeNegative() const;
	Image setBrightnessLvl(unsigned char lvl) const;
	Image setThreshold(unsigned char lvl) const;
	unsigned char getPixel(int x, int y) const;
	void logData() const;
	
	void load(const std::string& fname);
	void setPixel(int x, int y, unsigned char p);
	
};


//class Image{
//private:
//	Matrix<Pixel> imgmat;
//public:
//	Image();
//	Image(Image& img) : imgmat(img.imgmat) {};			// copy constructor
//	Image(BITMAP bd);
//	Image(std::string fname, BITDEPTH bd);
//	void setBitDepth(BITDEPTH bd);
//	
//	void load(std::string fname);
//	void save(std::string fname) const;
//	
//	
//	Image getNegative() const;
//	Image setBrightnessLvl(unsigned char lvl);
//	Image setThreshold(unsigned char lvl);
//	
//	
//	void getPixel(int x, int y);
//	void setPixel(int x, int y, Pixel p);
//	
//};


#include "../src/image.cpp"

#endif
