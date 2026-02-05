#ifndef MATRIXPROJ_HEADER_PIXEL
#define MATRIXPROJ_HEADER_PIXEL

class Pixel {
private:
	unsigned char r, g, b;
public:
	
	Pixel() 
	: r(0), g(0), b(0) {
	}
	
	Pixel(unsigned char r = 0,
		  unsigned char g = 0,
		  unsigned char b = 0)
	: r(r), g(g), b(b) {
	}
	
	
};



#endif
