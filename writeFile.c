#include "header.h"

/*
 * Writes an uncompressed 24-bit .bmp file, given an array of pixels,
 * and the dimensions
 *
 * filename - the .bmp file's name
 * image    - an array containing the original pixels, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 */
int writeFile (char *filename, int rows, int cols, pixel *image) {
  int fd;
  unsigned int start = DEFAULT_OFFSET;

  if ((fd = open (filename, O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0) {
    perror("Problem with output file");
    return -1;
  }

  writeHeader (fd, rows, cols, start);
  writeBits(fd, rows, cols, image, start);

  close (fd);
  return 0;
}

int writeHeader(int fd, unsigned int rows, unsigned int cols,
                       unsigned int start) {

  unsigned int fileSize;
  unsigned int headerSize;

  unsigned int paddedCols;

  int count =0;

  BITMAPFILEHEADER bmfh;
  BITMAPINFOHEADER bmih;

  memset (&bmfh, 0, sizeof(bmfh));
  memset (&bmih, 0, sizeof(bmih));

  paddedCols = ((cols/4)*4 !=cols ? ((cols+4)/4)*4 : cols);

  headerSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
  fileSize = rows*paddedCols*sizeof(pixel)+headerSize;

  bmfh.bfType = 0x4D42;
  bmfh.bfSize = fileSize;
  bmfh.bfReserved1 = 0;
  bmfh.bfReserved2 = 0;
  bmfh.bfOffBits = start;
  bmih.biSize = 40;
  bmih.biWidth  = cols;
  bmih.biHeight = rows;
  bmih.biPlanes = 1;
  bmih.biBitCount = 24;
  bmih.biCompression = 0;
  bmih.biSizeImage = 0;
  bmih.biXPelsPerMeter  = 0;
  bmih.biYPelsPerMeter = 0;
  bmih.biClrUsed = 0;
  bmih.biClrImportant = 0;

  write (fd, (BITMAPFILEHEADER *)((unsigned long)(&bmfh) + 2), sizeof(bmfh)-2);
  count = write (fd, &bmih, sizeof(bmih));

  return 0;

}

int writeBits(int fd, int rows, int cols,
                     pixel *image, unsigned int start) {
  int row;

  char padding[3];
  int padAmount;

  padAmount = ((cols * sizeof(pixel)) % 4) ? (4 - ((cols * sizeof(pixel)) % 4)) : 0;

  memset(padding, 0, 3);

  lseek (fd, start, SEEK_SET);

  fflush (stdout);

  for (row=0; row < rows; row++) {
    write (fd, image + (row*cols), cols*sizeof(pixel));
    write (fd, padding, padAmount);
  }

  return 0;
}
