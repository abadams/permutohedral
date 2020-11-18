This is a single-header-file implementation of high-dimensional 
Gaussian filtering using the Permutohedral lattice. The implementation 
is in permutohedral.h. 



We encourage reading through the code in permutohedral.h. Skip past
 the hash table implementation at the top (it's a fairly standard 
hash-table) and have a look at PermutohedralLattice, and particularly 
its splat, blur, and slice methods. 

To demonstrate it, code is also included to compute color bilateral 
filters of jpegs and pngs (this accounts for all the rest of the 
files). The included Makefile should build a binary to compute such 
filters. It has been tested on linux and windows under cygwin. It 
should compile anywhere libpng and libjpeg are available.



After building, the following command line will compute a color 
bilateral filter with spatial standard deviation of 5 pixels, and 
color standard deviation of 1/8 (where black is zero and white is 1).



./bilateral input.jpg output.jpg 5 0.125
