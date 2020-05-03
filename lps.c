#include "lps.h"
// Should contain all elements for LPS and LCPS


int lps(char *Y, char *lpsOutput,int size){ 
    char *reverse_arr = (char*)malloc(10000 + 1); 
    int r_size = size; 
    
    for(int i = 0; i < size+1; i++){ 
        reverse_arr[i] = Y[size-1-i];
    }
    
    int value = findLCS(size,r_size,Y,reverse_arr,lpsOutput); 
    
    free(reverse_arr); 
    
    return value; 
}
