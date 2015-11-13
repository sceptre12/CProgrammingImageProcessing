#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// CONSTANTS DECLARATIONS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define TRUE  1
#define FALSE  0
#define SHOWLOG 1
#define DEFAULT_OFFSET 1078

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// STRUCTS DECLARATIONS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct {
        unsigned char r;
        unsigned char g;
        unsigned char b;
} pixel;

typedef struct {
  unsigned short padding;
  unsigned short bfType;
  unsigned int bfSize;
  unsigned short bfReserved1;
  unsigned short bfReserved2;
  unsigned int bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
  unsigned int biSize;
  int biWidth;
  int biHeight;
  unsigned short biPlanes;
  unsigned short biBitCount;
  unsigned int biCompression;
  unsigned int biSizeImage;
  unsigned int biXPelsPerMeter;
  unsigned int biYPelsPerMeter;
  unsigned int biClrUsed;
  unsigned int biClrImportant;
} BITMAPINFOHEADER;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FUNCTION OPERATIONS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
    Reads in the Bmpmap image and gathers information from the header
    Gets the width and height of the image which is used to calculate
    all of the bits that will be passed into the array of images
*/
int readFile (char fileName[], int *rows, int *cols, pixel **image);
int readHeader(int fd, int *rows, int *cols, unsigned int *start);
int readBits (int fd, pixel *image, int rows, int cols, unsigned int start);

/*
    Outputs the Bmpmap image and writes all the necessary information to the
    file first by creating the header and then using the rows and cols to
    generate the binary that should be put into the file
*/
int writeFile (char fileName[], int rows, int cols, pixel *image);
int writeHeader(int fd, unsigned int rows, unsigned int cols, unsigned int start);
int writeBits(int fd, int rows, int cols, pixel *image, unsigned int start);

/*
    Operates on the file
*/
int flipImage (pixel *original, pixel **newImage, int rows, int cols);
int rotate (pixel *original, pixel **newImage, int rotation, int rows, int cols);
int enlarge(pixel *original, int rows, int cols, int scale, pixel **newImage, int *newRows, int *newcols);

// Determines which operations to run
void determineFunctions(int scale, int degree, int flip,char *outputFile,char *inputFile);
