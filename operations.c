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
    if((rows <=0 || cols <= 0)){
        return -1;
    }

    *newImage = (pixel *)malloc(rows*cols*sizeof(pixel));
    
    int rowIndex = 0, colIndex = 0;
    int rotateAmount = rotation / 90;
    if(rotateAmount > 0){
        if(SHOWLOG){
            printf("\t\t\tRotate Amount: '%d'\n", rotateAmount);
        }
        for(rowIndex = 0; rowIndex < rows; rowIndex++){
            for(colIndex = 0; colIndex < cols; colIndex++){
                *((*newImage) + (((rows*cols) - (rows + rows*colIndex)) + rowIndex)) = *(original + (((rows*cols) - (rows + rows*colIndex)) + rowIndex));
            }
        }

        while(rotateAmount != 0){
            for(rowIndex = 0; rowIndex < rows; rowIndex++){
                for(colIndex = 0; colIndex < cols; colIndex++){
                    *((*new) + ((((rows-1)-rowIndex)*cols) + colIndex)) = *(original + rowIndex*cols + colIndex);
                }
            }
            rotateAmount--;
        }
    }

    printf("\t\t\tLeaving Rotate function\n");
    return 0;
}
