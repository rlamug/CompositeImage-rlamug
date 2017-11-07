//Rodolfo Lamug

//Keep asking the user for a file name until they type in "Done". Note: 10 files is the maximum number allowed.
//Prints out error if not valid bitmap file or the file is non-existent. Also prints out error if the width and height of the image doesn't have the same dimensions (width and height) as the first image loaded. Do not include files that have an error as described above. After evaluating all the file names, if at least 2 images don't have the same dimensions print out error message that a composite image cannot be created and do not do anything else in the program.
//The program should work with any valid BMP images that are 24bit color depth and uncompressed, regardless of its size.
//Combine the valid images together to make a composite image.


//Prototypes:
//This function is where it  will average the RGB values for each pixel
void averagePixel(PixelMatrix &, int);
//This function will check if the users image is a valid one
bool validImage(Bitmap image);
//This function is where I ask user for image
void askedImage(Bitmap input);
//This function will check if the images are the same size. If atleast two  aren't then the program will do nothing.
void dimensionImage(Bitmap size);
