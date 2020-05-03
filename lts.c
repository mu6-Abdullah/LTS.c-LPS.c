#include "lts.h"

// Should contain all functions for LTS and LCTS
int findSplit(char *X, int s1Len){
  int maxLCS = 0;
   // grabs individual pieces of output from each LCS computation done
  int split;//the divisor that partitions the array at specific indices
  int bestSplit = 0;
  
  for(split=1;split < (s1Len); split++){
    char *firstHalf = (char *)malloc((split + 1)*sizeof(char)); //create a first half of the array
    char *secondHalf = (char *)malloc(((s1Len-split)+1)*sizeof(char));// create a seconf half of the array
    char *outputSeq = (char *)malloc((10000+1)*sizeof(char));
    memcpy(firstHalf,X,(split)); //copy the first partition from 0 to i into firstHalf // REMOVED * sizeof(int)
    memcpy(secondHalf,X+ (split),(s1Len-split));//copy the second part from the partition from i+1 to 100 into secondHalf
    *(firstHalf + split) ='\0';
    *(secondHalf + (s1Len-split)) = '\0';
    

    int output;
    output = findLCS(split,(s1Len-split),firstHalf,secondHalf,outputSeq);
    
    
    if (output > maxLCS){//use it to compare with any larger past maximums
      maxLCS = output;//if larger change the value of maxLCS
      bestSplit = split;
      

    free(firstHalf);
    free(secondHalf);
    }
  
  }
  return bestSplit;
}

int lts(char * X,char *ltsOutput, int size){ 
    int split = findSplit(X,size); 
    
    char *firstHalf = (char *)malloc(split + 1); 
    char *secondHalf = (char *)malloc((size-split)+1);
    
    memcpy(firstHalf,X , (split) ); 
    memcpy(secondHalf, X + (split),(size-split));

    *(firstHalf + split) ='\0';
    *(secondHalf + (size - split)) ='\0';
    
    return findLCS(split,(size - split),firstHalf,secondHalf,ltsOutput); 
}
