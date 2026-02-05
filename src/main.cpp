#include "../include/image.h"
#include "../include/matrix.h"

int main() {

	Image img("test_image.pgm");

	Image(img).setNegative().save("neg_test_image.pgm");
	Image(img).setBrightnessLvl(150).save("neg_test_image.pgm");
	Image(img).threshold().save("neg_test_image.pgm");
	
	return 0;
}
