#include "utility.h"

void inputValidate(char *X, char *Y){
  bool valid = false;
  int s1Len =0;
  //int s2Len =0; 

  //printf("To compute an LTS, \n");
  while (valid == false){
    printf("enter the sequence: ");
    fgets(X,(10000 +2),stdin);
    s1Len = strlen(X) -1;

    if((s1Len>0)&& X[s1Len-1] =='\n'){
        X[s1Len] = '\0';
    }

    for (int counter1 =0; counter1 < s1Len-1; counter1++){
      if('0' > X[counter1] || '9' < X[counter1] || X[counter1] == ' '){
        printf("Error, non-digit characters detected! \n\n");
        s1Len = 0;
        break;
      }
    }
    if (s1Len ==0)
      continue;
    /*
    printf("enter the second sequence: ");
    fgets(Y,(10000 + 2), stdin);
    s2Len = strlen(Y) -1;
    

    for (int counter2 = 0; counter2 < s2Len-1; counter2++){
      if('0' > Y[counter2] || '9' < Y[counter2 || Y[counter2] == ' ']){
        printf("Error, non-digit characters detected! \n\n");
        s2Len = 0;
        break;
      }
    }
    */
    if(s1Len == 0){
      printf("Please make sure int values are entered into the sequence! \n");
      continue;
    }
    else
      valid = true;
    
  }
}
void gen_seq(char *seq, int seq_len){
	//create a number a
	int a;
	//create a container that holds all ints generated
	char int_container[2] = {'\0'};

	for(a=0;a < seq_len;a++){
		int q = rand() % 10;
		//append each randomly generated int from the cointainer
		// to the final seq
		sprintf(int_container,"%d",q);
		seq[a] = int_container[0];
	}

}

int read_file(FILE *filename, int opt, char *seq_a, char *seq_b){ //read input from a specified file into seq
    int a = 0; //int counters
    int b = 0;

    char ch = fgetc(filename); //get the first character of the file
    while (ch != '\n'){ //if it isnt a new line and while the character does not become a newline
        if (isdigit(ch)){ //check if its a digit
            seq_a[a] = ch; //if it isnt add it to the seq and iterate down it
            a++;
            ch = fgetc(filename); //get the next character
        }else{ //if the character isn't a digit
            printf("Invalid input sequence(s)!\n"); //print that it isnt a digit
            return 0; //return failiure code
        }
    }

    if (opt == 2){ //if we need two sequences
        ch = fgetc(filename); //get character after newline
        while (ch != '\n' && ch != EOF){ //while the next character isnt a newline and we havent reached the end of the file
            if (isdigit(ch)){ //check if character is a digit
                seq_b[b] = ch; //if not add it to the seq and iterate down the seq
                b++;
                ch = fgetc(filename); //get next character
            }else{ //otherwise print as much and return failiure code
                printf("Invalid input sequence(s)!\n");
                return 0;
            }
        }
    }

    return 1; //return success code

}