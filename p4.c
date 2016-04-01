/*
Parikh Shivam
Ukpere Stephanie

Project 4
2nd Group Project
*/


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100      // defines the initial size of the char
#define INCREMENT 50  // increment for realloc
#define MAX 3         // max amount of elements in token array -- used in main function
#define TRUNCMINLENGTH 2

FILE *firstFile;     // file pointer to print out first n line function
FILE *lastFile;      // file to print out last n line function
FILE *statFile;
FILE *patternFile;
FILE *diffFileOne;
FILE *diffFileTwo;
FILE *truncFile;

char *firstFileName;
char *lastFileName;
char *statFileName;
char *patternFileName;
char *diffFileNameOne;
char *diffFileNameTwo;
char *truncFileName;

int match;   // for prpat function

int num;

char *compareIn;  // this will point to the line returned by the nextLine function -- for prpat method


/* Function prototypes */

void first(int numFirstLines, char *fileName);
void last(int numLastLines, char *fileName);
char *nextLine(FILE *inputFile);
void stat(char *fileName);
void prpat(char *pattern, char *fileName);
void truncThis(int len, char *fileName);
void diff(char *fileNameOne, char *fileNameTwo);

///////////////////////////////////////////////////
///////         main Method STARTS            /////
///////////////////////////////////////////////////
//author Parikh Shivam
//author Ukpere Stephanie


/*
 This main method will open command file and read commmends using
 nextline function, this will determind which command needs to be called
 and if it gets at the end of line it will stop after finishing needed commands
 */

int main(int args, char *argv[]){ // This argument will keep track of input calls and
  // use the command file name to open it for reading

  FILE *cmdFile;                  // this pointer will point to the input command file

  char* line;
  char *cmdLineReader, *read[MAX];

  int i = 0;

  cmdFile = fopen(argv[1], "r");  // this will open the given file for reading

  if((args != 2)||(cmdFile == NULL)){ // if the given arguments are not equal to 2 (must be a.out command file)If the command file couldn't be open
    printf("ERROR: Command file cannot be opened \n"); // It will give error message about unsuccessful file open
    exit(1);                                           // It will exit the programm if the file is not opened
  }
  else{
    printf("Command file is opened \n");               // this will notify that file is open successfully
  }

  line =  nextLine(cmdFile);

    while(line != NULL){  // while the line is not null it will read the line
        cmdLineReader = strtok(line, " \t\r"); // stores the line using string token

        while(cmdLineReader != NULL){       // while the stored chars are not null do this
        read[i] = strdup(cmdLineReader);    // creates an array to store every word
        printf("read[%d] = [%s]\n", i, cmdLineReader); // prints array
            fflush(stdout);
            
        cmdLineReader = strtok(NULL, " \t\r");    //reads next word of the line
      i++;
    }

    // The following if else statmenents will compare the first element of the token array read
    // to the name of the method it aims to call

    if(strcmp(read[0], "stat") == 0){          // this statement will check if the command is "stat"

      statFileName = strtok(read[1], " \n"); //gets rid off endline character form the filename

      stat(statFileName);                   // calls stat method will filename
    }
    else if(strcmp(read[0], "prpat") == 0){    // this statement will check if the command is "prpat"

      patternFileName = strtok(read[MAX-1], " \n"); //gets rid off endline character form the filename

      prpat(read[1], patternFileName);      //calls prpat method with integer value and appropriate file name

    }
    else if(strcmp(read[0], "first") == 0){   // this statement will check if the command is "first"

      num = (int) strtol(read[1], NULL, 10);   //this will convert given parameter which is char[] will convert into an integer

      firstFileName = strtok(read[MAX-1], " \n");  //gets rid off endline character form the filename

      first(num, firstFileName);   // calls the appropriate method will parameters

    }
    else if(strcmp(read[0], "last") == 0){    // this statement will check if the command is "last"
        
      num = (int) strtol(read[1], NULL, 10);   //this will convert given parameter which is char[] will convert into an integer

      lastFileName = strtok(read[MAX-1], " \n");//gets rid off endline character form the filename

      last(num, lastFileName);                  // calls method will interger and filename as parameters
    }
    else if(strcmp(read[0], "trunc") == 0){   // this statement will check if the command is "trunc"

      num = (int) strtol(read[1], NULL, 10);  //this will convert given parameter which is char[] will convert into an integer

      truncFileName = strtok(read[MAX-1], " \n"); //gets rid off endline character form the filename

      truncThis(num, truncFileName);            //calls truncThis method will integer and filename

    }
    else if (strcmp(read[0], "diff") == 0){   // this statement will check if the command is "diff"

      diffFileNameOne = strtok(read[1], "\n");// stores the first file name without end line character
      diffFileNameTwo = strtok(read[MAX-1], "\n");// stores second file name without end line character

      diff(diffFileNameOne, diffFileNameTwo); //calls diff methos will two file as parameter

    }


    printf("Ready for next command.\n\n");
        fflush(stdout);
    i = 0;
    line = nextLine(cmdFile);       //this will read next line and loop continues

  } // while loop ends

  return 0;

}
///////////////////////////////////////////////////
///////         main Method ENDS              /////
///////////////////////////////////////////////////


///////////////////////////////////////////////////
///////         stat Method STARTS            /////
///////////////////////////////////////////////////
//author Ukpere Stephanie

/*
 This function willl take filename as parameter, opens it- if fails prints error
 also prints some statistics about the file contant such as,
 total number of lines
 length of longest line
 length of shortest line
 average length
 
 */

void stat(char *fileName){ // method takes filename as input
  unsigned long numLines = 0, longestLine = 0, shortestLine = 0, totalLength = 0, y;
  float avgLineLength = 0;
  char *buff;

  if((statFile = fopen(fileName, "r")) == NULL) {
    /* Open failed. */
  printf("Could not open file statFile for reading.\n");
    return;
  }
  else{
    printf("File opened.\n");
  }
  buff =  nextLine(statFile);

  if (buff == NULL){
    printf("Number of lines: %lu\nLength of longest line: %lu\nLength of shortest line: %lu\n", numLines, longestLine, shortestLine);
      fflush(stdout);
    printf("Average line length: %1.3f\n", avgLineLength);
      fflush(stdout);
    return;
  }

  longestLine = (unsigned long) strlen(buff);
  shortestLine = (unsigned long) strlen(buff);

  while (buff != NULL){

    numLines++;
    totalLength += (unsigned long) strlen(buff);

    printf("Line[%lu]:%s \tLine length:%lu \tTotal length:%lu \n", numLines, buff, (unsigned long) strlen(buff), totalLength);

      fflush(stdout);
    buff = nextLine(statFile);

    if(buff != NULL){
      y = (unsigned long) strlen(buff);

      if ( longestLine <= y ){
        longestLine = y;
      }

      if ( y <= shortestLine ){
        shortestLine = y;
      }
    }
    else{
      break;
    }
  }

  avgLineLength = (float) totalLength / numLines;

  printf("Number of lines: %lu\nLength of longest line: %lu\nLength of shortest line: %lu\n", numLines, longestLine, shortestLine);
    fflush(stdout);
  printf("Average line length: %1.3f\n", avgLineLength);
    fflush(stdout);

  printf("Ending stat.\n");

  if (fclose(statFile) == EOF) { /* Error in closing input file */
    printf("Error in closing statFile.\n");
    return;
  }
  printf("File closed.\n");

}

///////////////////////////////////////////////////
///////         stat Method ENDS             /////
///////////////////////////////////////////////////


///////////////////////////////////////////////////
///////         prpat Method STARTS           /////
///////////////////////////////////////////////////
//Author: Parikh Shivam

/*
 this will take pattern character and filename as input
 uses strstr function to search for substring
 if matches prints the whole line
 */

void prpat(char *pattern, char *fileName){ // this takes pattern character and a file name as parameters
  patternFile = fopen(fileName, "r");      // opens the given file for reading
  match = 0;   // this will check if the program doesnt find any match then there will be if statement to print out appropriat message



  if(patternFile == NULL){   // If the file wasn't opened correctly error will be printed
    printf("ERROR: File Open Failed for pattern check");
  }
  else{   // FIle is opened successfully do rest
    printf("Matches: \n");
    while((compareIn = nextLine(patternFile)) != NULL){ // while loop will run until nextLine becomes null
      if((strstr(compareIn, pattern)) != NULL){// there is strstr function to compare substrings. If there is a match it will not return NULL
        printf("%s\n", compareIn);// there is match, it will print the line which contains that substring
        match = 1;// it changes match to 1, it means there was a match atleast once, and will not print the "no match occur..."
      }
    }

  }

  if(match == 0){// if match is still 0, means there was not a single match
    printf("The specified pattern does not occur in the file. \n");
      fflush(stdout);
  }

  if (fclose(patternFile) == EOF) { /* Error in closing input file */
    printf("Error in closing patternFile.\n");
    return;
  }

}


///////////////////////////////////////////////////
///////         prpat Method ENDS             /////
///////////////////////////////////////////////////


///////////////////////////////////////////////////
///////         first Method STARTS           /////
///////////////////////////////////////////////////
//Author: Parikh Shivam
/*
 this will take integer and filename as input
 integer is the number of lines needs to be printed
 of the number is less than 0 then gives error
 and print given number of line if there are less lines then prins them all
 */

void first(int numFirstLines, char *fileName){ // this takes an integer and name of file as an input.

  firstFile = fopen(fileName, "r");

  if((numFirstLines < 0) || (firstFile == NULL)){ // this will check whether integer is less than 0 or file is opened right, print an error
    printf("Error: given number of lines is less than 0 OR File cannot be opened to reading \n");
  }

  else{ //file can be opened and number of lines is grear tha 0

    int i; // incerementer for for loop

    char *firstBuff; // character pointer will hold the given line from the file

    for(i = 0; i < numFirstLines; i++){ // this loop will run for given number of lines times
      firstBuff = nextLine(firstFile);  // firstBuff will point to line retunred by nextLine

      if(firstBuff == NULL){        // if the given number to print lines is greater than there are actual lines in the file it will return
        return;
      }
      else{  // if there is line stored in firtBuff it will printed now
        printf("First n Lines: %s\n", firstBuff);
          fflush(stdout);
      }
    }

    if (fclose(firstFile) == EOF) { /* Error in closing input file */
      printf("Error in closing statFile.\n");
      return;
    }

  }

}

///////////////////////////////////////////////////
///////         first Method ENDS             /////
///////////////////////////////////////////////////


///////////////////////////////////////////////////
///////          last Method ENDS             /////
///////////////////////////////////////////////////



void last(int numLastLines, char *fileName){

  if((lastFile = fopen(fileName, "r")) == NULL) {
    /* Open failed. */
    printf("Could not open file lastFile for reading.\n");
    return;
  }
  else{
    printf("File opened.\n");
  }

  printf("funky things will happen here.\n");

  if (fclose(lastFile) == EOF) { /* Error in closing input file */
    printf("Error in closing lastFile.\n");
    return;
  }
  printf("File closed.\n");

  printf("last successful.\n");
  return;
}

///////////////////////////////////////////////////
///////          last Method ENDS             /////
///////////////////////////////////////////////////



///////////////////////////////////////////////////
/////       truncThis Method STARTS           /////
///////////////////////////////////////////////////
//Author Parikh Shivam

/*
 This will truncate the whole given file to the given length-1
 and puts end line character at the end
 if the line is "shivam" and length to print is 3, it will print "sh\n"
 */



void truncThis(int len, char *fileName){// takes int and filename as parameters

  char *truncIt;

  int i;

  truncFile = fopen(fileName, "r"); // open file for reading




  if((len < TRUNCMINLENGTH) || (truncFile == NULL)){  // check for the length and it should be at least 2 and also check if the file is opened successfully for reading
    printf("ERROR: The length has to be at least 2 or the given file cannot be opened. \n");
  }
  else{
    while((truncIt = nextLine(truncFile)) != NULL){  // get lines from the file until it returns NULL

    for(i = 0; i < len-1; i++){// for loop will run 1 less times than given length
    printf("%c", truncIt[i]);// print the trunceted lines to appropriate length
        fflush(stdout);
      }

      printf("\n");// new line character
    }
  }

}

///////////////////////////////////////////////////
//////      truncThis Method ENDS             /////
///////////////////////////////////////////////////


///////////////////////////////////////////////////
///////         diff  Method STARTS           /////
///////////////////////////////////////////////////
//author Stephanie Ukpere
/* This method takes in two char pointers that
 * represent file names. It opens the files,
 * and compares them line by line to determine
 * if they are different or identical.
 * It prints the result to stdout.
 *
 */
void diff(char *fileNameOne, char *fileNameTwo){ // takes two files as parameters

  char *buffOne, *buffTwo;
  int lineCount = 0;

    if((diffFileOne = fopen(fileNameOne, "r")) == NULL) { // if it fails to open for reading
    /* Open failed. */
    printf("Could not open file statFile for reading.\n");
    return;
  }
  else{
    printf("First file opened.\n");

      if((diffFileTwo = fopen(fileNameTwo, "r")) == NULL) { // if it fails to open for reading
      /* Open failed. */
      printf("Could not open file statFile for reading.\n");
      return;
    }
    else{
        printf("Second file opened.\n");
    }
  }

    
  buffOne = nextLine(diffFileOne);
  buffTwo = nextLine(diffFileTwo);

    
  if ((buffOne == NULL) || (buffTwo == NULL)){
    if ((buffOne == NULL) && (buffTwo == NULL)){
      printf("Both file are empty, thus identical.\n");
      return;
    }

    lineCount++;
    printf("One of the files is empty, so the difference occurs in line %d by default.\n", lineCount);
    return;
  }

  while( (buffOne != NULL) || (buffTwo != NULL) ){
    lineCount++;

          //if ( (strcmp(buffOne, buffTwo)) != 0 ) {
      if((buffOne == buffTwo) != 0){
      printf("The files are different; the first difference is in line %d.\n", lineCount);
          fflush(stdout);
      return;
    }

    buffOne = nextLine(diffFileOne);
    buffTwo = nextLine(diffFileTwo);
  }

        if(buffOne == buffTwo){
        printf("The files are identical.");
            fflush(stdout);
        return;
      }
      else{
        printf("The files are different but were identical up until line %d.\n", lineCount + 1);
          fflush(stdout);
        return;
      }
    }
///////////////////////////////////////////////////
///////         diff  Method ENDS             /////
///////////////////////////////////////////////////


///////////////////////////////////////////////////
///////         nextLine Method ENDS          /////
///////////////////////////////////////////////////
//author Stephanie Ukpere

char * nextLine(FILE *inputFile){
  char *nextLine;
  char c;
  int lineSize = SIZE;
  int index = 0;

    if ((nextLine = (char *) malloc (lineSize * sizeof (char))) == NULL) { // if allocation is failed
    fprintf(stderr, "Allocation failed!\n");
        exit(1); // exit the program
  }

  nextLine[0] = '\0';

  if ((c = fgetc(inputFile)) == EOF) {
    return NULL;
  }

  /* while there is enough space in nextLine for a string */
  while (index + 1 < lineSize) {

    /* in the case that the end of the line is reached */
    if (c == '\n' || c == '\r') {
      if (c == '\r')
        fgetc(inputFile);

      nextLine[index] = '\n';
      nextLine[index + 1] = '\0';

      return nextLine;
    }

    /* if last line has been reached */
    else if (c == EOF) {
      return nextLine;
    }

    /* puts retrieved character in nextLine */
    nextLine[index] = c;

    /* makes last element '\0' which required for strings */
    nextLine[index+1] = '\0';

    index++;

    /* gets next character from file */
    c = fgetc(inputFile);

    /* checks if line (including space for '\0' character) needs more space */
    if (index + 1 == lineSize) {

      /* increases lineSize */
      lineSize += INCREMENT;

      /* Space reallocation */
      if ((nextLine = (char *) realloc (nextLine, lineSize * sizeof (char))) == NULL) {

        /* prints error if space cannot be reallocated */
        fprintf(stderr, "Reallocation failed!\n");
        exit(1);
      }
    }
  }
  return nextLine;

}
///////////////////////////////////////////////////
///////         nextLine Method ENDS          /////
///////////////////////////////////////////////////
