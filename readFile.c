#include "header.h"


/*
 * Reads an uncompressed 24-bit .bmp file from a file into an
 * array of pixels, notes the dimensions
 *
 * filename - the .bmp file's name
 * image    - an array containing the original pixels, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 */
int readFile (char *filename, int *rows, int *cols, pixel** image) {
  int fd;
  unsigned int start;

  if ((fd = open (filename, O_RDONLY)) < 0) {
    perror("Problem with input file");
    return -1;
  }

  readHeader (fd, rows, cols, &start);
  *image = (pixel *) malloc (sizeof(pixel) * (*rows) * (*cols));
  readBits (fd, *image, *rows, *cols, start);

  close (fd);

  return 0;

}

int readHeader(int fd, int *rows, int *cols, unsigned int *start) {

  BITMAPFILEHEADER bmfh;
  BITMAPINFOHEADER bmih;

  read (fd, (BITMAPFILEHEADER *)((unsigned long)(&bmfh) + 2), sizeof(bmfh)-2);
  read (fd, &bmih, sizeof(bmih));

  if(SHOWLOG) {
          printf("\t\tPrinting out the Bit File Header\n");
          printf("\t\t Padding: '%d'\n",(int)bmfh.padding);
          printf("\t\t The File Type: '%c'\n",(char)bmfh.bfType);
          printf("\t\t Size of Image in kb: '%d'\n",bmfh.bfSize/1024);
          printf("\t\t Reserved 1: '%u'\n",bmfh.bfReserved1);
          printf("\t\t Reserved 2: '%u'\n",bmfh.bfReserved2);
          printf("\t\t Offset: '%d'\n",(int)bmfh.bfOffBits);
          printf("\t\tLeaving the Print Bit File Header\n");
  }

  if(SHOWLOG) {
          printf("\t\tPrinting out the Bit File Info Header\n");
          printf("\t\t Required Bits: '%d'\n",(int)bmih.biSize);
          printf("\t\t Width: '%d'\n",(int)bmih.biWidth);
          printf("\t\t Height: '%d'\n",(int)bmih.biHeight);
          printf("\t\t Number of Planes for target Device: '%d'\n",(int)bmih.biPlanes);
          printf("\t\t Number of Bits per pixel: '%d'\n",(int)bmih.biBitCount);
          printf("\t\t Type of Compression '%d'\n",(int)bmih.biCompression);
          printf("\t\t Image size: '%d'\n",(int)bmih.biSizeImage);
          printf("\t\t Horizontal Resolution: '%d'\n",(int)bmih.biXPelsPerMeter);
          printf("\t\t Vertical Resolution: '%d'\n",(int)bmih.biYPelsPerMeter);
          printf("\t\t Number of color indexes that are actually used: '%d'\n",(int)bmih.biClrUsed);
          printf("\t\t Number of color indexes that are required: '%d'\n",(int)bmih.biClrImportant);
          printf("\t\tLeaving the Print Bit File Info Header\n");
  }
  *rows = bmih.biHeight;
  *cols = bmih.biWidth;
  *start = bmfh.bfOffBits;

  return 0;

}

int readBits (int fd, pixel *image, int rows, int cols,
                     unsigned int start) {

  int row;
  char padding[3];
  int padAmount = 0;

  padAmount = ((cols * sizeof(pixel)) % 4) ? (4 - ((cols * sizeof(pixel)) % 4)) : 0;

  lseek (fd, start, SEEK_SET);

  for (row=0; row < rows; row++) {
    read (fd, image + (row*cols), cols*sizeof(pixel));
    read (fd, padding, padAmount);
  }

  return 0;
}
