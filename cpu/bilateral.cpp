#include <stdio.h>
#include "macros.h"
#include "Image.h"
#include "png.h"
#include "jpg.h"
#include "permutohedral.h"

bool endswith(const char *str, const char *suffix) {
    return (strcmp(str + strlen(str) - strlen(suffix), suffix) == 0);
}

int main(int argc, char **argv) {
    if (argc < 5) {
	printf("Usage: ./bilateral <input file> <output file> <spatial standard deviation> <color standard deviation>\n");
	printf("        PNG, JPG are supported file formats.\n");
	printf("        For instance, try ./bilateral input.png output.png 4 0.5\n");
	return 1;
    }

    // Load the input image
    Image input;
    if (endswith(argv[1], ".png")) {
	input = PNG::load(argv[1]);
    } else if (endswith(argv[1], ".jpg")) {
	input = JPG::load(argv[1]);
    } else {
	printf("Input image is neither .png or .jpg file\n");
    }

    if (input.channels != 3) {
        printf("This example program is for color bilateral filtering. Please use a 3-channel color image as input\n");
        return -1;
    }

    float invSpatialStdev = 1.0f/atof(argv[3]);
    float invColorStdev = 1.0f/atof(argv[4]);

    // Construct the position vectors out of x, y, r, g, and b.
    Image positions(1, input.width, input.height, 5);
    for (int y = 0; y < input.height; y++) {
	for (int x = 0; x < input.width; x++) {
	    positions(x, y)[0] = invSpatialStdev * x;
	    positions(x, y)[1] = invSpatialStdev * y;
	    positions(x, y)[2] = invColorStdev * input(x, y)[0];
	    positions(x, y)[3] = invColorStdev * input(x, y)[1];
	    positions(x, y)[4] = invColorStdev * input(x, y)[2];
	}
    }

    // Filter the input with respect to the position vectors. (see permutohedral.h)
    Image out = PermutohedralLattice::filter(input, positions);
    
    // Save the result
    if (endswith(argv[2], ".png")) {
	PNG::save(out, argv[2]);
    } else if (endswith(argv[2], ".jpg")) {
	JPG::save(out, argv[2], 99);
    } else {
	printf("Output image is neither .png or .jpg file\n");
    }    
    
    return 0;
}
