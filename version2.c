#include <stdio.h> //libraries to include
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define maxLen 10000
int min(int a, int b);
int max(int a, int b);

int max(int a, int b) {
  return (a > b)? a : b;
}
int min(int a, int b){
  return (a < b)? a : b;
}

void inputValidate(char *X, char *Y){
  bool valid = false;
  int s1Len =0;
  int s2Len =0; 

  printf("To compute an LTS, \n");
  while (valid == false){
    printf("enter the first sequence: ");
    fgets(X,(maxLen +2),stdin);
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

    printf("enter the second sequence: ");
    fgets(Y,(maxLen + 2), stdin);
    s2Len = strlen(Y) -1;
    

    for (int counter2 = 0; counter2 < s2Len-1; counter2++){
      if('0' > Y[counter2] || '9' < Y[counter2 || Y[counter2] == ' ']){
        printf("Error, non-digit characters detected! \n\n");
        s2Len = 0;
        break;
      }
    }

    if(s1Len == 0 || s2Len == 0){
      printf("Please make sure int values are entered into the sequence! \n");
    }
    else
      valid = true;
    
  }
}

int findLCS(int s1Len,int s2Len, char *X, char *Y,char *output_seq){ 
    int **lenArr = (int**)malloc((s1Len + 1)*sizeof(int *)); 
    for (int k = 0; k < s1Len + 1; k++){
        lenArr[k] = (int*)malloc((s2Len + 1)*sizeof(int));   
    }
     
    int row = s1Len; 
    int col = s2Len;
    int len = 0; 

    for (int row = 0; row <= s1Len;row++){ 
        for (int col = 0; col <= s2Len;col++){
            if (row == 0 || col == 0){ 
                lenArr[row][col] = 0; 
                continue; 
            }

            else if (X[row-1] == Y[col-1]){ 
                lenArr[row][col] = lenArr[row-1][col-1] + 1;  
            }else{ 
                lenArr[row][col] = max(lenArr[row][col-1], lenArr[row-1][col]);
            }
        }
    }
    row = s1Len; 
    col = s2Len; 
    len = lenArr[s1Len][s2Len]; 
    int value = lenArr[s1Len][s2Len]; 
    while (row > 0 && col > 0){ 
        if (X[row-1] == Y[col-1]){ 
            output_seq[len-1] = X[row-1];
            len--; 
            row--; 
            col--;
        }else if(lenArr[row][col - 1] < lenArr[row - 1][col]) { 
        row--; 
        }else { 
        col--; 
        }
    }
    for (int i = 0; i < s1Len+1; i++){ 
         free(lenArr[i]);
    }
    free(lenArr);
    return value; 
}


int findSplit(char *X,int size, char *ltsOutput){ 
    int maxLCS = 0; 
    int output,split;
    int bestSplit = 0;
    
    for(split=1;split < size; split++){
        char *firstHalf = (char *)malloc(split + 1); 
        char *secondHalf = (char *)malloc((size-split)+1);
        
        memcpy(firstHalf,X, split);
        memcpy(secondHalf,(X + split),(size-split));

        *(firstHalf + split) ='\0'; 
        *(secondHalf + (size - split)) = '\0';
        
        output = findLCS(strlen(firstHalf),strlen(secondHalf),firstHalf,secondHalf,ltsOutput); 
        if (output > maxLCS){ 
            maxLCS = output;
            bestSplit = split;
        }
        free(firstHalf); 
        free(secondHalf);
    }
  
    return bestSplit; 
}


int lps(char *Y, char *lpsOutput,int size){ 
    char *reverse_arr = (char*)malloc(maxLen + 1); 
    int r_size = size; 
    
    for(int i = 0; i < size+1; i++){ 
        reverse_arr[i] = Y[size-1-i];
    }
    
    int value = findLCS(size,r_size,Y,reverse_arr,lpsOutput); 
    
    free(reverse_arr); 
    
    return value; 
}

int lts(char * X,char *ltsOutput, int size){ 
    int split = findSplit(X,size,ltsOutput); 
    
    char *firstHalf = (char *)malloc(split + 1); 
    char *secondHalf = (char *)malloc((size-split)+1);
    
    memcpy(firstHalf,X , (split) ); 
    memcpy(secondHalf, X + (split),(size-split));

    *(firstHalf + split) ='\0';
    *(secondHalf + (size - split)) ='\0';
    
    return findLCS(split,(size - split),firstHalf,secondHalf,ltsOutput); 
}

int main(){
    char *X = (char*)malloc(maxLen + 2); 
    char *Y = (char*)malloc(maxLen + 2);
    
    inputValidate(X,Y); 

    int s1Len = strlen(X); 
    int s2Len = strlen(Y);
    char *lpsOutput = (char*)malloc(s1Len + 1); 
    char *ltsOutput = (char*)malloc(s2Len + 1);

    printf("\n# the first sequence (length = %d) is:\n",s1Len); 
    printf("%s\n",X);
  
    printf("# an LTS (length = %d) for the first sequence is:\n",(2*lts(X,ltsOutput,s1Len))); 
    printf("%s%s\n",ltsOutput,ltsOutput);

    free(X); // free the sequence

    printf("# the second sequence (length = %d) is:\n",s2Len); 
    printf("%s\n",Y);

    printf("# an LPS (length = %d) for the second sequence is:\n",lps(Y,lpsOutput,s2Len)); 
    printf("%s\n",lpsOutput);

    free(Y); 
}

