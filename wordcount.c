/**********************************************************************
 * Name Marcel Champagne                                              *
 * Box(s): 3245                                                       *
 * Assignment name:  Supplemental Problem 12, Fall 2014               *
 * Assignment for Extra Credit                                        *
 **********************************************************************/

/* *********************************************************************
 * Academic honesty certification:                                     *
 *   Written/online sources used:                                      *
 *      None                                                           *
 *                                                                     *
 *   Help obtained                                                     *
 *      None
 *   My/our signature(s) below confirms that the above list of sources *
 *     is complete AND that I have not talked to anyone else           *
 *     about the solution to this problem                              *
 *                                                                     *
 *   Signature:                                                        *
     *******************************************************************/

#include <stdio.h>
#include <stdlib.h>

// A program that takes the name of a file and reads through the file to
// determine the number of words in each setence and then displays the result.


// pre-conditions: takes a int representing a char
// post-conditions: returns true if char is counted as white space
int isWhiteSpace(int ch){
  return !( (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || 
            (ch == '\'') || (ch == '\"') || (ch == '.') || 
            (ch == '?') || (ch == '!') );
}

// pre-conditions: takes an int representing a char
// post-conditions: returns true if char is counted as the end of a sentence
int isEndSentence(int ch){
  return ( (ch == '.') || (ch == '?') || (ch == '!') );
}

// pre-conditions: takes an int representing a char
// post-conditions: returns true if char is counted as a letter
int isLetter(int ch){
  return ( (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ); 
}

// pre-conditions: takes an int representing a char
// post-conditions: returns true if char is counted as a capital letter
int isCapital(int ch){
  return ( (ch >= 'A' && ch <= 'Z') ); 
}

// pre-conditions: takes an int representing a char
// post-conditions: returns true if char is counted as a digit
int isDigit(int ch){
  return ( (ch >= '0' && ch <= '9')); 
}

// pre-conditions: readFile takes a file and the string
//                 that represents the filename
// post-conditions: count the words and sentences, and print words in each sentence
//                  finally, print the total number of words and the average
//                  words/sentence

void readFile(FILE * filename, char name[]){
  int ch; // store the char as an int
  int pch = ' '; // store the previous 3 characters
  int ppch = ' '; 
  int pppch = ' '; 
  int whiteSpace = 1;
  int endSentence = 0;
  int sentence = 1;
  int words = 0;
  int totalWords = 0;
  while( (ch = getc(filename)) != EOF){

    // Ignore if end of sentence if embedded within digits
    // That is, if the current character is a digit, don't end the sentence
    if(isDigit(ch))
      endSentence = 0;

    // Don't end the sentence if before the end of the sentence
    // There was a single capital letter
    if(isCapital(ppch) && !isLetter(pppch))
      endSentence = 0;

    // End the sentence and increment the total words, reset current sentence words to 0
    if(endSentence){
        printf("Sentence:  %-8d    Words: %d\n",sentence,words);
        sentence += 1;
        totalWords += words;
        words = 0;
        endSentence = 0;
    }

    // Elementary sentence checking
    if(isWhiteSpace(ch)){
      whiteSpace = 1;
    }
    else if(isLetter(ch) && whiteSpace){
      words += 1;
      whiteSpace = 0;
    }
    else if(isEndSentence(ch)){
      endSentence = 1;
    }
    
    // Keep track of 3 most recent characters
    pppch = ppch;
    ppch = pch;
    pch = ch;
  }

  // If there are words after the last end of a sentence
  if(words != 0){
    printf("Sentence:  %-8d    Words: %d\n",sentence,words);
    totalWords += words;
  }
  else{
    sentence -= 1;
  }

  // Print the result
  double aveWords;
  if(sentence != 0)
    aveWords = (double)totalWords/sentence;
  else
    aveWords = 0.0;
  printf("File \"%s\" contains %d words in %d sentence(s) ",name,totalWords,sentence);
  printf("for an average of %.2lf words per sentence.\n",aveWords);
}

int main(){
  char filename[81];
  FILE * fp = NULL;
  while(fp == NULL){
    printf("Enter a filename for the program to read: \n");
    scanf("%s",filename);
    while(getchar() != '\n');
    fp = fopen(filename, "r");
    if(fp == NULL){
      printf("Invalid file name.\n");
    }
  }
  printf("This program counts the words and sentences in file \"%s\".\n\n",filename);
  readFile(fp,filename);
  fclose(fp);
}
