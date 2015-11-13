#include "header.h"

int flipImage (pixel *original, pixel **new, int rows, int cols) {
        if(SHOWLOG)
                printf("\t\tInside of the flip function\n");

        if ((rows <= 0) || (cols <= 0)) {
                return -1;
        }
        *new = (pixel *) malloc (rows*cols*sizeof(pixel));
        int rowIndex = 0, colIndex =0;

        for (rowIndex=0; rowIndex < rows; rowIndex++) {
                for (colIndex=0; colIndex < cols; colIndex++) {
                        *((*new) + ((((rows-1)-rowIndex)*cols) + colIndex)) = *(original + rowIndex*cols + colIndex);
                }
        }
        if(SHOWLOG)
                printf("\t\tLeaving the flip function\n");
        return 0;
}

int rotate (pixel *original,pixel **newImage, int rotation, int rows, int cols){
        if(SHOWLOG)
                printf("\t\t\tInside of Rotate function\n");
        if((rows <=0 || cols <= 0)) {
                return -1;
        }

        *newImage = (pixel *)malloc(rows*cols*sizeof(pixel));
        pixel *tempImage = (pixel *)malloc(rows*cols*sizeof(pixel));

        int rowIndex = 0, colIndex = 0;
        int rotateAmount = rotation / 90;
        if(rotateAmount > 0) {

                if(SHOWLOG) {
                        printf("\t\t\tRotate Amount: '%d'\n", rotateAmount);
                }
                for(rowIndex = 0; rowIndex < rows; rowIndex++) {
                        for(colIndex = 0; colIndex < cols; colIndex++) {
                                int newIndex = ((rows*cols) - (rows + rows*colIndex)) + rowIndex;
                                int oldIndex = rowIndex*cols + colIndex;
                                *((*newImage) + newIndex) = *(original + oldIndex);
                        }
                }

                while(rotateAmount > 1) {

                        for(rowIndex = 0; rowIndex < rows; rowIndex++) {
                                for(colIndex = 0; colIndex < cols; colIndex++) {
                                        int newIndex = ((rows*cols) - (rows + rows*colIndex)) + rowIndex;
                                        int oldIndex = rowIndex*cols + colIndex;
                                        *(tempImage + newIndex) = *((*newImage) + oldIndex);
                                }
                        }

                        if(SHOWLOG)
                                printf("First Free\n");
                        free(*newImage);
                        *newImage = (pixel *)malloc(rows*cols*sizeof(pixel));

                        for(rowIndex = 0; rowIndex < rows; rowIndex++) {
                                for(colIndex = 0; colIndex < cols; colIndex++) {
                                    if(rowIndex == 0) {
                                            *((*newImage) + colIndex) = *(tempImage + colIndex);
                                    }else{
                                            int normalIndex = ((rowIndex)*cols + colIndex);
                                            *((*newImage) + normalIndex) = *(tempImage + normalIndex);
                                    }
                                }
                        }
                        if(SHOWLOG)
                                printf("Second Free\n");
                        free(tempImage);
                        tempImage = (pixel *)malloc(rows*cols*sizeof(pixel));
                        rotateAmount--;
                }
        }

        printf("\t\t\tLeaving Rotate function\n");
        return 0;
}
int enlarge (pixel *original, int rows, int cols, int scale, pixel **newImage, int *newRows, int *newcols){
        if(SHOWLOG)
                printf("Inside of Enlarge Function\n" );

        *newRows = rows*scale;
        *newcols = cols*scale;

        int rowIndex = 0, colIndex = 0, scaleRowIndex =0, scaleColIndex =0;
        *newImage = (pixel *)malloc((rows*cols)*(scale*scale)*sizeof(int));

        if(SHOWLOG) {
                printf("old row: '%d', old cols: '%d'\n", rows, cols);
                printf("new row: '%d', new cols: '%d'\n",*newRows,*newcols);
        }

        for(rowIndex = 0; rowIndex < *newRows; rowIndex+= scale) {
                for(colIndex =0; colIndex < *newcols; colIndex += scale) {
                        for(scaleRowIndex = 0; scaleRowIndex < scale; scaleRowIndex++) {
                                int newIndex = ((rowIndex+scale)*(*newcols) + colIndex );
                                int oldIndex = ((rowIndex/scale)*((*newcols)/scale) + (colIndex/scale) );
                                *((*newImage) + newIndex) = *(original + oldIndex);

                                for(scaleColIndex = 0; scaleColIndex < scale; scaleColIndex++) {
                                        *((*newImage) + (newIndex + scaleColIndex)) = *(original + oldIndex);
                                }
                        }
                }
        }



        if(SHOWLOG)
                printf("Leaving the enlarge function\n");

        return 0;
}
