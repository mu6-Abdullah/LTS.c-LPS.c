#include "main.h"
#define maxLen 10000 

int main(int argc, char * argv[]){ //main function including command line arguments
	//create pointers for file in and file out
    char *fileIn;
    char *fileOut; 
    
    //set time
    srand(time(NULL)); 
    //the point of checkArr is to keep an account of all the fileIs entered in order to give out proper output
    int checkArr[6] = {0}; 
    // invalidate aims 
    bool invalidate = false;

    int caseA = 0;
    int caseB = 0;
    int caseC = 0;
    /*
	CHECK ARR EXPLANATION:
	0 = GEN NUMBERS
	1 = OUTPUT FILE GIVEN
	2 = input FILE PROVIDED
	3 = print LPS
	4 = print LTS
	5 = print LCS

	CASES EXPLANATION:
	A = Generate 2 sequences
    */
    for (int i = 1; i < argc;){ 
        if (strcmp(argv[i],"-g") == 0){ 
            if (!caseA && !caseB && !caseC){ //and not caseA (g flag set) or any of the other cases
                caseA = 1; //
                checkArr[0]++; //GEN numbers is true
                i++; 
            }else{
                invalidate = true;
                break;
            }
        }else if (strcmp(argv[i],"-i") == 0){ //if the flag is the fileI flag
            if (i + 1 != argc && !caseA && '-' != argv[i + 1][0]){ 
                checkArr[2] += 1; 
                fileIn = argv[i + 1]; 
                i += 2;
            }else{ 
                invalidate= true;
                break;
            }
		}else if (strcmp(argv[i],"-p") == 0){ 
            if (!caseA){ //it cannot be caseA 
                caseB = 1; //set caseB, the flag and increment down the array
                checkArr[3] += 1;
                i++;
            }
            else{ 
                invalidate = true;
                break;
            }
           
        }else if (strcmp(argv[i],"-o") == 0){ //or if the flag is for output
            if (i + 1 != argc && '-' != argv[i + 1][0]){ 
                checkArr[1] += 1; 
                fileOut = argv[i + 1]; 
                i += 2; 
            }else{ 
                invalidate = true;
                break;
            }
        
        
        }else if (strcmp(argv[i],"-t") == 0){ 
            if (!caseA){ //cant be case 1
                caseB = 1; //set caseB, set the flag and increment
                checkArr[4] += 1;
                i++;
            }else{ 
                invalidate = true;
                break;
            }
        }else if (strcmp(argv[i],"-c") == 0){ 
            if (!caseA){ //cant be caseA, set caseC, the flag and increment
                caseC = 1;
                checkArr[5] += 1;
                i++;
            }else{ 
                invalidate = true;
                break;
            }
        }else if (strcmp(argv[i],"-cp") == 0){ //if cp flag is set
        	printf("Error, this program does not support functionality to output LCPS \n");
        	invalidate = true;
        	break;

        }else if (strcmp(argv[i],"-ct") == 0){ //if ct flag is set
        	printf("Error, this program does not support functionality to output LCTS \n");
        	invalidate = true;
        	break;
        }else{ 
            invalidate = true;
            break;
        }
    }
    for (int i = 0; i < 6; i++){ 
        if (checkArr[i] != 0 && checkArr[i] != 1){
            invalidate = true;
        }
    }
    if (!caseA && !caseB && !caseC){ 
        invalidate = true;
    }
    
    if (invalidate == true){ 
        printf("-g [-o outputfilename]\n-t|-p [-i inputfilename] [-o outputfilename]\n-c|-ct|-cp [-t|-p] [-i inputfilename] [-o outputfilename]\n");
        return 0;
    }

    if (caseA){ //if it is case 1
    int lenArr[2] = {0}; //create the length array for the two sequences
    printf("Enter the two sequences length's: "); 
    // VALID LEN CHECKER
    for (int i = 0; i < 2; i++){
        int fileILen = scanf("%d",&lenArr[i]);
        while (!fileILen){ 
            fileILen = scanf("%d",&lenArr[i]);
        }
    }
    //create seqA and seqB
    char *seqA = (char *)malloc(lenArr[0] + 1); 
    char *seqB = (char *)malloc(lenArr[1] + 1);

    //generate random numbers
    gen_seq(seqA,lenArr[0]);
    gen_seq(seqB,lenArr[1]);


    char *sequences[2] = {seqA,seqB}; 
    if (checkArr[1] == 1){ 
        FILE *fileA; //open the file
        if ((fileA = fopen(fileOut,"a")) != NULL){ 
            for (int a = 0; a < 2; a++){ 
                for (int b = 0; b < lenArr[a]; b++){
                    fprintf(fileA,"%c",sequences[a][b]);
                }
                fprintf(fileA,"\n");
            }
            // close the file
            fclose(fileA); 
        }else{
            printf("Can't open file\n"); 
            //FREE SEQS
            free(seqA); 
            free(seqB);
            exit(EXIT_FAILURE);
        }
    }else{ 
    	//otherwise print to terminal
        for (int a = 0; a < 2; a++){ 
            for (int b = 0; b < lenArr[a]; b++){
                printf("%c",sequences[a][b]);
            }
            printf("\n");
        }
    }
    free(seqA); 
    free(seqB);
    }
    

    else if (caseB || caseC){ 
    	//create seqs
        char *seqA = (char *) malloc(maxLen + 2); 
        char *seqB = (char *) malloc(maxLen + 2);



         if (checkArr[2] == 1){ 
         	// INPUT FILE PROVIDED
            FILE *fileI; 
            if ((fileI = fopen(fileIn,"r")) != NULL){



            	//VALID fileI CHECK
                int value; 
                if (caseC){ 
                    value = read_file(fileI,2,seqA,seqB);
                }else{
                    value = read_file(fileI,1,seqA,seqB);
                }
                // close the file
                fclose(fileI);


                if  (value == 0){ 
                    free(seqA); 
                    free(seqB);
                    exit(EXIT_FAILURE);
                }



            }else{
                printf("Can't open file\n"); 
                //FREE SEQS
                free(seqA); 
                free(seqB);
                // EXIT
                exit(EXIT_FAILURE);
            }



        }else{ //if no input file was specified
            if (caseC){ //read in the correct number of sequences from the terminal depending on the case
                inputValidate(seqA,seqB);
                
            }else{
                inputValidate(seqA,seqB);
                
            }

        }
        int s1Len = strlen(seqA); //get the lens of both sequences
        int s2Len = strlen(seqB);
        int mSize = (s1Len > s2Len) ? s1Len : s2Len;

        // once all the given inputs are assorted with and it is assigned to individual cases
      	// there remains 2 possible cases for output, one where a valid output file is given
      	// and that file has the information of the oupuT appended to it or the case where
      	// there is no valid output file given then output to the terminal

        if (checkArr[1] != 1){ 
        	//	no output file
            if (checkArr[3] == 1){ 
            	//print LPS
                char *lpsOutput = (char*)malloc(s1Len + 1);
       
                printf("# an LPS (length = %d) for the sequence is: %s\n",lps(seqA,lpsOutput,s1Len),lpsOutput);
                free(lpsOutput);
            } 
            if (checkArr[4] == 1){
            	//print LTS
                char *ltsOutput = (char*)malloc(s1Len + 1);
                int ltsLen = 2 * lts(seqA,ltsOutput,s1Len);
                printf("# an LTS (length = %d) for the sequence is: %s%s\n",ltsLen,ltsOutput,ltsOutput);
                free(ltsOutput);   
            } 
            if (checkArr[5] == 1){
            	//print LCS
                char *lcsOutput = (char*)malloc(mSize + 1);
                int lcsLen = findLCS(s1Len,s2Len,seqA,seqB,lcsOutput);
                printf("# an LCS (length = %d) for the two sequences is: %s\n",lcsLen,lcsOutput);
                free(lcsOutput);
            }

        }else if (checkArr[1] == 1){ 
        	//SPECIFIED OUTPUT FILE
            FILE *fileOutput; 
            fileOutput = fopen(fileOut,"a");
            if (fileOutput == NULL){ //if output file cannot be opened
                printf("File cannot be opened!\n");//tell the user that, free the sequences and exit
                free(seqA);
                free(seqB);
                exit(EXIT_FAILURE);
            }
            if (checkArr[3] == 1){ 
            	//print LPS
                    char *lpsOutput = (char *)malloc(s1Len + 1);
                    fprintf(fileOutput,"# an LPS (length = %d) for the sequence is: %s\n",lps(seqA,lpsOutput,s1Len),lpsOutput);
                    free(lpsOutput);
            }
            if (checkArr[4] == 1){ 
            	//print LTS
                    char * ltsOutput = (char *)malloc(s1Len + 1);
                    int ltsLen = 2 * lts(seqA,ltsOutput,s1Len);
                    fprintf(fileOutput,"# an LTS (length = %d) for the sequence is: %s%s\n",ltsLen,ltsOutput,ltsOutput);
                    free(ltsOutput);
            }
            if (checkArr[5] == 1){ 
            	//print LCS
                    char *lcsOutput = (char *)malloc(mSize + 1);
                    int lcsLen = findLCS(s1Len,s2Len,seqA,seqB,lcsOutput);
                    fprintf(fileOutput,"# an LCS (length = %d) for the two sequences is: %s\n",lcsLen,lcsOutput);
                    free(lcsOutput);
            }
            
            fclose(fileOutput); //close the file
        }
        free(seqA); //free the sequences
        free(seqB);
    }
}