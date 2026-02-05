#ifndef MATRIXPROJ_HEADER_IMAGE
#define MATRIXPROJ_HEADER_IMAGE

#include <iostream>

class Image{
private:
	Matrix<Pixel> imgmat;
public:
	Image(std::string fname, BITDEPTH bd);
	Image(BITMAP bd);
	
	Image getNegative() const;
	Image setBrightnessLvl(unsigned char lvl);
	
	void setNegative();
	
	void load(std::string fname);
	void save(std::string fname);
	
	void getPixel(int x, int y);
	void setPixel(int x, int y, Pixel p);
	
	void setBitDepth(BITDEPTH bd);
};


#endif
