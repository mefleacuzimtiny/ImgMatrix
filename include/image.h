#ifndef MATRIXPROJ_HEADER_IMAGE
#define MATRIXPROJ_HEADER_IMAGE

#include <iostream>
//#include "../include/pixel.h"
#include "../include/matrix.h"

class Image{
private:
	Matrix<unsigned char> imgmat;
	int width;
	int height;
public:
	Image();							// default constructor
	Image(const Image& img);			// copy constructor
	Image(const Matrix<unsigned char>& mat);		// generate image directly from matrix of pixels or unsigned chars
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
