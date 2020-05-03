#include "lcs.h"

//Should contain all functions for LCS

int max(int a, int b) {
  return (a > b)? a : b;
}
int min(int a, int b){
  return (a < b)? a : b;
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
