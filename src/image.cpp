#include "../include/image.h"

Image::Image() {
	
}

Image Image::getNegative() const {
	imgmat = -imgmat;
}


