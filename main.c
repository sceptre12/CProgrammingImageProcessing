#include "header.h"

int main(int argc, char *argv[]){
        int c;
        /*
           opterr: If the value of this variable is nonzero then getopts prints an error message
                  to the standard error stream if it encounters an unkown option character or an
                  option with a missing required argument (this is the default behavior)
                  Setting it to 0 will not make getopts print any messages, but it returns
                  the character ? to indicate an error

         */
        opterr= 0;
        /*
            Creates an array of size 3 thats fileld with 0's
            Determines how many times an options arg is passed
            This also lets me know what options were passed;
         */
        int occurrence[3] = {0};
        char *outputFile = NULL;
        while((c = getopt(argc,argv,"s:r:fo:")) != -1) {
                switch(c) {
                case 's': // Scale
                          /*
                             optarg: This variable is set by getopt to point at the value of the
                             option argument, for those that accept arguments
                           */
                        if(occurrence[0] >= 2) {
                                fprintf(stderr, "More than one '-s' passed\n");
                                exit(1);
                        }
                        if(sscanf(optarg," %d", &occurrence[0]) != 1) {
                                fprintf(stderr, "Please Insert a number\n");
                                exit(1);
                        }
                        if(occurrence[0] < 0) {
                                fprintf(stderr, "Please Enter a positive number\n");
                                exit(1);
                        }
                        if(SHOWLOG)
                                printf("'s' Was passed with the arg being: '%d' \n", occurrence[0]);
                        break;
                case 'r': // Degree
                        if(occurrence[1] >= 2 || occurrence[1] < 0) {
                                fprintf(stderr, "More than one '-r' passed\n");
                                exit(1);
                        }
                        if(sscanf(optarg," %d", &occurrence[1]) != 1) {
                                fprintf(stderr, "Please Insert a number\n");
                                exit(1);
                        }
                        if((occurrence[1] % 90) != 0) {
                                fprintf(stderr, "The number must be a multiple of 90\n");
                                exit(1);
                        }
                        if(SHOWLOG)
                                printf("'r' Was passed with the arg being: '%d' \n",occurrence[1]);
                        break;
                case 'f': // Flip
                        occurrence[2]++;
                        if(occurrence[2] >= 2) {
                                fprintf(stderr, "More than one '-f' passed\n");
                                exit(1);
                        }
                        if(SHOWLOG)
                                printf("'f' Was passed \n");
                        break;
                case 'o': // Output file
                        occurrence[3]++;
                        if(occurrence[3] >= 2) {
                                fprintf(stderr, "More than one '-o' passed\n");
                                exit(1);
                        }
                        outputFile = optarg;
                        if(SHOWLOG)
                                printf("'o' Was passed with the arg being: '%s' \n",outputFile);
                        break;
                case '?':
                        if(optopt == 's' || optopt == 'r' || optopt == 'o') {
                                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                                /*
                                    isprint: checks whether a passed character is printable
                                 */
                        }else if(isprint(optopt)) {
                                /*
                                    Unknown Option passed
                                 */
                                fprintf(stderr, "Unkown Option '-%c'\n", optopt);
                        }else{
                                // Prints out the response in hex
                                fprintf(stderr, "Unkown Option char '\\x%x'\n",optopt);
                        }
                        exit(1);
                default:
                        abort();
                }
        }

        /*
            optind: is set by the getopts to the index of the next element to be processed
            this variable can be used to determine all non option arguments begining;
         */
        char *inputFile = NULL;
        if(argv[optind]) {
                inputFile = argv[optind];
        }

        determineFunctions(occurrence[0],occurrence[1],occurrence[2],outputFile,inputFile);

        return 0;
}
