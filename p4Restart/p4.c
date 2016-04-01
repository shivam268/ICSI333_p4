#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
  
  
#define SIZE 100
#define INCREMENT 50
  
FILE *firstFile; // file for first method
FILE *lastFile;  // file for last method


char *firstFileName;
char *lastFileName;

int num;

char *read1;
char *read2;
char *read2;

char * nextLine(FILE *inputFile);


int main(int args, char *argv[]){
  
  FILE *cmdFile;
  
  //char line[SIZE];
  
  cmdFile = fopen(argv[1], "r");
  
  if((args !=2) || (cmdFile == NULL)){
    printf("ERROR: Command file cannot be opened \n");
    exit(1);
  }
  else{
    printf("File is opened \n");
  }
  
  
  while(nextLine(cmdFile) != NULL){
    printf("There is line \n");
    
  }
  
           
 return 0;          
  
}




char * nextLine(FILE *inputFile){

char * nextLine;
  
int lineSize = SIZE; // Initial size of line to be retrieved
int lineEnd = SIZE - 1; // Variable to refer to last elememt in nextLine

  if((nextLine = (char *) malloc(lineSize * sizeof(char))) == NULL){
    fprintf(stderr, "Allocation failed!\n");
    exit(1);
  }

  if(feof(inputFile)){
    return NULL;
  }
  
  else{
    while(nextLine[lineEnd] != '\n'){
    fgets(nextLine, lineSize, inputFile);
      
        lineSize += INCREMENT;
      
      if ((nextLine = (char *) realloc(nextLine, lineSize * sizeof(char))) == NULL){
        
        printf("line size after realloc: %d\n", lineSize);
        
        fprintf(stderr, "OMG Reallocation failed!\n");
        
        exit(1);
      }
      lineEnd = strlen(nextLine) - 1;
    }
  }
 
  printf("This is returned by next line function: %s", nextLine);
  
  return nextLine;
}

  
       