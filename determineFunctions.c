#include "header.h"

void determineFunctions(int scale, int degree, int flip, char *outputFile,char *inputFile){
        if(SHOWLOG) {
                printf("\n\tInside of Determine Functions\n");
                printf("\tValues being passed:\n");
                printf("\tScale: '%d' | Degree: '%d' | Flip: '%d'\n\tOutputFile: '%s' | InputFile: '%s'\n", scale,degree,flip,outputFile,inputFile);
        }

        int rows = 0, cols = 0;
        pixel *oldimage;
        pixel *newImage;

        // This is a flag to determine if morethan one command line args was passed
        int otherFunctionPassed = 0;

        if(inputFile == NULL) {

        }else{
                if(SHOWLOG)
                        printf("\tInside of the reading Inputfile\n");

                readFile(inputFile,&rows,&cols, &oldimage);

                if(SHOWLOG)
                        printf("\tLeaving the reading Inputfile\n");
        }

        if(scale) {
                if(SHOWLOG)
                        printf("\tInside of the enlarge image\n");

                otherFunctionPassed++;
                enlarge(oldimage,rows,cols,scale,&newImage, &rows,&cols);

                if(SHOWLOG)
                        printf("\tLeaving the enlarge image\n");
        }

        if(degree) {
                if(SHOWLOG)
                        printf("\tInside of the Rotating function\n");

                otherFunctionPassed++;
                if(otherFunctionPassed > 1) {
                        oldimage = newImage;
                }
                rotate (oldimage,&newImage,degree,rows,cols);


                if(SHOWLOG)
                        printf("\tLeaving the Rotating function\n");
        }

        if(flip) {
                if(SHOWLOG)
                        printf("\tInside of the flip function\n");

                otherFunctionPassed++;
                if(otherFunctionPassed > 1) {
                        oldimage = newImage;
                }
                flipImage(oldimage, &newImage,rows,cols);

                if(SHOWLOG)
                        printf("\tLeaving the flip function\n");
        }

        if(outputFile == NULL) {

        }else{
                if(SHOWLOG)
                        printf("\tInside of the Writing outputfile\n");

                writeFile(outputFile,rows,cols,newImage);

                if(SHOWLOG)
                        printf("\tLeaving the Writing outputfile\n");
        }

        if(SHOWLOG)
                printf("\tLeaving Determine functions\n");
}
